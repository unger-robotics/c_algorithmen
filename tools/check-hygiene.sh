#!/bin/sh
# ju -- 2026 -- check-hygiene.sh
# Erzwingt die Projekt-Invarianten (NICHT den vollen clang-format-Stil, der das
# handgemachte Lehrmaterial umbauen wuerde), naemlich:
#   - keine build-Artefakte eingecheckt
#   - LF-Zeilenenden (kein CRLF) und gueltiges UTF-8 in allen Textdateien
#   - Quellcode (.c/.cpp/.h): Header-Kommentarzeile, kein Trailing-Whitespace,
#     abschliessende Newline
# Aufruf:  tools/check-hygiene.sh   (Exit 0 = ok, 1 = Verstoss)
set -eu
cd "$(dirname "$0")/.."
fail=0
note() { echo "  - $1"; fail=1; }

# 1. keine build-Artefakte im Repo
if [ -n "$(git ls-files build)" ]; then
  note "build/ ist eingecheckt (sollte in .gitignore bleiben)"
fi

# 2. Textdateien: kein CRLF, gueltiges UTF-8
git ls-files '*.c' '*.cpp' '*.h' '*.js' '*.css' '*.html' '*.md' '*.yml' '*.sh' '*.py' '*.json' > /tmp/hy_text.txt
while IFS= read -r f; do
  [ -f "$f" ] || continue
  if awk '/\r$/{exit 1}' "$f"; then :; else note "CRLF-Zeilenenden: $f"; fi
  iconv -f utf-8 -t utf-8 "$f" > /dev/null 2>&1 || note "kein gueltiges UTF-8: $f"
done < /tmp/hy_text.txt

# 3. Quellcode-Konventionen
git ls-files 'src/**/*.c' 'src/**/*.cpp' 'src/**/*.h' 'lib/*.c' 'lib/*.h' > /tmp/hy_src.txt
while IFS= read -r f; do
  [ -f "$f" ] || continue
  head -2 "$f" | grep -q "ju" || note "Header-Kommentarzeile (ju) fehlt: $f"
  grep -nE '[ '"$(printf '\t')"']+$' "$f" > /dev/null && note "Trailing-Whitespace: $f" || true
  [ -n "$(tail -c1 "$f")" ] && note "keine abschliessende Newline: $f" || true
done < /tmp/hy_src.txt

rm -f /tmp/hy_text.txt /tmp/hy_src.txt
if [ "$fail" -eq 0 ]; then
  echo "Hygiene: ok (LF, UTF-8, Header, kein Trailing-WS, keine build-Artefakte)."
else
  echo "Hygiene: Verstoesse gefunden."; exit 1
fi
