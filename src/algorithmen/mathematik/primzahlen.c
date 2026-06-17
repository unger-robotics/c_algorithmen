/* ju -- 2026 -- primzahlen.c
 * Primzahltest durch Probedivision: eine Zahl n ist prim, wenn sie durch keine
 * Zahl von 2 bis sqrt(n) teilbar ist. Hier für alle Zahlen 2..N einzeln.
 */
#include <stdio.h>
#include "trace.h"

static int ist_prim(int z) {
  if (z < 2) return 0;
  for (int d = 2; d * d <= z; d++) if (z % d == 0) return 0;
  return 1;
}

int main(int argc, char **argv) {
  int N = 20;
  int a[64], n = N - 1;
  for (int i = 0; i < n; i++) a[i] = i + 2;

  trace_init(argc, argv);
  trace_begin("primzahlen", "Primzahltest (Probedivision)", "array");
  trace_init_array(a, n);
  trace_note("Jede Zahl einzeln testen: teilbar durch 2..sqrt(n)?");

  for (int i = 0; i < n; i++) {
    trace_pointer("n", i);
    if (ist_prim(a[i])) trace_mark_sorted(i);
    else { a[i] = 0; trace_set(i, 0); }       /* zusammengesetzt -> streichen */
  }
  trace_done();
  trace_finish();

  printf("Primzahlen bis %d:", N);
  for (int i = 0; i < n; i++) if (a[i] != 0) printf(" %d", a[i]);
  printf("\n");
  return 0;
}
