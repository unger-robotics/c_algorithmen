#!/bin/sh
# Erzeugt alle Demo-Traces (web/traces/*.json) + manifest.json aus den
# kompilierten C-Programmen. Vorher: make all.  Aufruf: make traces
set -e
cd "$(dirname "$0")/.."
OUT=web/traces
mkdir -p "$OUT"
TMP="$OUT/.man.tmp"
: > "$TMP"

# run <build-pfad> <kategorie> <titel>
run() {
  name=$(basename "$1")
  if [ ! -x "build/$1" ]; then
    echo "  fehlt: build/$1 — erst 'make all'" >&2
    return 0
  fi
  ./build/"$1" --trace "$OUT/$name.json" >/dev/null
  printf '    {"kategorie":"%s","titel":"%s","datei":"%s.json"},\n' "$2" "$3" "$name" >> "$TMP"
  echo "  trace: $name.json"
}

# ---- Algorithmen (Reihenfolge = Anzeige im Player) -----------------------
run algorithmen/sortieren/bubblesort      Sortieren  "Bubblesort"

# ---- manifest.json zusammensetzen ----------------------------------------
{
  printf '{\n  "algorithmen": [\n'
  sed '$ s/,$//' "$TMP"
  printf '  ]\n}\n'
} > "$OUT/manifest.json"
rm -f "$TMP"
echo "manifest -> $OUT/manifest.json"
