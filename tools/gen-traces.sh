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
run algorithmen/sortieren/insertionsort   Sortieren  "Insertionsort"
run algorithmen/sortieren/selectionsort   Sortieren  "Selectionsort"
run algorithmen/sortieren/quicksort       Sortieren  "Quicksort"
run algorithmen/sortieren/mergesort       Sortieren  "Mergesort"
run algorithmen/sortieren/heapsort        Sortieren  "Heapsort"
run algorithmen/suchen/linearesuche       Suchen     "Lineare Suche"
run algorithmen/suchen/binaeresuche       Suchen     "Binäre Suche"
run algorithmen/datenstrukturen/verkettete_liste  Datenstrukturen  "Verkettete Liste"
run algorithmen/datenstrukturen/stack             Datenstrukturen  "Stack (LIFO)"
run algorithmen/datenstrukturen/queue             Datenstrukturen  "Queue (FIFO)"
run algorithmen/datenstrukturen/bst               Datenstrukturen  "Binärer Suchbaum"
run algorithmen/datenstrukturen/hashtabelle       Datenstrukturen  "Hashtabelle"
run algorithmen/graphen/bfs        Graphen  "Breitensuche (BFS)"
run algorithmen/graphen/dfs        Graphen  "Tiefensuche (DFS)"
run algorithmen/graphen/dijkstra   Graphen  "Dijkstra"
run algorithmen/rekursion/fibonacci   Rekursion  "Fibonacci (Aufrufbaum)"
run algorithmen/rekursion/hanoi       Rekursion  "Türme von Hanoi"
run algorithmen/strings/string_umkehr Strings    "String umkehren"
run algorithmen/strings/palindrom     Strings    "Palindrom-Prüfung"
run algorithmen/strings/naive_suche   Strings    "Naive Textsuche"
run algorithmen/mathematik/sieb_eratosthenes  Mathematik  "Sieb des Eratosthenes"
run algorithmen/mathematik/primzahlen         Mathematik  "Primzahltest"
run algorithmen/mathematik/ggt_euklid         Mathematik  "ggT (Euklid)"
run algorithmen/dynprog/fibonacci_dp  "Dynamische Programmierung"  "Fibonacci (DP)"
run algorithmen/dynprog/rucksack      "Dynamische Programmierung"  "0/1-Rucksack"
run grundlagen/schaltung   Grundlagen  "Schaltung (Logik)"
run grundlagen/bitweise/bitweisesUND             Bitoperationen  "UND (&)"
run grundlagen/bitweise/bitweisesODER            Bitoperationen  "ODER (|)"
run grundlagen/bitweise/bitweisesODER-v02        Bitoperationen  "ODER (|) v02"
run grundlagen/bitweise/bitweisesXOR             Bitoperationen  "XOR (^)"
run grundlagen/bitweise/bitweisesEinerkomplement Bitoperationen  "Einerkomplement (~)"
run grundlagen/bitweise/bitweiseVerschiebung     Bitoperationen  "Verschiebung (<< >>)"

# ---- manifest.json zusammensetzen ----------------------------------------
{
  printf '{\n  "algorithmen": [\n'
  sed '$ s/,$//' "$TMP"
  printf '  ]\n}\n'
} > "$OUT/manifest.json"
rm -f "$TMP"
echo "manifest -> $OUT/manifest.json"
