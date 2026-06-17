# C Algorithmen — interaktiv verstehen

Eine Lernsammlung klassischer Algorithmen in C (Stand 2026, macOS). Jeder
Algorithmus ist ein eigenständiges, kommentiertes C-Programm und kann zusätzlich
einen **Trace** schreiben, den ein interaktiver **Web-Player** Schritt für
Schritt animiert — zum Verstehen, nicht nur zum Nachschlagen.

![Dijkstra im Web-Player](docs/bilder/player-dijkstra.png)

## Idee

> Die C-Programme sind die **Quelle der Wahrheit**. Mit `--trace <datei>`
> schreiben sie ihren Ablauf als JSON; ohne das Flag laufen sie als ganz
> normale Terminal-Programme. Ein generischer Web-Player spielt die Traces ab.

Kein WebAssembly, kein Build-Schritt fürs Frontend — nur `clang`, `make` und ein
einfacher Python-Webserver, die auf macOS bereits vorhanden sind.

## Voraussetzungen

- **macOS** mit Xcode Command Line Tools (`clang`, `make`) — `xcode-select --install`
- **Python 3** für den lokalen Webserver (vorinstalliert)
- ein moderner Browser

## Schnellstart

```sh
make                 # alle Programme nach build/ bauen
make traces          # alle Demo-Traces nach web/traces/ erzeugen
make web             # Player unter http://localhost:8000/web/ servieren
```

Einzelnes Programm bauen und im Terminal ausführen:

```sh
make run NAME=algorithmen/sortieren/quicksort
```

Einen Trace gezielt neu erzeugen:

```sh
make trace NAME=algorithmen/sortieren/quicksort OUT=web/traces/quicksort.json
```

## Web-Player

`make web` starten, dann <http://localhost:8000/web/> öffnen (der Webserver ist
nötig — direktes Öffnen per `file://` blockiert das Laden der Traces). Oben den
Algorithmus wählen.

- **▶ / ⏸** abspielen / pausieren · **◀ ▶❘** Schritt zurück/vor · **⏮** zum Anfang
- **Timeline** an beliebige Stelle springen · **Tempo** Schritte pro Sekunde
- Tastatur: **Leertaste** play/pause, **←/→** Einzelschritt
- „Trace laden…" zeigt einen selbst erzeugten Trace direkt an

![Bubblesort im Web-Player](docs/bilder/player-bubblesort.png)

## Enthaltene Algorithmen

| Thema | Algorithmen |
|-------|-------------|
| Sortieren | Bubble-, Insertion-, Selection-, Quick-, Merge-, Heapsort |
| Suchen | lineare Suche, binäre Suche |
| Datenstrukturen | verkettete Liste, Stack, Queue, binärer Suchbaum, Hashtabelle |
| Graphen | Breitensuche (BFS), Tiefensuche (DFS), Dijkstra |
| Rekursion | Fibonacci-Aufrufbaum, Türme von Hanoi |
| Strings | Umkehren, Palindrom-Prüfung, naive Textsuche |
| Mathematik | Sieb des Eratosthenes, Primzahltest, ggT (Euklid) |
| Dynamische Programmierung | Fibonacci-Tabelle, 0/1-Rucksack |

Die Visualisierung kennt drei Sichten (`view`): `array` (Balken bzw. Buchstaben),
`tree` (Baum/Liste/Stack/Queue/Hash) und `graph`. Welche Sicht ein Algorithmus
nutzt, steht in seinem Trace; das Format ist in [docs/trace-schema.md](docs/trace-schema.md)
beschrieben.

## Projektstruktur

```
.
├── Makefile            portabler Auto-Discovery-Build (clang, build/)
├── lib/                meineFkt (Helfer) + trace (JSON-Trace-Bibliothek)
├── src/
│   ├── algorithmen/    die Algorithmen-Sammlung (thematisch gruppiert)
│   └── grundlagen/     ältere C-Lernbeispiele (Bitoperationen, Logik …)
├── web/                interaktiver Player (HTML/CSS/JS) + traces/
├── tools/gen-traces.sh erzeugt alle Traces + web/traces/manifest.json
└── docs/               Trace-Schema, Tabellen, Bilder
```

## Grundlagen-Beispiele

Unter `src/grundlagen/` liegen die ursprünglichen Lernprogramme: bitweise
Operatoren, Logik-/Zahlensystem-Tabellen, Eingabeprüfung u. a. Sie werden vom
selben `make all` gebaut, erzeugen aber keine Traces.

## Eigene Algorithmen hinzufügen

1. C-Datei unter `src/algorithmen/<thema>/` anlegen, `#include "trace.h"`.
2. `trace_init(argc, argv)`, dann `trace_begin(...)`, eine `trace_init_*`-Funktion
   und die passenden `trace_*`-Events einstreuen (siehe vorhandene Beispiele).
3. In `tools/gen-traces.sh` eine `run`-Zeile ergänzen.
4. `make traces && make web`.
