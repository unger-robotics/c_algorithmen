# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Was dieses Repository ist

Eine Lernsammlung klassischer Algorithmen in C (macOS, Stand 2026). Jeder
Algorithmus ist ein **eigenständiges** C-Programm mit eigenem `main()` und wird
zu einem separaten Executable kompiliert. Es gibt keine App-/Lib-Trennung außer
der gemeinsamen `lib/` (Helfer `meineFkt` + Trace-Bibliothek `trace`).

Kernidee: Die C-Programme sind die Quelle der Wahrheit. Mit `--trace <datei>`
schreiben sie ihren Ablauf als JSON-Trace, den ein interaktiver Web-Player
(`web/`) animiert. Ohne das Flag laufen sie als normale Terminal-Programme.

## Build & Ausführen

macOS/clang, **GNU Make 3.81** (Apple) — das Makefile ist bewusst konservativ
(nur `find`/`patsubst`, keine modernen Make-Funktionen). Standards: `-std=c17` /
`-std=c++17`, `-O0 -g`, Warnungen `-Wall -Wextra -Wno-missing-field-initializers`,
gelinkt gegen `-lm`.

```sh
make                 # Auto-Discovery: jedes src/**/*.c|cpp -> build/<pfad>
make run NAME=algorithmen/sortieren/quicksort        # eins bauen + ausführen
make trace NAME=... OUT=web/traces/x.json            # Trace gezielt erzeugen
make traces          # ALLE Demo-Traces + web/traces/manifest.json (via tools/gen-traces.sh)
make web             # python3 -m http.server -> http://localhost:8000/web/
make clean
```

Nicht offensichtlich:
- **Keine handgepflegte Ziel-Liste** mehr — `find src` entdeckt alle Quellen.
  Ein neuer Algorithmus wird automatisch gebaut; für einen Demo-Trace muss aber
  eine `run`-Zeile in `tools/gen-traces.sh` ergänzt werden. Der Trace-Dateiname
  ergibt sich aus dem **`basename` des Quellpfads**, nicht aus der `view` — daher
  `mitZuruecklegen.c` → `mitZuruecklegen.json` (obwohl View `lotto`). Die
  Reihenfolge der `run`-Zeilen ist die Anzeige-Reihenfolge im Player.
- `lib/meineFkt.c` und `lib/trace.c` werden in **jedes C-Programm** mitkompiliert
  (kein separates Linken). C++-Beispiele haben eine eigene Regel ohne die Libs.
- Verschachtelte `build/`-Pfade brauchen `mkdir -p $(dir $@)` pro Regel (drin).
- Compiler-Warnungen sind sauber zu halten (`-Wall -Wextra`, clang als `cc`).

## Visualisierungs-Architektur (das Wichtigste)

Drei Teile, lose über ein JSON-Format gekoppelt:

1. **`lib/trace.{h,c}`** — C-API, die Schritt-Events als JSON schreibt. Muster im
   Algorithmus: `trace_init(argc,argv)` → `trace_begin(algo,titel,view)` → eine
   `trace_init_*`-Funktion (`_array` / `_string` / `_layout` / `_none`) → Events
   (`trace_compare`, `trace_swap`, `trace_node`, `trace_visit`, …) → `trace_done()`
   → `trace_finish()`. Alle `trace_*`-Aufrufe sind No-Ops, wenn nicht getract wird,
   daher steht **derselbe Code** im Terminal- und im Trace-Lauf.
2. **`web/traces/*.json` + `manifest.json`** — von `tools/gen-traces.sh` aus den
   kompilierten Programmen erzeugt; im Repo eingecheckt (Demo-Daten).
3. **`web/`** — generischer Player. `js/player.js` ist der Rahmen (Play/Pause/
   Step/Timeline/Tempo) und wählt anhand von `trace.view` einen Renderer aus
   `window.RENDERERS`: `renderArray.js` (view `array`, Balken **oder** Buchstaben
   bei `init.labels`), `renderTree.js` (view `tree`; Layouts via `init.layout`:
   `tree`/`chain-h`/`chain-v`/`hash`), `renderGraph.js` (view `graph`),
   `renderBits.js` (view `bits`), `renderLogik.js` (view `logik`),
   `renderLotto.js` (view `lotto`), `renderSchaltung.js` (view `schaltung`).

Das Trace-Event-Format ist die zentrale Schnittstelle und in
[docs/trace-schema.md](docs/trace-schema.md) dokumentiert. Renderer ignorieren
unbekannte Event-Typen (vorwärtskompatibel). Einen neuen Algorithmus, der eine
vorhandene `view` nutzt, muss man **nicht** im Frontend anfassen.

## Verzeichnisstruktur

- `lib/` — `meineFkt` (Fakultät/Quersumme/Potenzen), `trace` (JSON-Emitter)
- `src/algorithmen/{sortieren,suchen,datenstrukturen,graphen,rekursion,strings,mathematik,dynprog}/`
- `src/grundlagen/` — ältere Lernbeispiele (Bitoperationen in `bitweise/`, Logik …); portabel, ohne Trace
- `web/` — `index.html`, `css/`, `js/`, `traces/`
- `tools/` — `gen-traces.sh` (Trace-/Manifest-Generator), `check-traces.py`,
  `check-golden.sh`, `check-hygiene.sh` (die CI-Gates, lokal ausführbar)
