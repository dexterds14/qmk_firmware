// ExportDecompiled.java -- POST-analysis: decompile EVERY function to C.
// Writes <outdir>/decompiled/<addr>_<name>.c (one file per function), plus
// <outdir>/decompiled/_ALL.c (concatenation, for grep) and _INDEX.csv (addr,name,file,status).
// Arg 0 = output directory.
//@category Keychron
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileOptions;
import ghidra.app.decompiler.DecompileResults;
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;

import java.io.File;
import java.io.PrintWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;

public class ExportDecompiled extends GhidraScript {

    @Override
    protected void run() throws Exception {
        String outDir = getScriptArgs().length > 0 ? getScriptArgs()[0] : ".";
        File dir = new File(outDir, "decompiled");
        dir.mkdirs();
        // remove stale output from earlier runs (names change between runs)
        File[] stale = dir.listFiles();
        if (stale != null) for (File sf : stale) if (sf.getName().endsWith(".c") || sf.getName().endsWith(".csv")) sf.delete();

        DecompInterface decomp = new DecompInterface();
        DecompileOptions opts = new DecompileOptions();
        opts.setCommentStyle(DecompileOptions.CommentStyleEnum.CPPStyle);
        decomp.setOptions(opts);
        decomp.toggleCCode(true);
        decomp.toggleSyntaxTree(false);
        decomp.setSimplificationStyle("decompile");
        if (!decomp.openProgram(currentProgram)) {
            throw new Exception("decompiler failed to open program: " + decomp.getLastMessage());
        }

        int ok = 0, fail = 0;
        try (PrintWriter all = new PrintWriter(new File(dir, "_ALL.c"), "UTF-8");
             PrintWriter idx = new PrintWriter(new File(dir, "_INDEX.csv"), "UTF-8")) {
            idx.println("addr,name,size,file,status");
            FunctionIterator fit = currentProgram.getFunctionManager().getFunctions(true);
            while (fit.hasNext() && !monitor.isCancelled()) {
                Function f = fit.next();
                String addr = String.format("%08x", f.getEntryPoint().getOffset());
                String safe = f.getName().replaceAll("[^A-Za-z0-9_.]", "_");
                String fname = addr + "_" + safe + ".c";
                String status;
                StringBuilder body = new StringBuilder();
                body.append("// ").append(f.getName()).append(" @ 0x").append(addr)
                    .append("  size=").append(f.getBody().getNumAddresses())
                    .append("  body=").append(f.getBody().toString()).append("\n");
                try {
                    DecompileResults res = decomp.decompileFunction(f, 90, monitor);
                    if (res != null && res.decompileCompleted() && res.getDecompiledFunction() != null) {
                        body.append(res.getDecompiledFunction().getC());
                        status = "ok"; ok++;
                    } else {
                        body.append("// DECOMPILE FAILED: ").append(res == null ? "null" : res.getErrorMessage()).append("\n");
                        status = "fail"; fail++;
                    }
                } catch (Exception e) {
                    body.append("// DECOMPILE EXCEPTION: ").append(e).append("\n");
                    status = "exception"; fail++;
                }
                Files.write(new File(dir, fname).toPath(), body.toString().getBytes(StandardCharsets.UTF_8));
                all.println("// ===================================================================");
                all.print(body);
                all.println();
                idx.println(String.format("0x%08X,%s,%d,%s,%s", f.getEntryPoint().getOffset(),
                    f.getName(), f.getBody().getNumAddresses(), fname, status));
            }
        } finally {
            decomp.dispose();
        }
        println("ExportDecompiled: ok=" + ok + " failed=" + fail + " -> " + dir);
    }
}
