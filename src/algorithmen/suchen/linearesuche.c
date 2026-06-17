/* ju -- 2026 -- linearesuche.c
 * Lineare Suche: prüfe die Elemente der Reihe nach, bis der gesuchte Wert
 * gefunden ist. Funktioniert auf unsortierten Daten. Laufzeit O(n).
 */
#include <stdio.h>
#include "trace.h"

int main(int argc, char **argv) {
  int a[] = {7, 2, 9, 4, 1, 8, 3, 6, 5};
  int n = (int)(sizeof a / sizeof a[0]);
  int gesucht = 8;

  trace_init(argc, argv);
  trace_begin("linearesuche", "Lineare Suche", "array");
  trace_init_array(a, n);
  trace_note("Lineare Suche nach 8: jedes Element der Reihe nach prüfen.");

  int pos = -1;
  for (int i = 0; i < n; i++) {
    trace_highlight(&i, 1);          /* aktuell geprüftes Element */
    if (a[i] == gesucht) { trace_found(i); pos = i; break; }
  }
  trace_done();
  trace_finish();

  if (pos >= 0) printf("Wert %d gefunden an Position %d.\n", gesucht, pos);
  else          printf("Wert %d nicht gefunden.\n", gesucht);
  return 0;
}
