// FindMoreFunctions.java -- POST-analysis pass that recovers functions the default
// analyzers miss (reached only via function-pointer tables in .rodata / the .data init
// image, ChibiOS thread entry points, driver vtables, QMK keycode handler tables...).
//
// Pass A  function-pointer scan: every 4-byte-aligned word in 0x08000000..CODE_END whose
//         value is odd and points into the text range is treated as a Thumb function
//         pointer; if the target is not already a function entry it is disassembled and a
//         function created there (Ghidra then re-analyses it and follows its calls).
// Pass B  orphan instructions: instruction ranges not inside any function get a function
//         created at their start.
// Pass D  switch tables: every tbb/tbh whose targets Ghidra did not resolve gets its table
//         decoded (count from the preceding cmp rN,#imm), COMPUTED_JUMP references added,
//         the targets disassembled and the table typed as data; the owning function body
//         is then recomputed.
// Pass C  gap scan (only in rounds where A, B and D found nothing, so literal pools
//         referenced by new code have been typed by the constant-reference analyzer): each
//         undefined range in 0x08008000..RODATA_LIMIT is walked halfword by halfword;
//         padding (0x0000, 0xBF00 nop, 0xFFFF), referenced literal-pool words and words
//         holding flash addresses are skipped; at the first halfword that is a strict
//         function-start shape a function is created.
// Every function created by B or C is validated: if its flow runs into a "Bad Instruction"
// error or falls through into undefined bytes, it is removed again and the bytes cleared.
// After each round analyzeChanges() runs; rounds repeat until nothing new appears.
// Pass E  body fixup: functions whose body swallowed another function's entry point (b.w
//         tail calls disassembled before the callee became a function) are recomputed.
// Finally any function/instruction at or beyond RODATA_LIMIT is removed (data region).
// Every created/removed entry is logged ("FindMoreFunctions: A/B/C/D/E/REVERT/CLEANUP ...").
// Arg 0 (optional) = RODATA_LIMIT hex (default 0x08016000).
//@category Keychron
import ghidra.app.cmd.function.CreateFunctionCmd;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressRange;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.address.AddressSetView;
import ghidra.program.model.data.ArrayDataType;
import ghidra.program.model.data.ByteDataType;
import ghidra.program.model.data.UnsignedShortDataType;
import ghidra.program.model.lang.Register;
import ghidra.program.model.listing.Bookmark;
import ghidra.program.model.listing.BookmarkManager;
import ghidra.program.model.listing.BookmarkType;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.listing.Listing;
import ghidra.program.model.symbol.RefType;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.SourceType;

