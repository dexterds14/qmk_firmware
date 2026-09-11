#!/bin/bash
# run_ghidra.sh -- headless Ghidra 12.1.3 analysis of the Keychron V10 Max flash dump.
#
# Usage:
#   run_ghidra.sh analyze            import dump_a.bin (base 0x08000000, ARM:LE:32:Cortex),
#                                    run PreSetup.java, auto-analyse, run all export post-scripts,
#                                    save the program into the project (overwrites an existing import)
#   AGGRESSIVE=1 run_ghidra.sh analyze   same, but enables Ghidra's "Aggressive Instruction Finder"
#   run_ghidra.sh export             re-run only the export post-scripts on the saved program
#   run_ghidra.sh script Foo.java [args...]
#                                    run one script (from scripts/) on the saved program, read-only
#
# Project (kept for later workflows): $PROJ_DIR / $PROJ_NAME, program name "dump_a.bin".
# Outputs go to the backup dir (../..): ghidra_functions.csv, ghidra_callgraph.json,
# ghidra_xrefs.json, ghidra_strings.csv, ghidra_coverage.txt, decompiled/*.c
# Logs: $PROJ_DIR/headless.log (analysis), $PROJ_DIR/script.log (script println output).
set -euo pipefail

export JAVA_HOME=/opt/homebrew/opt/openjdk@21/libexec/openjdk.jdk/Contents/Home
export PATH="$JAVA_HOME/bin:$PATH"
GHIDRA=/opt/homebrew/opt/ghidra/libexec/support/analyzeHeadless

HERE="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BACKUP="$(cd "$HERE/../.." && pwd)"
DUMP="$BACKUP/dump_a.bin"
SCRIPTS="$HERE/scripts"
OUT="${GHIDRA_OUT:-$BACKUP}"
PROJ_DIR="${GHIDRA_PROJ_DIR:-/private/tmp/claude-501/-Users-dexter-code-qmk/05a2f1c0-36d0-494b-8463-6b0ce77f8bca/scratchpad/ghidra_proj}"
PROJ_NAME="${GHIDRA_PROJ_NAME:-keychron_v10max}"
MODE="${1:-analyze}"

mkdir -p "$PROJ_DIR" "$OUT"
LOGS=(-log "$PROJ_DIR/headless.log" -scriptlog "$PROJ_DIR/script.log")
EXPORTS=(
  -postScript ReportCoverage.java  "$OUT"
  -postScript ExportFunctions.java "$OUT"
  -postScript ExportCallGraph.java "$OUT"
  -postScript ExportXrefs.java     "$OUT"
  -postScript ExportStrings.java   "$OUT"
  -postScript ExportDecompiled.java "$OUT"
)

case "$MODE" in
  analyze)
    AGGR="${AGGRESSIVE:-0}"
    echo ">> import+analyze $DUMP into $PROJ_DIR/$PROJ_NAME (aggressive=$AGGR)"
    "$GHIDRA" "$PROJ_DIR" "$PROJ_NAME" \
      -import "$DUMP" -overwrite \
      -loader BinaryLoader -loader-baseAddr 0x08000000 \
      -processor ARM:LE:32:Cortex -cspec default \
      -scriptPath "$SCRIPTS" \
      -preScript PreSetup.java "aggressive=$AGGR" \
      -postScript FindMoreFunctions.java "${RODATA_LIMIT:-0x08016000}" \
      "${EXPORTS[@]}" \
      -analysisTimeoutPerFile 1800 \
      "${LOGS[@]}"
    ;;
  export)
    echo ">> export from saved program in $PROJ_DIR/$PROJ_NAME"
    "$GHIDRA" "$PROJ_DIR" "$PROJ_NAME" \
      -process dump_a.bin -noanalysis -readOnly \
      -scriptPath "$SCRIPTS" \
      "${EXPORTS[@]}" \
      "${LOGS[@]}"
    ;;
  names)
    # apply known_names.csv (evidence-backed names) to the saved program, save, re-export
    CSV="${2:-$HERE/known_names.csv}"
    echo ">> apply names from $CSV, then re-export"
    "$GHIDRA" "$PROJ_DIR" "$PROJ_NAME" \
      -process dump_a.bin -noanalysis \
      -scriptPath "$SCRIPTS" \
      -postScript ApplyNames.java "$CSV" \
      "${EXPORTS[@]}" \
      "${LOGS[@]}"
    ;;
  script)
    shift
    echo ">> run script $* on saved program"
    "$GHIDRA" "$PROJ_DIR" "$PROJ_NAME" \
      -process dump_a.bin -noanalysis -readOnly \
      -scriptPath "$SCRIPTS" \
      -postScript "$@" \
      "${LOGS[@]}"
    ;;
  *)
    echo "usage: $0 analyze|export|script <Name.java> [args]" >&2
    exit 2
    ;;
esac
