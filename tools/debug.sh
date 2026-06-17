#!/bin/sh
# ju -- 2026 -- debug.sh
# Auto-Debug: baut EIN Programm mit Debug-Symbolen (.dSYM, echte Datei:Zeile-
# Backtraces auf macOS) und laesst es nicht-interaktiv unter lldb laufen. Auf
# macOS linkt clang die DWARF-Infos nicht ins Executable, sondern hinterlegt
# eine Debug-Map auf die .o-Dateien — der Einschritt-Build loescht die aber
# sofort. Darum hier .o behalten + dsymutil, sonst gaebe es keine Zeilennummern.
# Laeuft das Programm sauber durch -> normale Ausgabe; stuerzt es ab (Segfault/
# Assert) -> automatischer vollstaendiger Backtrace, dann Ende.
#   sh tools/debug.sh <pfad-ohne-endung> [programm-argumente...]
set -eu
cd "$(dirname "$0")/.."

NAME="${1:?Aufruf: make debug NAME=<pfad> [ARGS=...]}"
shift  # Rest = Argumente fuer das Programm (z. B. --trace /tmp/t.json)

WARN="-Wall -Wextra -Wno-missing-field-initializers"
OUT="build/dbg/$NAME"          # unter build/ -> gitignored, via 'make clean' weg
mkdir -p "$(dirname "$OUT")"

if [ -f "src/$NAME.c" ]; then
  CFLAGS="$WARN -std=c17 -O0 -g -Ilib"
  # .o behalten -> macOS-Debug-Map/dsymutil finden die DWARF-Infos.
  cc $CFLAGS -c "src/$NAME.c"  -o "$OUT.o"
  cc $CFLAGS -c lib/meineFkt.c -o build/dbg/meineFkt.o
  cc $CFLAGS -c lib/trace.c    -o build/dbg/trace.o
  cc $CFLAGS -o "$OUT" "$OUT.o" build/dbg/meineFkt.o build/dbg/trace.o -lm
elif [ -f "src/$NAME.cpp" ]; then
  CXXFLAGS="$WARN -std=c++17 -O0 -g -Ilib"
  c++ $CXXFLAGS -c "src/$NAME.cpp" -o "$OUT.o"
  c++ $CXXFLAGS -o "$OUT" "$OUT.o" -lm
else
  echo "Quelle nicht gefunden: src/$NAME.c oder src/$NAME.cpp" >&2
  exit 1
fi

dsymutil "$OUT"                # self-contained .dSYM mit Datei:Zeile-Infos

# Nicht-interaktiv: run; bei Absturz -> Backtrace + quit, sonst laeuft es durch.
exec lldb --batch \
  -o run \
  -k 'thread backtrace all' \
  -k 'quit' \
  -- "./$OUT" "$@"
