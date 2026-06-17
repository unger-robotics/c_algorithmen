/* ju -- 2026 -- bubblesort.c
 * Bubblesort: vergleiche benachbarte Elemente und tausche sie bei falscher
 * Reihenfolge. Nach Durchlauf k steht das k-größte Element endgültig hinten.
 * Laufzeit O(n^2). Mit --trace <datei> wird der Ablauf für den Web-Player
 * aufgezeichnet (sonst normales Terminal-Programm).
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
  trace_begin("bubblesort", "Bubblesort", "array");
  trace_init_array(a, n);
  trace_note("Bubblesort: benachbarte Elemente vergleichen und ggf. tauschen.");

  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - 1 - i; j++) {
      trace_compare(j, j + 1);
      if (a[j] > a[j + 1]) {
        int t = a[j]; a[j] = a[j + 1]; a[j + 1] = t;
        trace_swap(j, j + 1);
      }
    }
    trace_mark_sorted(n - 1 - i);   /* größtes der Runde ist hinten platziert */
  }
  trace_mark_sorted(0);
  trace_done();
  trace_finish();

  drucke("Sortiert: ", a, n);
  return 0;
}