import java.math.BigInteger;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Set;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class FindMoreFunctions extends GhidraScript {
    static final long BASE = 0x08000000L;
    static final long CODE_START = 0x08008000L;
    static final long CODE_END = 0x08017F04L;

    long rodataLimit = 0x08016000L;
    Register tmode;
    int createdA = 0, createdB = 0, createdC = 0, switchesD = 0, fixedE = 0, createdF = 0, absorbedG = 0, reverted = 0;
    Set<Long> tried = new HashSet<>();
    List<String> log = new ArrayList<>();

    @Override
    protected void run() throws Exception {
        if (getScriptArgs().length > 0 && getScriptArgs()[0].startsWith("0x")) {
            rodataLimit = Long.parseLong(getScriptArgs()[0].substring(2), 16);
        }
        tmode = currentProgram.getProgramContext().getRegister("TMode");
        int before = currentProgram.getFunctionManager().getFunctionCount();
        for (int round = 1; round <= 12; round++) {
            int a = passPointers();
            int b = passOrphans();
            int d = passSwitchTables();
            int f = passTailTargets();
            int c = 0;
            if (a + b + d + f == 0) c = passGaps();
            println(String.format("FindMoreFunctions: round %d  A(pointers)=%d  B(orphans)=%d  D(switches)=%d  F(tail-targets)=%d  C(gaps)=%d  functions=%d",
                round, a, b, d, f, c, currentProgram.getFunctionManager().getFunctionCount()));
            if (a + b + c + d + f == 0) break;
            analyzeChanges(currentProgram);
        }
        int g = passAbsorbSwitchFragments();
        int e = passFixupBodies();
        int removed = cleanupRodata();
        if (g + e + removed > 0) analyzeChanges(currentProgram);
        int after = currentProgram.getFunctionManager().getFunctionCount();
        println(String.format("FindMoreFunctions: functions %d -> %d (A=%d B=%d C=%d D=%d E=%d F=%d G(absorbed)=%d reverted=%d)",
            before, after, createdA, createdB, createdC, switchesD, fixedE, createdF, absorbedG, reverted));
        for (String s : log) println(s);
    }

    // ---------------------------------------------------------------- helpers
    private boolean hasErrorBookmarkOrBadFlow(Function f) {
        Listing lst = currentProgram.getListing();
        BookmarkManager bm = currentProgram.getBookmarkManager();
        AddressSetView body = f.getBody();
        Iterator<Bookmark> it = bm.getBookmarksIterator(BookmarkType.ERROR);
        while (it.hasNext()) {
            Bookmark b = it.next();
            Address a = b.getAddress();
            if (body.contains(a)) return true;
            if (a.getOffset() == body.getMaxAddress().getOffset() + 1) return true;
        }
        InstructionIterator iit = lst.getInstructions(body, true);
        while (iit.hasNext()) {
            Instruction ins = iit.next();
            if (ins.getFlowType().hasFallthrough()) {
                Address ft = ins.getFallThrough();
                if (ft != null && !body.contains(ft) && lst.getInstructionAt(ft) == null) return true;
            }
        }
        return false;
    }

    private boolean tryCreate(Address ta, String pass, String why, boolean validate) {
        Listing lst = currentProgram.getListing();
        if (lst.getFunctionAt(ta) != null) return false;
        if (lst.getFunctionContaining(ta) != null) return false;   // inside another body
        try {
            currentProgram.getProgramContext().setValue(tmode, ta, ta, BigInteger.ONE);
        } catch (Exception e) { /* already has instructions */ }
        boolean disassembledHere = false;
        if (lst.getInstructionAt(ta) == null) {
            if (lst.getDefinedDataContaining(ta) != null) return false;   // typed data, don't override
            disassemble(ta);
            disassembledHere = true;
            if (lst.getInstructionAt(ta) == null) return false;
        }
        Function f = createFunction(ta, null);
        if (f == null) return false;
        if (validate && hasErrorBookmarkOrBadFlow(f)) {
            AddressSetView body = f.getBody();
            log.add(String.format("FindMoreFunctions: REVERT %s 0x%08X size=%d (bad flow) %s", pass, ta.getOffset(), body.getNumAddresses(), why));
            currentProgram.getFunctionManager().removeFunction(ta);
            if (disassembledHere) {
                try { clearListing(body); } catch (Exception e) { /* ignore */ }
            }
            reverted++;
            return false;
        }
        log.add(String.format("FindMoreFunctions: %s 0x%08X size=%d %s", pass, ta.getOffset(), f.getBody().getNumAddresses(), why));
        return true;
    }

    // ---------------------------------------------------------------- Pass A
    private int passPointers() throws Exception {
        int n = 0;
        for (long a = BASE; a + 4 <= CODE_END; a += 4) {
            long v = getInt(toAddr(a)) & 0xFFFFFFFFL;
            if ((v & 1) == 0 || v < CODE_START || v >= rodataLimit) continue;
            Address ta = toAddr(v & ~1L);
            if (currentProgram.getListing().getInstructionContaining(toAddr(a)) != null) continue;
            if (tryCreate(ta, "A", String.format("ptr word @0x%08X", a), false)) { n++; createdA++; }
        }
        return n;
    }

    // ---------------------------------------------------------------- Pass B
    private int passOrphans() throws Exception {
        Listing lst = currentProgram.getListing();
        AddressSet code = new AddressSet(toAddr(CODE_START), toAddr(rodataLimit - 1));
        AddressSet fnSet = new AddressSet();
        FunctionIterator fit = currentProgram.getFunctionManager().getFunctions(true);
        while (fit.hasNext()) fnSet.add(fit.next().getBody());
        AddressSet insSet = new AddressSet();
        InstructionIterator iit = lst.getInstructions(code, true);
        while (iit.hasNext()) { Instruction i = iit.next(); insSet.add(i.getMinAddress(), i.getMaxAddress()); }
        AddressSetView orphan = insSet.subtract(fnSet);
        int n = 0;
        for (AddressRange r : orphan) {
            Instruction ins = lst.getInstructionAt(r.getMinAddress());
            if (ins == null) continue;
            while (ins != null && ins.getMnemonicString().equals("nop") && r.contains(ins.getMaxAddress().add(1))) {
                ins = ins.getNext();
            }
            if (ins == null || !r.contains(ins.getAddress())) continue;
            if (tryCreate(ins.getAddress(), "B", "orphan instruction range " + r, true)) { n++; createdB++; }
        }
        return n;
    }

    // ---------------------------------------------------------------- Pass D
    static final Pattern TB_RE = Pattern.compile("\\[pc,\\s*(r\\d+)");
    static final Pattern CMP_RE = Pattern.compile("^cmp\\s+(r\\d+),\\s*#(0x[0-9a-fA-F]+|\\d+)");

    private int passSwitchTables() throws Exception {
        return passSwitchTables(new AddressSet(toAddr(CODE_START), toAddr(rodataLimit - 1)));
    }

    private int passSwitchTables(AddressSetView scope) throws Exception {
        Listing lst = currentProgram.getListing();
        int n = 0;
        InstructionIterator iit = lst.getInstructions(scope, true);
        List<Instruction> tbs = new ArrayList<>();
        while (iit.hasNext()) {
            Instruction ins = iit.next();
            String m = ins.getMnemonicString();
            if (m.equals("tbb") || m.equals("tbh")) tbs.add(ins);
        }
        for (Instruction ins : tbs) {
            boolean resolved = false;
            for (Reference r : ins.getReferencesFrom()) if (r.getReferenceType().isJump()) { resolved = true; break; }
            if (resolved) continue;
            boolean half = ins.getMnemonicString().equals("tbh");
            Matcher mt = TB_RE.matcher(ins.toString());
            if (!mt.find()) { log.add("FindMoreFunctions: D skip (not pc-based) " + ins.getAddress() + " " + ins); continue; }
            String idx = mt.group(1);
            // find the bounding cmp within the previous 8 instructions
            int count = -1;
            Instruction p = ins.getPrevious();
            for (int k = 0; k < 8 && p != null; k++, p = p.getPrevious()) {
                Matcher mc = CMP_RE.matcher(p.toString());
                if (mc.find() && mc.group(1).equals(idx)) {
                    String v = mc.group(2);
                    count = (v.startsWith("0x") ? Integer.parseInt(v.substring(2), 16) : Integer.parseInt(v)) + 1;
                    break;
                }
            }
            long table = ins.getAddress().getOffset() + 4;
            if (count < 0) count = 0; // unknown: probe with sanity limits below
            List<Long> targets = new ArrayList<>();
            int limit = count > 0 ? count : 64;
            for (int i = 0; i < limit; i++) {
                long off = half ? (getShort(toAddr(table + 2L * i)) & 0xFFFF) : (getByte(toAddr(table + i)) & 0xFF);
                long tgt = table + 2 * off;
                if (count == 0) {  // probing: stop at implausible entries
                    if (off == 0 || tgt >= rodataLimit || tgt < table + (half ? 2L * (i + 1) : (i + 1))) break;
                }
                if (tgt < CODE_START || tgt >= rodataLimit) { targets.clear(); break; }
                targets.add(tgt);
            }
            if (targets.isEmpty()) { log.add("FindMoreFunctions: D unresolved " + ins.getAddress() + " " + ins); continue; }
            for (long t : targets) {
                Address ta = toAddr(t);
                currentProgram.getReferenceManager().addMemoryReference(ins.getAddress(), ta, RefType.COMPUTED_JUMP, SourceType.ANALYSIS, 0);
                if (lst.getInstructionAt(ta) == null && lst.getDefinedDataContaining(ta) == null) {
                    try { currentProgram.getProgramContext().setValue(tmode, ta, ta, BigInteger.ONE); } catch (Exception e) { }
                    disassemble(ta);
                }
            }
            int tlen = half ? 2 * targets.size() : targets.size();
            Address tAddr = toAddr(table);
            if (lst.isUndefined(tAddr, tAddr.add(tlen - 1))) {
                try {
                    createData(tAddr, half ? new ArrayDataType(UnsignedShortDataType.dataType, targets.size(), 2)
                                           : new ArrayDataType(ByteDataType.dataType, targets.size(), 1));
                } catch (Exception e) { /* ignore */ }
            }
            Function f = lst.getFunctionContaining(ins.getAddress());
            if (f != null) CreateFunctionCmd.fixupFunctionBody(currentProgram, f, monitor);
            log.add(String.format("FindMoreFunctions: D %s @0x%08X table=0x%08X entries=%d (cmp-bound=%s) in %s",
                ins.getMnemonicString(), ins.getAddress().getOffset(), table, targets.size(), count > 0 ? "yes" : "probed",
                f == null ? "-" : f.getName()));
            n++; switchesD++;
        }
        return n;
    }

    // ---------------------------------------------------------------- Pass F
    // Unconditional jumps whose target is inside ANOTHER function's body (but not its entry)
    // are GCC tail calls / ICF thunks to a function that was never given an entry; create it.
    private int passTailTargets() throws Exception {
        Listing lst = currentProgram.getListing();
        AddressSet code = new AddressSet(toAddr(CODE_START), toAddr(rodataLimit - 1));
        List<Address> targets = new ArrayList<>();
        InstructionIterator iit = lst.getInstructions(code, true);
        while (iit.hasNext()) {
            Instruction ins = iit.next();
            if (!ins.getFlowType().isJump() || ins.getFlowType().isComputed()) continue;
            boolean uncond = !ins.getFlowType().isConditional();
            Function fx = lst.getFunctionContaining(ins.getAddress());
            for (Reference r : ins.getReferencesFrom()) {
                if (!r.getReferenceType().isJump()) continue;
                Address t = r.getToAddress();
                Function fy = lst.getFunctionContaining(t);
                if (fy == null || fy.getEntryPoint().equals(t)) continue;
                Instruction ti = lst.getInstructionAt(t);
                // rule 2: a branch target that is a push{..,lr}/push.w prologue is a function entry
                boolean prologue = ti != null && (ti.getMnemonicString().equals("push") && ti.toString().contains("lr"));
                if (prologue) { targets.add(t); continue; }
                if (!uncond) continue;
                if (fx != null && fx.getEntryPoint().equals(fy.getEntryPoint())) continue;   // intra-function jump
                targets.add(t);
            }
        }
        int n = 0;
        for (Address t : targets) {
            if (lst.getFunctionAt(t) != null) continue;
            Function fy = lst.getFunctionContaining(t);
            Function f = createFunction(t, null);
            if (f == null) { log.add(String.format("FindMoreFunctions: F failed at 0x%08X", t.getOffset())); continue; }
            if (fy != null) CreateFunctionCmd.fixupFunctionBody(currentProgram, fy, monitor);
            log.add(String.format("FindMoreFunctions: F 0x%08X size=%d (tail-call target carved out of %s)", t.getOffset(), f.getBody().getNumAddresses(), fy == null ? "-" : fy.getName()));
            n++; createdF++;
        }
        return n;
    }

    // ---------------------------------------------------------------- Pass C
    private int passGaps() throws Exception {
        Listing lst = currentProgram.getListing();
        AddressSet code = new AddressSet(toAddr(CODE_START), toAddr(rodataLimit - 1));
        AddressSet covered = new AddressSet();
        InstructionIterator iit = lst.getInstructions(code, true);
        while (iit.hasNext()) { Instruction i = iit.next(); covered.add(i.getMinAddress(), i.getMaxAddress()); }
        ghidra.program.model.listing.DataIterator dit = lst.getDefinedData(code, true);
        while (dit.hasNext()) { ghidra.program.model.listing.Data d = dit.next(); covered.add(d.getMinAddress(), d.getMaxAddress()); }
        AddressSetView undef = code.subtract(covered);
        int n = 0;
        for (AddressRange r : undef) {
            long a = r.getMinAddress().getOffset();
            long end = r.getMaxAddress().getOffset() + 1;
            if (a % 2 == 1) a++;
            while (a + 2 <= end) {
                int hw = getShort(toAddr(a)) & 0xFFFF;
                if (hw == 0x0000 || hw == 0xBF00 || hw == 0xFFFF) { a += 2; continue; }       // padding
                if (a % 4 == 0 && a + 4 <= end) {
                    long word = getInt(toAddr(a)) & 0xFFFFFFFFL;
                    boolean thunk = (hw & 0xF800) == 0xF000 && ((word >> 16) & 0x8000) != 0;   // bl / b.w
                    boolean referenced = currentProgram.getReferenceManager().hasReferencesTo(toAddr(a));
                    boolean flashPtr = word >= 0x08000000L && word < 0x08018000L;
                    if (!thunk && (referenced || flashPtr)) { a += 4; continue; }              // literal-pool word
                }
                int hw2 = a + 4 <= end ? (getShort(toAddr(a + 2)) & 0xFFFF) : 0;
                if (strictPrologue(hw, hw2) && !tried.contains(a) && lst.getFunctionContaining(toAddr(a)) == null) {
                    tried.add(a);
                    if (tryCreate(toAddr(a), "C", String.format("gap %s first=%04x", r, hw), true)) {
                        n++; createdC++;
                        Function nf = lst.getFunctionAt(toAddr(a));
                        if (nf != null && passSwitchTables(nf.getBody()) > 0) {
                            CreateFunctionCmd.fixupFunctionBody(currentProgram, nf, monitor);
                        }
                        break;   // the rest of this gap is re-evaluated next round
                    }
                }
                a += 2;
            }
        }
        return n;
    }

    // Thumb first-instruction shapes that start real functions in GCC output (strict set).
    static boolean strictPrologue(int hw, int hw2) {
        int hi = hw >> 8;
        if (hi == 0xB5 || hi == 0xB4) return true;                    // push {..}
        if (hw == 0xE92D) return true;                                // push.w
        if (hw == 0x4770) return true;                                // bx lr (empty weak fn)
        if ((hw & 0xF800) == 0xF000 && (hw2 & 0x8000) != 0) return true; // bl / b.w thunk
        if ((hw & 0xF500) == 0xB100) return true;                     // cbz / cbnz r?, ..
        if ((hw & 0xF800) == 0x4800) return true;                     // ldr rX, [pc, #imm]
        if ((hw & 0xF800) == 0x2800) return (hw2 & 0xF000) == 0xD000 && (hw2 & 0x0F00) != 0x0F00; // cmp rX,#imm ; b<cond>
        if ((hw & 0xFF00) == 0x4600) return (hw2 >> 8) == 0xB5 || (hw2 >> 8) == 0xB4;             // mov rX,rY ; push
        if ((hw & 0xF800) == 0x2000) {                                // movs rX, #imm: only as a tiny leaf
            return hw2 == 0x4770 || (hw2 & 0xFF00) == 0xBD00 || (hw2 & 0xF800) == 0xE000;
        }
        if ((hw & 0xFFF0) == 0xF8D0 || (hw & 0xFFF0) == 0xF890 || (hw & 0xFFF0) == 0xF8B0) return true; // ldr.w/ldrb.w/ldrh.w
        if ((hw & 0xFBF0) == 0xF240 || (hw & 0xFBF0) == 0xF2C0) return true; // movw / movt
        if ((hw & 0xFF80) == 0xB080) return true;                     // sub sp, #imm
        return false;
    }

    // ---------------------------------------------------------------- Pass G
    // A function owning a resolved tbb/tbh switch: fragment "functions" inside its span
    // (case bodies / shared return blocks created before the owner existed) are removed so
    // the owner's body can be recomputed over them. A fragment = entry with no CALL-type
    // reference, not a push/push.w prologue, not a vector/pointer-table target.
    private boolean isRealEntry(Function g, Function owner) {
        Listing lst = currentProgram.getListing();
        Instruction fi = lst.getInstructionAt(g.getEntryPoint());
        if (fi != null && (fi.getMnemonicString().equals("push") || fi.getMnemonicString().equals("push.w"))) return true;
        long lo = owner.getEntryPoint().getOffset(), hi = g.getEntryPoint().getOffset();
        StringBuilder why = new StringBuilder();
        ghidra.program.model.symbol.ReferenceIterator it = currentProgram.getReferenceManager().getReferencesTo(g.getEntryPoint());
        while (it.hasNext()) {
            Reference r = it.next();
            long from = r.getFromAddress().getOffset();
            why.append(String.format(" %s@%08X", r.getReferenceType().getName(), from));
            if (r.getReferenceType().isCall()) {
                // Shared-Return analysis turns 'b <entry>' into CALL refs: only a real bl/blx counts
                Instruction ci = lst.getInstructionAt(r.getFromAddress());
                if (ci != null && ci.getMnemonicString().startsWith("bl")) return true;
                continue;
            }
            // a DATA ref from the owner's own span is the tbb/tbh byte table, not a pointer table
            if (r.getReferenceType().isData() && !(from >= lo && from < hi) && !owner.getBody().contains(r.getFromAddress())) return true;
        }
        log.add(String.format("FindMoreFunctions: G candidate 0x%08X first=%s refs:%s", hi, fi == null ? "?" : fi.getMnemonicString(), why));
        return false;
    }

    private int passAbsorbSwitchFragments() throws Exception {
        Listing lst = currentProgram.getListing();
        AddressSet code = new AddressSet(toAddr(CODE_START), toAddr(rodataLimit - 1));
        int n = 0;
        List<Function> owners = new ArrayList<>();
        InstructionIterator iit = lst.getInstructions(code, true);
        while (iit.hasNext()) {
            Instruction ins = iit.next();
            String m = ins.getMnemonicString();
            if (!m.equals("tbb") && !m.equals("tbh")) continue;
            Function f = lst.getFunctionContaining(ins.getAddress());
            if (f != null && !owners.contains(f)) owners.add(f);
        }
        for (Function f : owners) {
            // span end = next real entry after f
            Address start = f.getEntryPoint();
            Address end = toAddr(rodataLimit);
            FunctionIterator after = currentProgram.getFunctionManager().getFunctions(start.add(1), true);
            List<Function> frags = new ArrayList<>();
            while (after.hasNext()) {
                Function g = after.next();
                if (g.getEntryPoint().getOffset() >= end.getOffset()) break;
                if (isRealEntry(g, f)) { end = g.getEntryPoint(); break; }
                frags.add(g);
            }
            if (frags.isEmpty()) continue;
            for (Function g : frags) {
                log.add(String.format("FindMoreFunctions: G absorbed fragment 0x%08X size=%d into %s", g.getEntryPoint().getOffset(), g.getBody().getNumAddresses(), f.getName()));
                currentProgram.getFunctionManager().removeFunction(g.getEntryPoint());
                n++; absorbedG++;
            }
            CreateFunctionCmd.fixupFunctionBody(currentProgram, f, monitor);
            // fallback: any instruction inside the span that still belongs to no function is a
            // switch-case / shared-return block of f -> add it to f's body explicitly
            AddressSet span = new AddressSet(start, end.subtract(1));
            AddressSet orphan = new AddressSet();
            InstructionIterator si = lst.getInstructions(span, true);
            while (si.hasNext()) {
                Instruction i = si.next();
                if (lst.getFunctionContaining(i.getAddress()) == null) orphan.add(i.getMinAddress(), i.getMaxAddress());
            }
            if (!orphan.isEmpty()) {
                try {
                    f.setBody(f.getBody().union(orphan));
                    log.add(String.format("FindMoreFunctions: G added %d orphan bytes to %s body", orphan.getNumAddresses(), f.getName()));
                } catch (Exception ex) {
                    log.add("FindMoreFunctions: G setBody failed for " + f.getName() + ": " + ex.getMessage());
                }
            }
            log.add(String.format("FindMoreFunctions: G owner 0x%08X %s body now %d bytes, span end 0x%08X", f.getEntryPoint().getOffset(), f.getName(), f.getBody().getNumAddresses(), end.getOffset()));
        }
        return n;
    }

    // ---------------------------------------------------------------- Pass E
    private int passFixupBodies() throws Exception {
        int n = 0;
        List<Function> all = new ArrayList<>();
        FunctionIterator fit = currentProgram.getFunctionManager().getFunctions(true);
        while (fit.hasNext()) all.add(fit.next());
        for (Function f : all) {
            AddressSetView body = f.getBody();
            boolean swallowed = false;
            FunctionIterator inner = currentProgram.getFunctionManager().getFunctions(body, true);
            while (inner.hasNext()) {
                Function g = inner.next();
                if (!g.getEntryPoint().equals(f.getEntryPoint())) { swallowed = true; break; }
            }
            if (!swallowed) continue;
            long sizeBefore = body.getNumAddresses();
            CreateFunctionCmd.fixupFunctionBody(currentProgram, f, monitor);
            long sizeAfter = f.getBody().getNumAddresses();
            if (sizeAfter != sizeBefore) {
                log.add(String.format("FindMoreFunctions: E fixup 0x%08X %s size %d -> %d", f.getEntryPoint().getOffset(), f.getName(), sizeBefore, sizeAfter));
                n++; fixedE++;
            }
        }
        return n;
    }

    // ---------------------------------------------------------------- cleanup
    private int cleanupRodata() throws Exception {
        Listing lst = currentProgram.getListing();
        AddressSet ro = new AddressSet(toAddr(rodataLimit), toAddr(CODE_END - 1));
        int n = 0;
        List<Function> junk = new ArrayList<>();
        FunctionIterator fit = currentProgram.getFunctionManager().getFunctions(ro, true);
        while (fit.hasNext()) junk.add(fit.next());
        for (Function f : junk) {
            log.add(String.format("FindMoreFunctions: CLEANUP removed function 0x%08X size=%d (inside rodata)",
                f.getEntryPoint().getOffset(), f.getBody().getNumAddresses()));
            currentProgram.getFunctionManager().removeFunction(f.getEntryPoint());
            n++;
        }
        AddressSet insns = new AddressSet();
        InstructionIterator iit = lst.getInstructions(ro, true);
        while (iit.hasNext()) { Instruction i = iit.next(); insns.add(i.getMinAddress(), i.getMaxAddress()); }
        for (AddressRange r : insns) {
            log.add(String.format("FindMoreFunctions: CLEANUP cleared instructions 0x%08X..0x%08X", r.getMinAddress().getOffset(), r.getMaxAddress().getOffset()));
            clearListing(r.getMinAddress(), r.getMaxAddress());
            n++;
        }
        println("FindMoreFunctions: cleanup removed " + junk.size() + " functions and " + insns.getNumAddressRanges() + " instruction ranges >= 0x" + Long.toHexString(rodataLimit));
        return n;
    }
}
