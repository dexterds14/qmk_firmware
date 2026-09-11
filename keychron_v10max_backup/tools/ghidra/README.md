# Ghidra headless analysis of the Keychron V10 Max flash dump

Input: `../../dump_a.bin` (262144 B, flash 0x08000000..0x0803FFFF of an STM32F401xC).
Ghidra 12.1.3 (`/opt/homebrew/opt/ghidra`), JDK 21 (`/opt/homebrew/opt/openjdk@21`).

## Project (kept, re-used by later workflows)

| item | value |
|---|---|
| project dir | `/private/tmp/claude-501/-Users-dexter-code-qmk/05a2f1c0-36d0-494b-8463-6b0ce77f8bca/scratchpad/ghidra_proj` |
| project name | `keychron_v10max` (file `keychron_v10max.gpr`) |
| program | `/dump_a.bin`, language `ARM:LE:32:Cortex`, cspec `default`, base 0x08000000 |
| logs | `ghidra_proj/headless.log` (analysis), `ghidra_proj/script.log` (script println output incl. every function created by `FindMoreFunctions`) |
| comparison project | `.../scratchpad/ghidra_proj_aggr` / `keychron_v10max_aggr` = same pipeline with Ghidra's "Aggressive Instruction Finder" enabled (no measurable benefit: 864 vs 862 functions at that stage, coverage 82.24 % vs 82.33 %) |

Override with env vars `GHIDRA_PROJ_DIR`, `GHIDRA_PROJ_NAME`, `GHIDRA_OUT`, `RODATA_LIMIT` (default in the
runner is `0x08016000`; the analysis was run with `0x08016710`, the first byte after the last code
function `0x080166FC..0x08016701`), `AGGRESSIVE=1`.

## Runner: `run_ghidra.sh`

```
run_ghidra.sh analyze              import + PreSetup + auto-analysis + FindMoreFunctions + exports (overwrites)
run_ghidra.sh names [csv]          ApplyNames.java known_names.csv on the saved program, then exports
run_ghidra.sh export               only the export post-scripts (read-only)
run_ghidra.sh script Foo.java ...  any script in scripts/ on the saved program (read-only)
```

## Scripts (`scripts/`)

| script | stage | what it does |
|---|---|---|
| `PreSetup.java` | pre | splits flash into `FLASH_hdr` (0x08000000-0x08007FFF), `FLASH_text` (0x08008000-0x08017FFF, the only executable block), `FLASH_unused`; creates uninitialized `SRAM` 0x20000000+64K, `PERIPH_APB_AHB1` 0x40000000+0x80000, `PERIPH_AHB2_USB` 0x50000000+0x61000, `PPB_SCS` 0xE0000000+1M (peripherals volatile); labels `g_vector_table`, `eeprom_backing_store` (0x08004000), types `keymaps` at 0x080169B8 as `ushort[6][6][18]`; sets TMode=1 over the text block; types the 120 vector slots as pointers, disassembles the 31 distinct odd targets and names them ChibiOS/STM32F401 style (`_crt0_entry`, `_unhandled_exception`, `SVCall_Handler`, `Vector58_IRQ6_EXTI0`, `Vector14C_IRQ67_OTG_FS`, ...); enables "Decompiler Parameter ID", sets ASCII min string length 4, toggles "Aggressive Instruction Finder" per `aggressive=` arg |
| `FindMoreFunctions.java` | post 1 | iterative recovery of functions the stock analyzers miss: A = Thumb function-pointer scan of every word in the image, B = orphan instruction ranges, D = manual `tbb`/`tbh` table decoding when Ghidra left one unresolved, F = tail-call targets (unconditional jumps into another body, or any branch target that is a `push {..,lr}`), C = gap walk with strict prologue shapes and literal-pool skipping (only after A/B/D/F settle), G = absorb switch-case fragments back into the owning function, E = recompute bodies that swallowed later-created entries; cleanup removes anything at/after `RODATA_LIMIT`. Every created / reverted / absorbed entry is logged in `script.log` |
| `ApplyNames.java` | post | applies `known_names.csv` (addr,kind,name,evidence): renames/creates functions with the evidence as plate comment, creates data labels |
| `ReportCoverage.java` | export | `ghidra_coverage.txt` – bytes of 0x08008000..0x08017F04 in function bodies / instructions / data / undefined, undefined gaps ≥ 8 B |
| `ExportFunctions.java` | export | `ghidra_functions.csv` – entry,size,name,n_callers,n_callees,is_thunk,signature,strings |
| `ExportCallGraph.java` | export | `ghidra_callgraph.json` – nodes, caller→callee edges (call and tail-jump, with call sites), indirect call sites |
| `ExportXrefs.java` | export | `ghidra_xrefs.json` – references to keymaps[] (direct + literal-pool words + readers), all refs into 0x08016000..0x08017F04 |
| `ExportStrings.java` | export | `ghidra_strings.csv` – defined strings with xrefs (through literal pools) |
| `ExportDecompiled.java` | export | `decompiled/<addr>_<name>.c` for every function, plus `decompiled/_ALL.c` and `_INDEX.csv` |
| `DebugCreate.java` | tool | prints listing state at given addresses and what `createFunction` would do (run read-only) |
| `../summarize_ghidra.py` | tool | `ghidra_summary.md` – coverage, 20 largest functions, keymap references, functions with keycode-like constants |

## Pitfalls met (so nobody repeats them)

* A word that *looks* like a peripheral/SRAM pointer (0x4xxx_xxxx, 0x2000_xxxx) is very often a
  `push {..}; ldr rX,[pc]` or `bx lr; movs r0,#0` pair – never skip gap bytes on that basis alone.
  Literal-pool words are recognised by having a reference to them, or by holding a flash address.
* Ghidra's switch analysis puts DATA references from the `tbb` byte table onto the case targets;
  do not treat such references as pointer-table evidence for a function entry.
* GCC's ICF turns `keycode_at_keymap_location` into a 4-byte `b.w` thunk, and `-Os` tail calls
  (`b.w` to a function that nothing `bl`s) make Ghidra swallow the callee into the caller's body.
  Pass F carves those out; the body of the swallowing function is recomputed afterwards.
