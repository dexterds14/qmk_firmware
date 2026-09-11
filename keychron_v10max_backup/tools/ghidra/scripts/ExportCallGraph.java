// ExportCallGraph.java -- POST-analysis: caller->callee edges as JSON.
// {"nodes":[{"addr","name","size"}], "edges":[{"from","from_name","to","to_name","sites":[...],"tail":bool}],
//  "indirect_call_sites":[{"fn","fn_name","at"}]}
// An edge is recorded for every CALL reference (bl/blx) and for unconditional JUMPs that
// leave the caller's body and land on another function's entry (tail calls / thunks).
// Arg 0 = output directory (writes ghidra_callgraph.json).
//@category Keychron
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.listing.FunctionManager;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.listing.Listing;
import ghidra.program.model.symbol.FlowType;
import ghidra.program.model.symbol.RefType;
import ghidra.program.model.symbol.Reference;

import java.io.File;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.TreeMap;

public class ExportCallGraph extends GhidraScript {

    static class Edge {
        Function from, to; boolean tail; List<Long> sites = new ArrayList<>();
    }

    @Override
    protected void run() throws Exception {
        String outDir = getScriptArgs().length > 0 ? getScriptArgs()[0] : ".";
        Listing lst = currentProgram.getListing();
        FunctionManager fm = currentProgram.getFunctionManager();
        TreeMap<String, Edge> edges = new TreeMap<>();
        List<String> indirect = new ArrayList<>();
        StringBuilder nodes = new StringBuilder();
        int nNodes = 0;

        FunctionIterator fit = fm.getFunctions(true);
        while (fit.hasNext()) {
            Function f = fit.next();
            if (nNodes++ > 0) nodes.append(",\n");
            nodes.append(String.format("  {\"addr\":\"0x%08X\",\"name\":\"%s\",\"size\":%d,\"thunk\":%s}",
                f.getEntryPoint().getOffset(), esc(f.getName()), f.getBody().getNumAddresses(),
                f.isThunk() ? "true" : "false"));
            InstructionIterator iit = lst.getInstructions(f.getBody(), true);
            while (iit.hasNext()) {
                Instruction ins = iit.next();
                FlowType ft = ins.getFlowType();
                boolean sawTarget = false;
                for (Reference r : ins.getReferencesFrom()) {
                    RefType rt = r.getReferenceType();
                    boolean isCall = rt.isCall();
                    boolean isTail = rt.isJump() && !f.getBody().contains(r.getToAddress());
                    if (!isCall && !isTail) continue;
                    Function callee = fm.getFunctionAt(r.getToAddress());
                    if (callee == null) {
                        // pointer-mediated call (e.g. via a literal pool word): resolve the data
                        Function inside = fm.getFunctionContaining(r.getToAddress());
                        if (inside != null && isTail) continue;  // jump into another body: not a call
                        if (inside == null) continue;
                        callee = inside;
                    }
                    sawTarget = true;
                    String key = f.getEntryPoint() + "->" + callee.getEntryPoint() + (isTail ? "T" : "C");
                    Edge e = edges.get(key);
                    if (e == null) { e = new Edge(); e.from = f; e.to = callee; e.tail = isTail; edges.put(key, e); }
                    e.sites.add(ins.getAddress().getOffset());
                }
                if (!sawTarget && ft.isCall() && ft.isComputed()) {
                    indirect.add(String.format("  {\"fn\":\"0x%08X\",\"fn_name\":\"%s\",\"at\":\"0x%08X\",\"insn\":\"%s\"}",
                        f.getEntryPoint().getOffset(), esc(f.getName()), ins.getAddress().getOffset(), esc(ins.toString())));
                }
            }
        }

        File out = new File(outDir, "ghidra_callgraph.json");
        try (PrintWriter w = new PrintWriter(out)) {
            w.println("{\n\"program\":\"" + esc(currentProgram.getName()) + "\",");
            w.println("\"nodes\":[");
            w.print(nodes);
            w.println("\n],");
            w.println("\"edges\":[");
            int i = 0;
            for (Edge e : edges.values()) {
                if (i++ > 0) w.println(",");
                StringBuilder s = new StringBuilder();
                for (Long a : e.sites) { if (s.length() > 0) s.append(","); s.append(String.format("\"0x%08X\"", a)); }
                w.print(String.format("  {\"from\":\"0x%08X\",\"from_name\":\"%s\",\"to\":\"0x%08X\",\"to_name\":\"%s\",\"tail\":%s,\"sites\":[%s]}",
                    e.from.getEntryPoint().getOffset(), esc(e.from.getName()),
                    e.to.getEntryPoint().getOffset(), esc(e.to.getName()), e.tail ? "true" : "false", s));
            }
            w.println("\n],");
            w.println("\"indirect_call_sites\":[");
            w.println(String.join(",\n", indirect));
            w.println("]\n}");
        }
        println("ExportCallGraph: " + nNodes + " nodes, " + edges.size() + " edges, " + indirect.size() +
            " indirect call sites -> " + out);
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
