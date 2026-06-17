#!/bin/sh
# ju -- 2026 -- check-golden.sh
# Vergleicht die Terminal-Ausgabe deterministischer Programme mit den
# erwarteten Ausgaben unter tests/golden/. Die Programmliste steht in
# tests/golden/PROGRAMS (build-relative Pfade). Voraussetzung: make all.
#   tools/check-golden.sh            prueft (Exit 1 bei Abweichung)
#   tools/check-golden.sh --update   erzeugt/aktualisiert die Golden-Dateien
set -eu
cd "$(dirname "$0")/.."
GOLDEN=tests/golden
LIST="$GOLDEN/PROGRAMS"
mode=check
[ "${1:-}" = "--update" ] && mode=update
fail=0

while IFS= read -r p; do
  case "$p" in ''|\#*) continue ;; esac
  bin="build/$p"
  if [ ! -x "$bin" ]; then
    echo "fehlt (erst 'make all'): $bin"; fail=1; continue
  fi
  name=$(echo "$p" | tr '/' '_')
  exp="$GOLDEN/$name.txt"
  if [ "$mode" = update ]; then
    "$bin" < /dev/null > "$exp" 2>&1 || true
    echo "golden aktualisiert: $name.txt"
  else
    got=$(mktemp)
    "$bin" < /dev/null > "$got" 2>&1 || true
    if [ ! -f "$exp" ]; then
      echo "FEHLT golden: $exp"; fail=1
    elif ! diff -u "$exp" "$got" > /dev/null 2>&1; then
      echo "ABWEICHUNG: $p"; diff -u "$exp" "$got" | head -20; fail=1
    fi
    rm -f "$got"
  fi
done < "$LIST"

if [ "$mode" = check ]; then
  if [ "$fail" -eq 0 ]; then
    echo "Golden-Tests: alle Ausgaben stimmen."
  else
    echo "Golden-Tests: Abweichungen gefunden."; exit 1
  fi
fi
[ "$fail" -eq 0 ] || exit 1
