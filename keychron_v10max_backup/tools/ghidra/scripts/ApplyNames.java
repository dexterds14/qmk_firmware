// ApplyNames.java -- apply evidence-backed names from a CSV to the analysed program.
// CSV columns: addr,kind,name,evidence     (kind = func | label | thunk_target)
//   func   : ensure a function exists at addr (disassemble/create if needed), rename it,
//            and attach the evidence text as a plate comment
//   label  : create a primary label at addr (data/variables) with an EOL comment
// Lines starting with '#' and blank lines are ignored. Arg 0 = CSV path.
//@category Keychron
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.CodeUnit;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Listing;
import ghidra.program.model.symbol.SourceType;

import java.io.BufferedReader;
import java.io.FileReader;
import java.math.BigInteger;

public class ApplyNames extends GhidraScript {

    @Override
    protected void run() throws Exception {
        if (getScriptArgs().length < 1) throw new Exception("usage: ApplyNames.java <names.csv>");
        Listing lst = currentProgram.getListing();
        int nf = 0, nl = 0;
        try (BufferedReader br = new BufferedReader(new FileReader(getScriptArgs()[0]))) {
            String line;
            while ((line = br.readLine()) != null) {
                line = line.trim();
                if (line.isEmpty() || line.startsWith("#") || line.startsWith("addr,")) continue;
                String[] p = line.split(",", 4);
                if (p.length < 3) continue;
                Address a = toAddr(Long.parseLong(p[0].trim().replace("0x", ""), 16));
                String kind = p[1].trim(), name = p[2].trim();
                String evidence = p.length > 3 ? p[3].trim() : "";
                if (kind.equals("func")) {
                    Function f = lst.getFunctionAt(a);
                    if (f == null) {
                        if (lst.getInstructionAt(a) == null) {
                            try {
                                currentProgram.getProgramContext().setValue(
                                    currentProgram.getProgramContext().getRegister("TMode"), a, a, BigInteger.ONE);
                            } catch (Exception e) { /* ignore */ }
                            disassemble(a);
                        }
                        f = createFunction(a, name);
                        if (f == null) { println("ApplyNames: could not create function at " + a); continue; }
                    }
                    f.setName(name, SourceType.USER_DEFINED);
                    if (!evidence.isEmpty()) lst.setComment(a, CodeUnit.PLATE_COMMENT, evidence);
                    nf++;
                } else if (kind.equals("label")) {
                    createLabel(a, name, true, SourceType.USER_DEFINED);
                    if (!evidence.isEmpty()) lst.setComment(a, CodeUnit.EOL_COMMENT, evidence);
                    nl++;
                }
            }
        }
        println("ApplyNames: renamed/created " + nf + " functions, " + nl + " labels");
    }
}
