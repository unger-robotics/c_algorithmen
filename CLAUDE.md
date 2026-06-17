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
(nur `find`/`patsubst`, keine modernen Make-Funktionen).

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
  eine `run`-Zeile in `tools/gen-traces.sh` ergänzt werden.
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
   `tree`/`chain-h`/`chain-v`/`hash`), `renderGraph.js` (view `graph`).

Das Trace-Event-Format ist die zentrale Schnittstelle und in
[docs/trace-schema.md](docs/trace-schema.md) dokumentiert. Renderer ignorieren
unbekannte Event-Typen (vorwärtskompatibel). Einen neuen Algorithmus, der eine
vorhandene `view` nutzt, muss man **nicht** im Frontend anfassen.

## Verzeichnisstruktur

- `lib/` — `meineFkt` (Fakultät/Quersumme/Potenzen), `trace` (JSON-Emitter)
- `src/algorithmen/{sortieren,suchen,datenstrukturen,graphen,rekursion,strings,mathematik,dynprog}/`
- `src/grundlagen/` — ältere Lernbeispiele (Bitoperationen in `bitweise/`, Logik …); portabel, ohne Trace
- `web/` — `index.html`, `css/`, `js/`, `traces/`
- `tools/gen-traces.sh` — Trace-/Manifest-Generator (Tabelle der Algorithmen)
- `docs/` — `trace-schema.md`, `tabellen/`, `bilder/`

## Verifikation (End-to-End)

1. `make all` ohne neue Warnungen.
2. `make run NAME=...` → Terminal-Ausgabe korrekt (Grundlagen: Vergleich mit dem
   `/* Ausgabe */`-Kommentar in der Datei).
3. `make trace ...` → `python3 -m json.tool <datei>` validiert das JSON.
4. `make web`, Browser/Playwright: Algorithmus wählen, abspielen, Endzustand
   prüfen (sortiert / Treffer / Pfad), keine JS-Konsolenfehler.

## Konventionen

- Header-Kommentarzeile je Datei: `// ju -- 2026 -- <datei>` (Stil aus dem Projekt).
- Deutsche Kommentare und Bezeichner (mit Umlauten), UTF-8, Zeilenende LF, 2 Leerzeichen Einzug.
- Algorithmus-Dateien sind self-contained und lesbar gehalten — sie sind das Lehrmaterial.
