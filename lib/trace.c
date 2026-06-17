/* ju -- 2026 -- trace.c -- Implementierung der Trace-Bibliothek (siehe trace.h) */

#include "trace.h"
#include <stdio.h>
#include <string.h>

/* Interner Zustand: Zielstrom + Komma-Buchhaltung fuer das events-Array. */
static FILE *tf = NULL;
static int   first_event = 1;

int trace_is_active(void) { return tf != NULL; }

int trace_init(int argc, char **argv) {
  for (int i = 1; i + 1 < argc; i++) {
    if (strcmp(argv[i], "--trace") == 0) {
      tf = fopen(argv[i + 1], "w");
      if (!tf) {
        fprintf(stderr, "trace: konnte '%s' nicht oeffnen\n", argv[i + 1]);
        return 0;
      }
      return 1;
    }
  }
  return 0;
}

/* JSON-String mit Anfuehrungszeichen ausgeben; UTF-8 bleibt roh (Umlaute ok). */
static void jstr(const char *s) {
  fputc('"', tf);
  for (const unsigned char *p = (const unsigned char *)s; *p; p++) {
    switch (*p) {
      case '"':  fputs("\\\"", tf); break;
      case '\\': fputs("\\\\", tf); break;
      case '\n': fputs("\\n", tf);  break;
      case '\t': fputs("\\t", tf);  break;
      case '\r': fputs("\\r", tf);  break;
      default:
        if (*p < 0x20) fprintf(tf, "\\u%04x", (unsigned)*p);
        else           fputc(*p, tf);
    }
  }
  fputc('"', tf);
}

static void arr_ints(const int *a, int n) {
  fputc('[', tf);
  for (int i = 0; i < n; i++) { if (i) fputc(',', tf); fprintf(tf, "%d", a[i]); }
  fputc(']', tf);
}

void trace_begin(const char *algo, const char *titel, const char *view) {
  if (!tf) return;
  fputs("{\n", tf);
  fputs("\"algo\":",  tf); jstr(algo);  fputs(",\n", tf);
  fputs("\"titel\":", tf); jstr(titel); fputs(",\n", tf);
  fputs("\"view\":",  tf); jstr(view);  fputs(",\n", tf);
}

void trace_init_array(const int *a, int n) {
  if (!tf) return;
  fputs("\"init\":{\"array\":", tf); arr_ints(a, n); fputs("},\n", tf);
  fputs("\"events\":[\n", tf);
  first_event = 1;
}

void trace_init_none(void) {
  if (!tf) return;
  fputs("\"init\":{},\n\"events\":[\n", tf);
  first_event = 1;
}

/* --- Event-Builder ------------------------------------------------------- */
static void ev_begin(const char *t) {
  if (!first_event) fputs(",\n", tf);
  first_event = 0;
  fputs("{\"t\":", tf); jstr(t);
}
static void ev_int (const char *k, int v)               { fprintf(tf, ",\"%s\":%d", k, v); }
static void ev_str (const char *k, const char *s)       { fprintf(tf, ",\"%s\":", k); jstr(s); }
static void ev_ints(const char *k, const int *a, int n) { fprintf(tf, ",\"%s\":", k); arr_ints(a, n); }
static void ev_end (void)                               { fputc('}', tf); }

/* --- universell ---------------------------------------------------------- */
void trace_note(const char *text) { if (!tf) return; ev_begin("note"); ev_str("text", text); ev_end(); }
void trace_done(void)             { if (!tf) return; ev_begin("done"); ev_end(); }

/* --- array --------------------------------------------------------------- */
void trace_compare(int i, int j)            { if (!tf) return; ev_begin("compare");    ev_int("i", i); ev_int("j", j); ev_end(); }
void trace_swap(int i, int j)               { if (!tf) return; ev_begin("swap");       ev_int("i", i); ev_int("j", j); ev_end(); }
void trace_set(int i, int val)              { if (!tf) return; ev_begin("set");        ev_int("i", i); ev_int("val", val); ev_end(); }
void trace_highlight(const int *idx, int n) { if (!tf) return; ev_begin("highlight");  ev_ints("idx", idx, n); ev_end(); }
void trace_mark_sorted(int i)               { if (!tf) return; ev_begin("markSorted"); ev_int("i", i); ev_end(); }
void trace_pointer(const char *name, int i) { if (!tf) return; ev_begin("pointer");    ev_str("name", name); ev_int("i", i); ev_end(); }
void trace_found(int i)                     { if (!tf) return; ev_begin("found");      ev_int("i", i); ev_end(); }

/* --- tree ---------------------------------------------------------------- */
void trace_node(int id, int val, int parent, const char *pos) {
  if (!tf) return;
  ev_begin("addNode"); ev_int("id", id); ev_int("val", val);
  if (parent >= 0) ev_int("parent", parent);
  if (pos)         ev_str("pos", pos);
  ev_end();
}
void trace_remove_node(int id)            { if (!tf) return; ev_begin("removeNode");  ev_int("id", id); ev_end(); }
void trace_edge(int from, int to)         { if (!tf) return; ev_begin("addEdge");     ev_int("from", from); ev_int("to", to); ev_end(); }
void trace_visit(int id)                  { if (!tf) return; ev_begin("visit");       ev_int("id", id); ev_end(); }
void trace_compare_node(int id, int val)  { if (!tf) return; ev_begin("compareNode"); ev_int("id", id); ev_int("val", val); ev_end(); }
void trace_bucket(int idx, const int *ids, int n) { if (!tf) return; ev_begin("bucket"); ev_int("idx", idx); ev_ints("ids", ids, n); ev_end(); }

/* --- graph --------------------------------------------------------------- */
void trace_gnode(int id, const char *label, int x, int y) {
  if (!tf) return;
  ev_begin("addNode"); ev_int("id", id); ev_str("label", label);
  if (x != TRACE_NONE && y != TRACE_NONE) { ev_int("x", x); ev_int("y", y); }
  ev_end();
}
void trace_gedge(int from, int to, int w, int directed) {
  if (!tf) return;
  ev_begin("addEdge"); ev_int("from", from); ev_int("to", to);
  if (w >= 0)   ev_int("w", w);
  if (directed) ev_int("dir", 1);
  ev_end();
}
void trace_frontier(const int *ids, int n) { if (!tf) return; ev_begin("frontier"); ev_ints("ids", ids, n); ev_end(); }
void trace_relax(int from, int to, int dist) { if (!tf) return; ev_begin("relax"); ev_int("from", from); ev_int("to", to); ev_int("dist", dist); ev_end(); }
void trace_set_dist(int id, int dist)      { if (!tf) return; ev_begin("setDist");  ev_int("id", id); ev_int("dist", dist); ev_end(); }
void trace_path(const int *ids, int n)     { if (!tf) return; ev_begin("path");     ev_ints("ids", ids, n); ev_end(); }

void trace_finish(void) {
  if (!tf) return;
  fputs("\n]\n}\n", tf);
  fclose(tf);
  tf = NULL;
}
