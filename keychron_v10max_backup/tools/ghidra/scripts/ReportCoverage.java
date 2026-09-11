// ReportCoverage.java -- POST-analysis: how much of the code region 0x08008000..0x08017F04
// is covered by defined functions / instructions / data, and where the undefined gaps are.
// Arg 0 = output directory (writes ghidra_coverage.txt).
//@category Keychron
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressRange;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.address.AddressSetView;
import ghidra.program.model.listing.Data;
import ghidra.program.model.listing.DataIterator;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.listing.Listing;

import java.io.File;
import java.io.PrintWriter;

public class ReportCoverage extends GhidraScript {
    static final long CODE_START = 0x08008000L;
    static final long CODE_END = 0x08017F04L;

    @Override
    protected void run() throws Exception {
        String outDir = getScriptArgs().length > 0 ? getScriptArgs()[0] : ".";
        Listing lst = currentProgram.getListing();
        AddressSet code = new AddressSet(toAddr(CODE_START), toAddr(CODE_END - 1));
        long total = code.getNumAddresses();

        AddressSet fnSet = new AddressSet();
        int nFn = 0, nFnInCode = 0, nThunk = 0;
        FunctionIterator fit = currentProgram.getFunctionManager().getFunctions(true);
        while (fit.hasNext()) {
            Function f = fit.next();
            nFn++;
            if (f.isThunk()) nThunk++;
            if (code.contains(f.getEntryPoint())) nFnInCode++;
            fnSet.add(f.getBody());
        }
        long fnBytes = code.intersect(fnSet).getNumAddresses();

        AddressSet insSet = new AddressSet();
        long insBytes = 0; int nIns = 0;
        InstructionIterator iit = lst.getInstructions(code, true);
        while (iit.hasNext()) {
            Instruction i = iit.next();
            insBytes += i.getLength(); nIns++;
            insSet.add(i.getMinAddress(), i.getMaxAddress());
        }
        AddressSet dataSet = new AddressSet();
        long dataBytes = 0; int nData = 0;
        DataIterator dit = lst.getDefinedData(code, true);
        while (dit.hasNext()) {
            Data d = dit.next();
            dataBytes += d.getLength(); nData++;
            dataSet.add(d.getMinAddress(), d.getMaxAddress());
        }
        AddressSetView covered = insSet.union(dataSet);
        AddressSetView undef = code.subtract(covered);
        AddressSetView insOutsideFn = insSet.subtract(fnSet);

        File out = new File(outDir, "ghidra_coverage.txt");
        try (PrintWriter w = new PrintWriter(out)) {
            String hdr = String.format(
                "Ghidra coverage of code region 0x%08X..0x%08X (%d bytes)\n" +
                "functions total=%d (thunks=%d) with entry in code region=%d\n" +
                "bytes inside function bodies : %d (%.2f%%)\n" +
                "bytes as instructions        : %d (%.2f%%)  [%d instructions]\n" +
                "bytes as defined data        : %d (%.2f%%)  [%d data items]\n" +
                "bytes undefined              : %d (%.2f%%)\n" +
                "instruction bytes outside any function: %d\n",
                CODE_START, CODE_END, total, nFn, nThunk, nFnInCode,
                fnBytes, 100.0 * fnBytes / total,
                insBytes, 100.0 * insBytes / total, nIns,
                dataBytes, 100.0 * dataBytes / total, nData,
                undef.getNumAddresses(), 100.0 * undef.getNumAddresses() / total,
                insOutsideFn.getNumAddresses());
            w.print(hdr);
            println(hdr);
            w.println("\nUndefined gaps >= 8 bytes (start, length, first 8 bytes hex):");
            for (AddressRange r : undef) {
                long len = r.getLength();
                if (len < 8) continue;
                StringBuilder hex = new StringBuilder();
                for (int k = 0; k < Math.min(8, len); k++) {
                    hex.append(String.format("%02x", getByte(r.getMinAddress().add(k)) & 0xff));
                }
                w.println(String.format("  0x%08X %6d %s", r.getMinAddress().getOffset(), len, hex));
            }
            w.println("\nInstruction ranges outside any function:");
            for (AddressRange r : insOutsideFn) {
                w.println(String.format("  0x%08X %6d", r.getMinAddress().getOffset(), r.getLength()));
            }
        }
        println("ReportCoverage: wrote " + out);
    }
}
