# Trace-Schema

Ein **Trace** ist eine JSON-Datei, die der Web-Player (`web/`) abspielt. Jeder
C-Algorithmus erzeugt sie mit `--trace <datei>` über die Bibliothek
[`lib/trace.h`](../lib/trace.h). Ohne das Flag laufen die `trace_*`-Aufrufe als
No-Op und das Programm verhält sich wie ein normales Terminal-Programm.

## Aufbau

```json
{
  "algo":  "bubblesort",
  "titel": "Bubblesort",
  "view":  "array",
  "init":  { "array": [5, 2, 8, 1, 9, 3] },
  "events": [
    { "t": "compare", "i": 0, "j": 1 },
    { "t": "swap",    "i": 0, "j": 1 },
    { "t": "markSorted", "i": 5 },
    { "t": "done" }
  ]
}
```

| Feld     | Bedeutung |
|----------|-----------|
| `algo`   | technischer Name (Dateiname ohne Endung) |
| `titel`  | Anzeigename im Player |
| `view`   | `"array"` \| `"tree"` \| `"graph"` — bestimmt den Renderer |
| `init`   | Startzustand (bei `array`: `{ "array": [...] }`; bei `tree`/`graph`: `{}`) |
| `events` | abspielbare Schrittfolge |

Der Player baut aus `init` den Anfangszustand und wendet die `events` der Reihe
nach an. Ein Slider/Step setzt den Cursor; gezeichnet wird durch erneutes
Abspielen von `init` bis zum Cursor (idempotenter Replay). **Unbekannte
Event-Typen werden ignoriert** (vorwärtskompatibel).

## Event-Typen

### universell (alle Sichten)
| `t` | Felder | Wirkung |
|-----|--------|---------|
| `note` | `text` | Erklärtext in der Statuszeile |
| `done` | — | Algorithmus fertig |

### view `array` — Sortieren, Suchen
| `t` | Felder | Wirkung | `trace.h` |
|-----|--------|---------|-----------|
| `compare` | `i`,`j` | zwei Balken vergleichen (gelb) | `trace_compare` |
| `swap` | `i`,`j` | Werte an `i`,`j` tauschen | `trace_swap` |
| `set` | `i`,`val` | Balken `i` auf `val` setzen | `trace_set` |
| `highlight` | `idx[]` | Indexmenge markieren (z. B. Pivot) | `trace_highlight` |
| `markSorted` | `i` | Balken `i` endgültig platziert (grün) | `trace_mark_sorted` |
| `pointer` | `name`,`i` | benannter Zeiger (`lo`,`hi`,`mid`) | `trace_pointer` |
| `found` | `i` | Treffer (Suche) | `trace_found` |

### view `tree` — verkettete Liste, Stack, Queue, BST, Hashtabelle
| `t` | Felder | Wirkung | `trace.h` |
|-----|--------|---------|-----------|
| `addNode` | `id`,`val`,`parent?`,`pos?` | Knoten anlegen (`pos`=`left`/`right`) | `trace_node` |
| `removeNode` | `id` | Knoten entfernen | `trace_remove_node` |
| `addEdge` | `from`,`to` | Kante (Listen-`next`/Baum-Kind) | `trace_edge` |
| `visit` | `id` | Knoten hervorheben | `trace_visit` |
| `compareNode` | `id`,`val` | Vergleich an Knoten (BST-Suche) | `trace_compare_node` |
| `bucket` | `idx`,`ids[]` | Hash-Bucket-Belegung | `trace_bucket` |

### view `graph` — BFS, DFS, Dijkstra
| `t` | Felder | Wirkung | `trace.h` |
|-----|--------|---------|-----------|
| `addNode` | `id`,`label`,`x?`,`y?` | Graph-Knoten (optionale feste Position) | `trace_gnode` |
| `addEdge` | `from`,`to`,`w?`,`dir?` | Kante (Gewicht, gerichtet) | `trace_gedge` |
| `visit` | `id` | Knoten besucht | `trace_visit` |
| `frontier` | `ids[]` | aktuelle Queue/Stack-Front | `trace_frontier` |
| `relax` | `from`,`to`,`dist` | Dijkstra-Kantenrelaxation | `trace_relax` |
| `setDist` | `id`,`dist` | Distanzlabel aktualisieren | `trace_set_dist` |
| `path` | `ids[]` | finalen Pfad hervorheben | `trace_path` |

## Trace erzeugen

```sh
make trace NAME=algorithmen/sortieren/bubblesort OUT=web/traces/bubblesort.json
python3 -m json.tool web/traces/bubblesort.json   # validieren
```
