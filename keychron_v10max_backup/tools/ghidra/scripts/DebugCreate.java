// DebugCreate.java -- diagnose why a function could not be created at the given addresses.
// Args: one or more hex addresses. Prints listing state, tries disassemble + createFunction,
// reports the result and any error bookmarks nearby. Meant to be run with -readOnly.
//@category Keychron
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Bookmark;
import ghidra.program.model.listing.BookmarkType;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.Listing;

import java.util.Iterator;

public class DebugCreate extends GhidraScript {
    @Override
    protected void run() throws Exception {
        Listing lst = currentProgram.getListing();
        for (String s : getScriptArgs()) {
            Address a = toAddr(Long.parseLong(s.replace("0x", ""), 16));
            println("== " + a);
            println("  instructionAt=" + lst.getInstructionAt(a) + " dataContaining=" + lst.getDefinedDataContaining(a) +
                " fnAt=" + lst.getFunctionAt(a) + " fnContaining=" + lst.getFunctionContaining(a));
            println("  TMode=" + currentProgram.getProgramContext().getValue(
                currentProgram.getProgramContext().getRegister("TMode"), a, false));
            if (lst.getInstructionAt(a) == null) {
                boolean ok = disassemble(a);
                println("  disassemble -> " + ok + " instructionAt=" + lst.getInstructionAt(a));
            }
            Instruction ins = lst.getInstructionAt(a);
            int k = 0;
            while (ins != null && k++ < 12) { println("    " + ins.getAddress() + "  " + ins); ins = ins.getNext(); }
            Function f = createFunction(a, null);
            println("  createFunction -> " + (f == null ? "null" : f.getName() + " body=" + f.getBody()));
            Iterator<Bookmark> it = currentProgram.getBookmarkManager().getBookmarksIterator(BookmarkType.ERROR);
            while (it.hasNext()) {
                Bookmark b = it.next();
                long d = b.getAddress().getOffset() - a.getOffset();
                if (d >= -16 && d <= 128) println("  ERROR bookmark " + b.getAddress() + ": " + b.getComment());
            }
        }
    }
}
