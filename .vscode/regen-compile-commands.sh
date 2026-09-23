#!/bin/sh
# Regenerate compile_commands.json for IDE IntelliSense (clangd / cpptools).
#
# Why this wrapper exists: QMK never compiles a keymap's keymap.c as its own
# translation unit -- it is #included into quantum/keymap_introspection.c. So
# `qmk compile --compiledb` produces NO entry for keymap.c, and any editor that
# opens keymap.c directly parses it with no include paths or -D defines (every
# QMK type/keycode shows as "undefined"). This script runs the normal compiledb
# build, then synthesizes a keymap.c entry by cloning the introspection TU's
# flags, so keymap.c becomes a first-class database entry.
#
# Usage: .vscode/regen-compile-commands.sh [-kb <kb>] [-km <km>]
#        defaults: -kb szrkbd/bcorne -km dexter
set -e

KB="szrkbd/bcorne"
KM="dexter"
IF_STALE=0
while [ $# -gt 0 ]; do
    case "$1" in
        -kb|--keyboard) KB="$2"; shift 2 ;;
        -km|--keymap)   KM="$2"; shift 2 ;;
        # Only rebuild when the database is missing or older than a
        # build-affecting file (config.h / rules.mk / *.mk / keyboard.json).
        # Used by the auto-task so opening the folder is a cheap no-op unless
        # the compiler flags could actually have changed. Editing keymap.c's
        # body does NOT change flags, so it won't trigger a rebuild.
        --if-stale)     IF_STALE=1; shift ;;
        *) echo "unknown arg: $1" >&2; exit 1 ;;
    esac
done

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"

DB="$ROOT/compile_commands.json"
KMC_REL="keyboards/$KB/keymaps/$KM/keymap.c"

if [ "$IF_STALE" = 1 ]; then
    fresh=1
    [ -f "$DB" ] || fresh=0
    # keymap.c must already be a database entry (the injected one).
    if [ "$fresh" = 1 ] && ! grep -q "$KMC_REL" "$DB"; then fresh=0; fi
    # Any build-config file newer than the database => flags may have changed.
    if [ "$fresh" = 1 ]; then
        newer=$(find "keyboards/$KB" "users/$KM" \
                     \( -name '*.mk' -o -name 'config.h' -o -name 'keyboard.json' \
                        -o -name 'info.json' -o -name 'rules.mk' \) \
                     -newer "$DB" -print 2>/dev/null | head -1)
        [ -z "$newer" ] || fresh=0
    fi
    if [ "$fresh" = 1 ]; then
        echo "compile_commands.json is up to date; nothing to do."
        exit 0
    fi
    echo "compile_commands.json is stale or missing; regenerating..."
fi

# A clean build guarantees every real TU emits a command (an up-to-date object
# is skipped and would be missing from the database otherwise).
qmk compile -kb "$KB" -km "$KM" --compiledb -c

python3 - "$KB" "$KM" <<'PY'
import json, sys, os
kb, km = sys.argv[1], sys.argv[2]
db = json.load(open("compile_commands.json"))

kmc = f"keyboards/{kb}/keymaps/{km}/keymap.c"
if any(e.get("file", "").endswith(kmc) for e in db):
    sys.exit(0)  # already present (future QMK may compile it directly)

# keymap.c is #included into quantum/keymap_introspection.c; reuse its flags.
src = next((e for e in db if e.get("file", "").endswith("quantum/keymap_introspection.c")), None)
if src is None:
    print("warning: no keymap_introspection.c entry; leaving DB unchanged", file=sys.stderr)
    sys.exit(0)

entry = dict(src)
entry["file"] = os.path.join(src.get("directory", os.getcwd()), kmc) if not os.path.isabs(kmc) else kmc
# Point the command at keymap.c so the engine parses THIS file with these flags.
old = "quantum/keymap_introspection.c"
if "command" in entry and old in entry["command"]:
    entry["command"] = entry["command"].replace(old, kmc)
if "arguments" in entry:
    entry["arguments"] = [kmc if a == old else a for a in entry["arguments"]]
entry.pop("output", None)  # avoid two entries claiming the same .o

db.append(entry)
json.dump(db, open("compile_commands.json", "w"), indent=1)
print(f"injected DB entry for {kmc}")
PY
