/* ju -- 2026 -- insertionsort.c
 * Insertionsort: baue links eine sortierte Teilfolge auf und füge jedes
 * weitere Element an der richtigen Stelle ein (durch Verschieben nach rechts).
 * Laufzeit O(n^2), sehr effizient bei fast sortierten Daten.
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
  trace_begin("insertionsort", "Insertionsort", "array");
  trace_init_array(a, n);
  trace_note("Insertionsort: jedes Element in die sortierte linke Teilfolge einfügen.");

  for (int i = 1; i < n; i++) {
    int key = a[i];
    trace_highlight(&i, 1);          /* aktuell einzufügendes Element */
    int j = i - 1;
    while (j >= 0 && a[j] > key) {
      trace_compare(j, j + 1);
      a[j + 1] = a[j];
      trace_set(j + 1, a[j]);        /* nach rechts schieben */
      j--;
    }
    a[j + 1] = key;
    trace_set(j + 1, key);           /* Element an die Lücke setzen */
  }
  for (int i = 0; i < n; i++) trace_mark_sorted(i);
  trace_done();
  trace_finish();

  drucke("Sortiert: ", a, n);
  return 0;
}
