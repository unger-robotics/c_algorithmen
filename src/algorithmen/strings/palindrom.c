/* ju -- 2026 -- palindrom.c
 * Palindrom-Prüfung: ein Wort liest sich vorwärts wie rückwärts. Zwei Zeiger
 * von außen nach innen vergleichen die Zeichen paarweise. Laufzeit O(n).
 */
#include <stdio.h>
#include <string.h>
#include "trace.h"

int main(int argc, char **argv) {
  char s[] = "RENTNER";
  int n = (int)strlen(s);

  trace_init(argc, argv);
  trace_begin("palindrom", "Palindrom-Prüfung", "array");
  trace_init_string(s);
  trace_note("Zeichen von außen nach innen vergleichen.");

  int lo = 0, hi = n - 1, ist_palindrom = 1;
  while (lo < hi) {
    trace_pointer("lo", lo);
    trace_pointer("hi", hi);
    trace_compare(lo, hi);
    if (s[lo] != s[hi]) { ist_palindrom = 0; break; }
    lo++; hi--;
  }
  if (ist_palindrom) {
    trace_note("Alle Paare gleich → Palindrom.");
    for (int i = 0; i < n; i++) trace_mark_sorted(i);
  } else {
    trace_note("Ungleiches Paar gefunden → kein Palindrom.");
  }
  trace_done();
  trace_finish();

  printf("\"%s\" ist %s Palindrom.\n", s, ist_palindrom ? "ein" : "kein");
  return 0;
}
