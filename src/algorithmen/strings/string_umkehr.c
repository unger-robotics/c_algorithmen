/* ju -- 2026 -- string_umkehr.c
 * String umkehren: zwei Zeiger von außen nach innen laufen lassen und die
 * Zeichen paarweise tauschen. Laufzeit O(n).
 */
#include <stdio.h>
#include <string.h>
#include "trace.h"

int main(int argc, char **argv) {
  char s[] = "ALGORITHMUS";
  int n = (int)strlen(s);

  trace_init(argc, argv);
  trace_begin("string_umkehr", "String umkehren", "array");
  trace_init_string(s);
  trace_note("Zwei Zeiger von außen nach innen, Zeichen paarweise tauschen.");

  int lo = 0, hi = n - 1;
  while (lo < hi) {
    trace_pointer("lo", lo);
    trace_pointer("hi", hi);
    char t = s[lo]; s[lo] = s[hi]; s[hi] = t;
    trace_swap(lo, hi);
    lo++; hi--;
  }
  for (int i = 0; i < n; i++) trace_mark_sorted(i);
  trace_done();
  trace_finish();

  printf("Umgekehrt: %s\n", s);
  return 0;
}
