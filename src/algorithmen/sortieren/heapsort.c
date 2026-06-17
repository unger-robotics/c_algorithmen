/* ju -- 2026 -- heapsort.c
 * Heapsort: baue aus dem Feld einen Max-Heap (größtes Element an der Wurzel),
 * tausche die Wurzel ans Ende und stelle den Heap wieder her. Laufzeit
 * O(n log n), in-place. Kinder von i: 2*i+1 und 2*i+2.
 */
#include <stdio.h>
#include "trace.h"

static int a[] = {5, 2, 8, 1, 9, 3, 7, 4, 6};
static int n   = (int)(sizeof a / sizeof a[0]);

static void tausche(int i, int j) {
  int t = a[i]; a[i] = a[j]; a[j] = t;
  trace_swap(i, j);
}

/* Wurzel bei 'start' nach unten versickern lassen, Heap reicht bis 'end'. */
static void versickern(int start, int end) {
  int root = start;
  while (2 * root + 1 <= end) {
    int kind = 2 * root + 1;
    if (kind + 1 <= end) {
      trace_compare(kind, kind + 1);
      if (a[kind + 1] > a[kind]) kind++;     /* größeres Kind wählen */
    }
    trace_compare(root, kind);
    if (a[root] < a[kind]) { tausche(root, kind); root = kind; }
    else break;
  }
}

static void drucke(const char *titel) {
  printf("%s", titel);
  for (int i = 0; i < n; i++) printf("%d ", a[i]);
  printf("\n");
}

int main(int argc, char **argv) {
  trace_init(argc, argv);
  trace_begin("heapsort", "Heapsort", "array");
  trace_init_array(a, n);
  trace_note("Heapsort: Max-Heap aufbauen, dann Wurzel ans Ende tauschen und Heap reparieren.");

  /* Phase 1: Max-Heap aufbauen */
  for (int start = n / 2 - 1; start >= 0; start--) versickern(start, n - 1);

  /* Phase 2: Wurzel (Maximum) ans Ende, Heap verkleinern */
  for (int end = n - 1; end > 0; end--) {
    tausche(0, end);
    trace_mark_sorted(end);
    versickern(0, end - 1);
  }
  trace_mark_sorted(0);
  trace_done();
  trace_finish();
  drucke("Sortiert: ");
  return 0;
}
