/* ju -- 2026 -- sieb_eratosthenes.c
 * Sieb des Eratosthenes: alle Primzahlen bis N finden. Für jede Primzahl p
 * werden ihre Vielfachen gestrichen; was übrig bleibt, ist prim.
 * Laufzeit O(N log log N).
 */
#include <stdio.h>
#include "trace.h"

int main(int argc, char **argv) {
  int N = 30;
  int a[64], n = N - 1;
  for (int i = 0; i < n; i++) a[i] = i + 2;   /* Werte 2..N, Index v-2 */

  trace_init(argc, argv);
  trace_begin("sieb_eratosthenes", "Sieb des Eratosthenes", "array");
  trace_init_array(a, n);
  trace_note("Vielfache jeder Primzahl streichen (auf 0 setzen).");

  for (int p = 2; p * p <= N; p++) {
    if (a[p - 2] == 0) continue;              /* schon gestrichen */
    trace_pointer("p", p - 2);
    trace_mark_sorted(p - 2);                 /* p ist prim */
    // Erst ab p*p streichen: kleinere Vielfache (2p, 3p, …) hat bereits eine
    // kleinere Primzahl erledigt.
    for (int m = p * p; m <= N; m += p) {
      if (a[m - 2] != 0) { a[m - 2] = 0; trace_set(m - 2, 0); }
    }
  }
  for (int i = 0; i < n; i++) if (a[i] != 0) trace_mark_sorted(i);
  trace_done();
  trace_finish();

  printf("Primzahlen bis %d:", N);
  for (int i = 0; i < n; i++) if (a[i] != 0) printf(" %d", a[i]);
  printf("\n");
  return 0;
}
