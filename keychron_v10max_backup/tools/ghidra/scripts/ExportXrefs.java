// ExportXrefs.java -- POST-analysis: who references the keymaps table and the rodata region.
// Output ghidra_xrefs.json with:
//  keymaps_addr           : 0x080169B8
//  direct_refs            : Ghidra references whose target is inside keymaps[] (1296 bytes)
//  literal_words          : every 4-byte-aligned word in the code region whose value points
//                           inside keymaps[] (literal-pool constants), with the instructions
//                           that read that word and their functions
//  functions_referencing_keymaps : union of the above, by function
//  rodata_refs            : all references from code into 0x08016000..0x08017F04 grouped by target
// Arg 0 = output directory.
//@category Keychron
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Listing;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;
import ghidra.program.model.symbol.ReferenceManager;

import java.io.File;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.TreeMap;
import java.util.TreeSet;

public class ExportXrefs extends GhidraScript {
    static final long CODE_START = 0x08008000L;
    static final long CODE_END = 0x08017F04L;
    static final long RODATA_START = 0x08016000L;
    static final long KEYMAPS = 0x080169B8L;
    static final long KEYMAPS_LEN = 6 * 6 * 18 * 2;   // 1296

    @Override
    protected void run() throws Exception {
        String outDir = getScriptArgs().length > 0 ? getScriptArgs()[0] : ".";
        Listing lst = currentProgram.getListing();
        ReferenceManager rm = currentProgram.getReferenceManager();
        TreeMap<Long, String> fnsRefKeymaps = new TreeMap<>();

        // 1. direct references to any address inside keymaps[]
        List<String> direct = new ArrayList<>();
        for (long a = KEYMAPS; a < KEYMAPS + KEYMAPS_LEN; a++) {
            ReferenceIterator it = rm.getReferencesTo(toAddr(a));
            while (it.hasNext()) {
                Reference r = it.next();
                Function f = lst.getFunctionContaining(r.getFromAddress());
                direct.add(String.format("  {\"to\":\"0x%08X\",\"from\":\"0x%08X\",\"from_fn\":%s,\"type\":\"%s\",\"from_is_code\":%s}",
                    a, r.getFromAddress().getOffset(), fnJson(f), r.getReferenceType().getName(),
                    lst.getInstructionAt(r.getFromAddress()) != null ? "true" : "false"));
                if (f != null) fnsRefKeymaps.put(f.getEntryPoint().getOffset(), f.getName());
                // a literal-pool word referencing keymaps: find who reads the word
                if (lst.getInstructionAt(r.getFromAddress()) == null) {
                    ReferenceIterator it2 = rm.getReferencesTo(r.getFromAddress());
                    while (it2.hasNext()) {
                        Function f2 = lst.getFunctionContaining(it2.next().getFromAddress());
                        if (f2 != null) fnsRefKeymaps.put(f2.getEntryPoint().getOffset(), f2.getName());
                    }
                }
            }
        }

        // 2. raw scan of literal-pool words
        List<String> words = new ArrayList<>();
        for (long a = CODE_START; a + 4 <= CODE_END; a += 4) {
            long v = getInt(toAddr(a)) & 0xFFFFFFFFL;
            if (v < KEYMAPS || v >= KEYMAPS + KEYMAPS_LEN) continue;
            StringBuilder readers = new StringBuilder();
            ReferenceIterator it = rm.getReferencesTo(toAddr(a));
            while (it.hasNext()) {
                Reference r = it.next();
                Function f = lst.getFunctionContaining(r.getFromAddress());
                if (readers.length() > 0) readers.append(",");
                readers.append(String.format("{\"from\":\"0x%08X\",\"fn\":%s,\"type\":\"%s\"}",
                    r.getFromAddress().getOffset(), fnJson(f), r.getReferenceType().getName()));
                if (f != null) fnsRefKeymaps.put(f.getEntryPoint().getOffset(), f.getName());
            }
            Function inside = lst.getFunctionContaining(toAddr(a));
            if (inside != null) fnsRefKeymaps.putIfAbsent(inside.getEntryPoint().getOffset(), inside.getName());
            words.add(String.format("  {\"word_addr\":\"0x%08X\",\"value\":\"0x%08X\",\"offset_in_keymaps\":%d,\"inside_fn\":%s,\"readers\":[%s]}",
                a, v, v - KEYMAPS, fnJson(inside), readers));
        }

        // 3. all refs into rodata region grouped by target
        TreeMap<Long, List<String>> rodata = new TreeMap<>();
        for (long a = RODATA_START; a < CODE_END; a++) {
            ReferenceIterator it = rm.getReferencesTo(toAddr(a));
            while (it.hasNext()) {
                Reference r = it.next();
                Function f = lst.getFunctionContaining(r.getFromAddress());
                Data d = lst.getDataContaining(toAddr(a));
                rodata.computeIfAbsent(a, k -> new ArrayList<>()).add(String.format(
                    "{\"from\":\"0x%08X\",\"fn\":%s,\"type\":\"%s\",\"data\":\"%s\"}",
                    r.getFromAddress().getOffset(), fnJson(f), r.getReferenceType().getName(),
                    d == null ? "" : esc(d.getDataType().getName() + " " + d.getDefaultValueRepresentation())));
            }
        }

        File out = new File(outDir, "ghidra_xrefs.json");
        try (PrintWriter w = new PrintWriter(out)) {
            w.println("{");
            w.println(String.format("\"keymaps_addr\":\"0x%08X\",\"keymaps_len\":%d,", KEYMAPS, KEYMAPS_LEN));
            w.println("\"direct_refs\":[\n" + String.join(",\n", direct) + "\n],");
            w.println("\"literal_words\":[\n" + String.join(",\n", words) + "\n],");
            w.println("\"functions_referencing_keymaps\":[");
            int i = 0;
            for (java.util.Map.Entry<Long, String> e : fnsRefKeymaps.entrySet()) {
                if (i++ > 0) w.println(",");
                w.print(String.format("  {\"addr\":\"0x%08X\",\"name\":\"%s\"}", e.getKey(), esc(e.getValue())));
            }
            w.println("\n],");
            w.println("\"rodata_refs\":{");
            i = 0;
            for (java.util.Map.Entry<Long, List<String>> e : rodata.entrySet()) {
                if (i++ > 0) w.println(",");
                w.print(String.format("  \"0x%08X\":[%s]", e.getKey(), String.join(",", e.getValue())));
            }
            w.println("\n}\n}");
        }
        println("ExportXrefs: direct=" + direct.size() + " literal_words=" + words.size() +
            " fns_ref_keymaps=" + fnsRefKeymaps.size() + " rodata_targets=" + rodata.size() + " -> " + out);
        for (java.util.Map.Entry<Long, String> e : fnsRefKeymaps.entrySet()) {
            println(String.format("ExportXrefs:   keymaps referenced by 0x%08X %s", e.getKey(), e.getValue()));
        }
    }

    static String fnJson(Function f) {
        if (f == null) return "null";
        return String.format("{\"addr\":\"0x%08X\",\"name\":\"%s\"}", f.getEntryPoint().getOffset(), esc(f.getName()));
    }

    static String esc(String s) {
        if (s == null) return "";
        StringBuilder b = new StringBuilder();
        for (char c : s.toCharArray()) {
            switch (c) {
                case '"': b.append("\\\""); break;
                case '\\': b.append("\\\\"); break;
                case '\n': b.append("\\n"); break;
                case '\r': b.append("\\r"); break;
                case '\t': b.append("\\t"); break;
                default:
                    if (c < 0x20 || c > 0x7e) b.append(String.format("\\u%04x", (int) c)); else b.append(c);
            }
        }
        return b.toString();
    }
}
