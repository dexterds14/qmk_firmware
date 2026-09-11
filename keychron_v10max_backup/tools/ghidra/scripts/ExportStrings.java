// ExportStrings.java -- POST-analysis: every defined string with its cross-references.
// Writes ghidra_strings.csv: addr,len,type,value,xrefs
//   xrefs = "from@fn" entries separated by " | " (from = referencing address; for a
//   pointer word in a literal pool the readers of that word are listed too).
// Arg 0 = output directory.
//@category Keychron
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.DataIterator;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Listing;
import ghidra.program.model.symbol.Reference;
import ghidra.program.model.symbol.ReferenceIterator;
import ghidra.program.model.symbol.ReferenceManager;

import java.io.File;
import java.io.PrintWriter;
import java.util.LinkedHashSet;
import java.util.Set;

public class ExportStrings extends GhidraScript {

    @Override
    protected void run() throws Exception {
        String outDir = getScriptArgs().length > 0 ? getScriptArgs()[0] : ".";
        Listing lst = currentProgram.getListing();
        ReferenceManager rm = currentProgram.getReferenceManager();
        File out = new File(outDir, "ghidra_strings.csv");
        int n = 0;
        try (PrintWriter w = new PrintWriter(out)) {
            w.println("addr,len,type,value,xrefs");
            DataIterator it = lst.getDefinedData(true);
            while (it.hasNext()) {
                Data d = it.next();
                if (!d.hasStringValue()) continue;
                Set<String> xr = new LinkedHashSet<>();
                collect(rm, lst, d.getAddress(), xr, 0);
                // also refs to any interior byte (offcut refs)
                for (long a = d.getAddress().getOffset() + 1; a < d.getAddress().getOffset() + d.getLength(); a++) {
                    collect(rm, lst, toAddr(a), xr, 0);
                }
                Object v = d.getValue();
                w.println(String.format("0x%08X,%d,%s,%s,%s", d.getAddress().getOffset(), d.getLength(),
                    d.getDataType().getName(), csv(v == null ? "" : v.toString()),
                    csv(String.join(" | ", xr))));
                n++;
            }
        }
        println("ExportStrings: " + n + " strings -> " + out);
    }

    private void collect(ReferenceManager rm, Listing lst, Address a, Set<String> xr, int depth) {
        if (depth > 1) return;
        ReferenceIterator it = rm.getReferencesTo(a);
        while (it.hasNext()) {
            Reference r = it.next();
            Address from = r.getFromAddress();
            Function f = lst.getFunctionContaining(from);
            xr.add(String.format("%08X@%s", from.getOffset(), f == null ? "-" : f.getName()));
            if (lst.getInstructionAt(from) == null) {
                collect(rm, lst, from, xr, depth + 1);   // literal-pool pointer word: who reads it
            }
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