- `tests/` — `golden/*.txt` (erwartete Terminal-Ausgaben + `PROGRAMS`-Liste),
  `unit/*.c` (assert-basierte C-Unit-Tests für `lib/`, je eigenes `main()`),
  `e2e/player.spec.js` (Playwright-Player-Test)
- `docs/` — `trace-schema.md`, `tabellen/`, `bilder/`
- Tooling-Konfig im Wurzelverzeichnis: `.clang-format`/`.clang-tidy` (informativ),
  `.editorconfig`, `eslint.config.js`, `playwright.config.js`, `.github/workflows/`

## Verifikation, Tests & CI-Gates

Vier CI-Workflows (`.github/workflows/`) laufen bei jedem Push/PR. Vor dem
Commit lokal gegenprüfen — die Skripte **sind** die Gates:

```sh
sh tools/check-hygiene.sh        # harte Invarianten (s. u.) — blockierend
make test                        # Logik: assert-Unit-Tests aus tests/unit/ (Exit≠0 = Fehler)
make memcheck                    # Speicher: ASan/UBSan-Lauf aller Programme + Tests (LSan nur Linux)
make all && sh tools/check-golden.sh   # deterministische Terminal-Ausgaben
make traces && python3 tools/check-traces.py   # Trace-Schema/Manifest/Vollständigkeit
npm ci && npm run lint           # ESLint über web/js + tests/e2e
npm run test:e2e                 # Playwright (startet python3-Server selbst)
```

`tests/unit/*.c` liegen bewusst **außerhalb** von `src/` (das Auto-Discovery baut
nur `src/**`): sie sind kein `make all`-Ziel und bekommen kein Trace/Golden/Manifest.
Neue Unit-Tests dort werden von `make test` und `make memcheck` automatisch erfasst.

Was die Gates erzwingen (Reihenfolge der Workflows: `build`, `analyze`,
`hygiene`, `web`):
- **Golden-Tests** (`build`): die Terminal-Ausgabe jedes Programms in
  `tests/golden/PROGRAMS` muss byte-genau zur eingecheckten `tests/golden/*.txt`
  passen. Ändert sich eine Ausgabe **absichtlich**, neu schreiben mit
  `sh tools/check-golden.sh --update` und die Diffs mitcommitten. Interaktive
  Programme (`eingabe-user-pruefen*`) stehen nicht in `PROGRAMS`.
- **Demo-Traces in sync** (`build`): `git diff --exit-code -- web/traces` nach
  `make traces` muss leer sein — eingecheckte Traces sind Teil des Tests.
  Einzige Ausnahme: `mitZuruecklegen.json` (nutzt `rand()`, libc-abhängig).
- **Strenge Warnungen** (`analyze`): Build mit gcc **und** clang unter
  `-Werror -Wshadow -Wconversion -Wsign-conversion`. Lokal vor dem Commit:
  `make all WARN="-Wall -Wextra -Wno-missing-field-initializers -Wshadow -Wconversion -Wsign-conversion -Werror"`.
- **Sanitizer** (`analyze`): ASan+UBSan+LSan, jedes Programm **und** jeder
  `tests/unit/`-Test normal sowie mit `--trace` ausgeführt — Lecks und UB sind
  Fehler. Lokales Pendant: `make memcheck` (= `tools/check-memory.sh`); LSan läuft
  nur unter Linux, auf macOS greifen lokal nur ASan/UBSan (Lecks fängt erst die CI).
- **Unit-Tests** (`build`): `make test` baut/läuft `tests/unit/*.c`. Decken die
  `lib/`-API ab (`meineFkt`-Arithmetik, `trace`-Lebenszyklus) — der Lehrcode in
  `src/` ist `static`/global gekoppelt und nicht isoliert testbar.
- **`check-traces.py`** prüft mehr als JSON-Wohlgeformtheit: Pflichtfelder,
  erlaubte `view` (muss einen registrierten Renderer haben), ein abschließendes
  `done`-Event, Manifest-Konsistenz und dass **jede** Quelle mit `trace_begin(`
  einen Trace hat (sonst fehlt die `run`-Zeile in `gen-traces.sh`).
- `clang-format` und `clang-tidy` laufen nur **informativ** (`continue-on-error`):
  der Lehrcode ist bewusst von Hand formatiert (z. B. ausgerichtete Swaps
  `int t=a[i]; a[i]=a[j]; a[j]=t;`) — **nicht** blind reformatieren.

## Konventionen

- Header-Kommentarzeile je Datei: `// ju -- 2026 -- <datei>` (Stil aus dem Projekt).
- Deutsche Kommentare und Bezeichner (mit Umlauten), UTF-8, Zeilenende LF, 2 Leerzeichen Einzug.
- Algorithmus-Dateien sind self-contained und lesbar gehalten — sie sind das Lehrmaterial.
- `check-hygiene.sh` erzwingt hart (CI-blockierend): keine eingecheckten
  `build/`-Artefakte, LF (kein CRLF) + gültiges UTF-8 in allen Textdateien und
  in jeder Quelle (`.c/.cpp/.h`) die `ju`-Header-Zeile, kein Trailing-Whitespace,
  abschließende Newline. Neue Grundlagen-Beispiele behalten den
  `/* Ausgabe */`-Kommentar als dokumentierte Soll-Ausgabe.
