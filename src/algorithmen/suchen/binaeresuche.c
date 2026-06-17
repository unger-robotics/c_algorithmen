/* ju -- 2026 -- binaeresuche.c
 * Binäre Suche: halbiere auf einem SORTIERTEN Feld den Suchbereich, bis der
 * Wert gefunden ist. Vergleiche das mittlere Element und springe in die
 * passende Hälfte. Laufzeit O(log n).
 */
#include <stdio.h>
#include "trace.h"

int main(int argc, char **argv) {
  int a[] = {2, 4, 6, 8, 10, 12, 14, 16, 18};   /* sortiert! */
  int n = (int)(sizeof a / sizeof a[0]);
  int gesucht = 14;

  trace_init(argc, argv);
  trace_begin("binaeresuche", "Binäre Suche", "array");
  trace_init_array(a, n);
  trace_note("Binäre Suche nach 14 im sortierten Feld: Suchbereich halbieren.");

  int lo = 0, hi = n - 1, pos = -1;
  while (lo <= hi) {
    int mid = (lo + hi) / 2;
    trace_pointer("lo", lo);
    trace_pointer("hi", hi);
    trace_pointer("mid", mid);
    trace_highlight(&mid, 1);
    if (a[mid] == gesucht)      { trace_found(mid); pos = mid; break; }
    else if (a[mid] < gesucht)  { lo = mid + 1; }   /* rechte Hälfte */
    else                        { hi = mid - 1; }   /* linke Hälfte  */
  }
  trace_done();
  trace_finish();

  if (pos >= 0) printf("Wert %d gefunden an Position %d.\n", gesucht, pos);
  else          printf("Wert %d nicht gefunden.\n", gesucht);
  return 0;
}
