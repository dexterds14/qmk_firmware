// ExportFunctions.java -- POST-analysis: one CSV row per function.
// Columns: entry,size,name,n_callers,n_callees,is_thunk,signature,strings
//   strings = string literals referenced from the body ("|"-separated, quotes doubled),
//   either directly or through a pointer word in a literal pool.
// Arg 0 = output directory (writes ghidra_functions.csv).
//@category Keychron
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.listing.Listing;
import ghidra.program.model.symbol.Reference;

import java.io.File;
import java.io.PrintWriter;
import java.util.LinkedHashSet;
import java.util.Set;

public class ExportFunctions extends GhidraScript {

    @Override
    protected void run() throws Exception {
        String outDir = getScriptArgs().length > 0 ? getScriptArgs()[0] : ".";
        Listing lst = currentProgram.getListing();
        File out = new File(outDir, "ghidra_functions.csv");
        int n = 0;
        try (PrintWriter w = new PrintWriter(out)) {
            w.println("entry,size,name,n_callers,n_callees,is_thunk,signature,strings");
            FunctionIterator fit = currentProgram.getFunctionManager().getFunctions(true);
            while (fit.hasNext()) {
                Function f = fit.next();
                Set<String> strs = new LinkedHashSet<>();
                InstructionIterator iit = lst.getInstructions(f.getBody(), true);
                while (iit.hasNext()) {
                    Instruction ins = iit.next();
                    for (Reference r : ins.getReferencesFrom()) {
                        addStringAt(lst, r.getToAddress(), strs, 0);
                    }
                }
                StringBuilder sb = new StringBuilder();
                for (String s : strs) {
                    if (sb.length() > 0) sb.append(" | ");
                    sb.append(s);
                }
                w.println(String.format("0x%08X,%d,%s,%d,%d,%s,%s,%s",
                    f.getEntryPoint().getOffset(), f.getBody().getNumAddresses(), csv(f.getName()),
                    f.getCallingFunctions(monitor).size(), f.getCalledFunctions(monitor).size(),
                    f.isThunk() ? "1" : "0", csv(f.getPrototypeString(false, false)), csv(sb.toString())));
                n++;
            }
        }
        println("ExportFunctions: " + n + " functions -> " + out);
    }

    private void addStringAt(Listing lst, Address a, Set<String> strs, int depth) {
        if (a == null || depth > 1) return;
        Data d = lst.getDataContaining(a);
        if (d == null) return;
        if (d.hasStringValue()) {
            Object v = d.getValue();
            if (v != null) strs.add(String.format("%08X:%s", d.getAddress().getOffset(), v.toString()));
            return;
        }
        if (d.isPointer()) {
            Object v = d.getValue();
            if (v instanceof Address) addStringAt(lst, (Address) v, strs, depth + 1);
        }
    }

    static String csv(String s) {
        if (s == null) return "";
        s = s.replace("\r", "\\r").replace("\n", "\\n");
        if (s.indexOf(',') >= 0 || s.indexOf('"') >= 0 || s.indexOf(' ') >= 0) {
            return "\"" + s.replace("\"", "\"\"") + "\"";
        }
        return s;
    }
}
