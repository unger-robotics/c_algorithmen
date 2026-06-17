/* ju -- 2026 -- selectionsort.c
 * Selectionsort: suche in jedem Durchlauf das Minimum des unsortierten Rests
 * und tausche es an den Anfang. Der linke Bereich ist dann endgültig sortiert.
 * Laufzeit O(n^2), aber mit höchstens n-1 Vertauschungen.
 */
#include <stdio.h>
#include "trace.h"

static void drucke(const char *titel, const int *a, int n) {
  printf("%s", titel);
  for (int i = 0; i < n; i++) printf("%d ", a[i]);
  printf("\n");
}

int main(int argc, char **argv) {
  int a[] = {5, 2, 8, 1, 9, 3, 7, 4, 6};
  int n = (int)(sizeof a / sizeof a[0]);

  trace_init(argc, argv);
  trace_begin("selectionsort", "Selectionsort", "array");
  trace_init_array(a, n);
  trace_note("Selectionsort: kleinstes Element des Rests suchen und nach vorne tauschen.");

  for (int i = 0; i < n - 1; i++) {
    int min = i;
    trace_pointer("min", min);
    for (int j = i + 1; j < n; j++) {
      trace_compare(min, j);
      if (a[j] < a[min]) { min = j; trace_pointer("min", min); }
    }
    if (min != i) {
      int t = a[i]; a[i] = a[min]; a[min] = t;
      trace_swap(i, min);
    }
    trace_mark_sorted(i);            /* Anfang ist jetzt endgültig sortiert */
  }
  trace_mark_sorted(n - 1);
  trace_done();
  trace_finish();

  drucke("Sortiert: ", a, n);
  return 0;
}
