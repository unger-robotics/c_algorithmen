/* ju -- 2026 -- quicksort.c
 * Quicksort (Lomuto-Partition): wähle ein Pivot (hier das rechte Element),
 * ordne kleinere Elemente nach links, größere nach rechts, und sortiere die
 * beiden Teile rekursiv. Mittlere Laufzeit O(n log n).
 */
#include <stdio.h>
#include "trace.h"

static int a[] = {5, 2, 8, 1, 9, 3, 7, 4, 6};
static int n  = (int)(sizeof a / sizeof a[0]);

static void tausche(int i, int j) {
  int t = a[i]; a[i] = a[j]; a[j] = t;
  trace_swap(i, j);
}

static void quicksort(int lo, int hi) {
  if (lo > hi) return;
  if (lo == hi) { trace_mark_sorted(lo); return; }

  int pivot = a[hi];
  trace_pointer("pivot", hi);        /* Pivot bleibt während der Partition markiert */
  // i markiert das Ende der "<= Pivot"-Zone. Invariante: alles bei lo..i ist <= Pivot.
  int i = lo - 1;
  for (int j = lo; j < hi; j++) {
    trace_compare(j, hi);
    if (a[j] <= pivot) {
      // a[j] gehört in die kleine Zone: Zone um eins wachsen lassen und a[j] hineintauschen.
      i++;
      if (i != j) tausche(i, j);
    }
  }
  // Hinter der kleinen Zone (Index i+1) ist der endgültige Platz des Pivots:
  // links davon steht alles <= Pivot, rechts alles > Pivot.
  int p = i + 1;
  tausche(p, hi);                    /* Pivot an seine endgültige Position */
  trace_mark_sorted(p);

  quicksort(lo, p - 1);
  quicksort(p + 1, hi);
}

static void drucke(const char *titel) {
  printf("%s", titel);
  for (int i = 0; i < n; i++) printf("%d ", a[i]);
  printf("\n");
}

int main(int argc, char **argv) {
  trace_init(argc, argv);
  trace_begin("quicksort", "Quicksort", "array");
  trace_init_array(a, n);
  trace_note("Quicksort: um ein Pivot partitionieren, dann beide Hälften rekursiv sortieren.");

  quicksort(0, n - 1);

  trace_done();
  trace_finish();
  drucke("Sortiert: ");
  return 0;
}
