#!/bin/sh
# ju -- 2026 -- check-memory.sh
# Lokales Pendant zum CI-Sanitizer-Job (.github/workflows/analyze.yml): baut alle
# Programme UND die Unit-Tests mit Address-/UndefinedBehavior-Sanitizer und fuehrt
# sie aus (Demos zusaetzlich mit --trace). LeakSanitizer laeuft nur unter Linux —
# macOS/Darwin unterstuetzt LSan nicht. Interaktive Programme (eingabe-user-pruefen)
# werden uebersprungen.
#   tools/check-memory.sh          (Exit 0 = sauber, != 0 = Sanitizer-Fund)
set -eu
cd "$(dirname "$0")/.."

CC=${CC:-cc}
CXX=${CXX:-c++}
SAN="-fsanitize=address,undefined -fno-sanitize-recover=all -g"
export UBSAN_OPTIONS=print_stacktrace=1

# LeakSanitizer nur unter Linux aktivieren (macOS kann LSan nicht).
case "$(uname -s)" in
  Linux) export ASAN_OPTIONS=detect_leaks=1 ;;
  *)     export ASAN_OPTIONS=detect_leaks=0 ;;
esac

# Build-Ausgaben unter build/ -> durch .gitignore unversioniert, via 'make clean'
# aufraeumbar.
OUT=build/san
mkdir -p "$OUT"

# --- Demo-Programme (gleiche Auswahl wie die CI: git ls-files src) -----------
for f in $(git ls-files 'src/**/*.c'); do
  b="$OUT/$(echo "$f" | tr '/' '_')"
  $CC $SAN -std=c17 -Ilib -o "$b" "$f" lib/trace.c lib/meineFkt.c -lm
  case "$f" in *eingabe-user-pruefen*) echo "skip interaktiv: $f"; continue ;; esac
  echo "run: $f"
  "$b" < /dev/null > /dev/null
  "$b" --trace "$OUT/t.json" < /dev/null > /dev/null
done

for f in $(git ls-files 'src/**/*.cpp'); do
  b="$OUT/$(echo "$f" | tr '/' '_')"
  $CXX $SAN -std=c++17 -Ilib -o "$b" "$f" -lm
  echo "run: $f"
  "$b" < /dev/null > /dev/null
done

# --- Unit-Tests (Logik) ebenfalls unter den Sanitizern ----------------------
# Direkter Glob (nicht git ls-files): so greift der Check auch fuer noch nicht
# eingecheckte Tests bei der lokalen Entwicklung.
for f in tests/unit/*.c; do
  [ -e "$f" ] || continue
  b="$OUT/$(echo "$f" | tr '/' '_')"
  $CC $SAN -std=c17 -Ilib -o "$b" "$f" lib/trace.c lib/meineFkt.c -lm
  echo "run-test: $f"
  "$b" < /dev/null > /dev/null
done

echo "Speicher-Check: alles sauber."
