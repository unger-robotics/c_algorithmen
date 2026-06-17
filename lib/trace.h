/* ju -- 2026 -- trace.h
 * Schlanke Trace-Bibliothek: ein Algorithmus schreibt seinen Ablauf als
 * Folge von JSON-Events in eine Datei, die der Web-Player abspielt.
 *
 * Idee: dieselben trace_*-Aufrufe stehen im Algorithmus, egal ob getract
 * wird oder nicht. Ohne "--trace <datei>" sind alle Aufrufe No-Ops und das
 * Programm laeuft als normales Terminal-Programm.
 *
 * Typischer Ablauf:
 *   trace_init(argc, argv);                 // schaltet Tracing ein/aus
 *   trace_begin("bubblesort","Bubblesort","array");
 *   trace_init_array(a, n);                 // Startzustand
 *   ... trace_compare(i,j); trace_swap(i,j); ...
 *   trace_done();
 *   trace_finish();
 */
#ifndef TRACE_H
#define TRACE_H

#include <limits.h>

/* Sentinel fuer "kein Wert" bei optionalen Koordinaten. */
#define TRACE_NONE INT_MIN

#ifdef __cplusplus
extern "C" {
#endif

/* --trace <datei> in argv suchen und Datei oeffnen. 1 = aktiv, 0 = aus. */
int  trace_init(int argc, char **argv);
int  trace_is_active(void);

/* Kopf + Startzustand. view = "array" | "tree" | "graph". */
void trace_begin(const char *algo, const char *titel, const char *view);
void trace_init_array(const int *a, int n);
void trace_init_string(const char *s);  /* array-view mit Buchstaben (Strings) */
void trace_init_none(void);   /* fuer tree/graph: Struktur entsteht via Events */
void trace_init_layout(const char *layout); /* tree/graph: Layout-Hinweis fuer den Renderer */

/* universell */
void trace_note(const char *text);
void trace_done(void);

/* view "array" (Sortieren / Suchen) */
void trace_compare(int i, int j);
void trace_swap(int i, int j);
void trace_set(int i, int val);
void trace_highlight(const int *idx, int n);
void trace_mark_sorted(int i);
void trace_pointer(const char *name, int i);
void trace_found(int i);

/* view "tree" (verkettete Liste, Stack, Queue, BST, Hashtabelle) */
void trace_node(int id, int val, int parent, const char *pos); /* parent<0 / pos=NULL = weglassen */
void trace_remove_node(int id);
void trace_edge(int from, int to);
void trace_visit(int id);
void trace_compare_node(int id, int val);
void trace_bucket(int idx, const int *ids, int n);

/* view "graph" (BFS / DFS / Dijkstra) */
void trace_gnode(int id, const char *label, int x, int y); /* x/y = TRACE_NONE = weglassen */
void trace_gedge(int from, int to, int w, int directed);   /* w<0 = weglassen */
void trace_frontier(const int *ids, int n);
void trace_relax(int from, int to, int dist);
void trace_set_dist(int id, int dist);
void trace_path(const int *ids, int n);

/* view "schaltung": eine Schalterstellung (n Schalter 0/1) + Lampenzustand */
void trace_circuit(int zaehler, const int *schalter, int n, int lampe);

void trace_finish(void);

#ifdef __cplusplus
}
#endif

#endif /* TRACE_H */
