/* ju -- 2026 -- fibonacci_dp.c
 * Fibonacci mit dynamischer Programmierung: die Tabelle f[0..n] wird von links
 * nach rechts gefüllt, jeder Wert ist die Summe der beiden Vorgänger. Jedes
 * Teilproblem wird genau einmal gelöst — Laufzeit O(n) statt exponentiell.
 */
#include <stdio.h>
#include "trace.h"

int main(int argc, char **argv) {
  int n = 12;
  int f[32], init[32] = {0};

  trace_init(argc, argv);
  trace_begin("fibonacci_dp", "Fibonacci (DP-Tabelle)", "array");
  trace_init_array(init, n + 1);
  trace_note("Tabelle f[i] = f[i-1] + f[i-2] von links füllen.");

  f[0] = 0; trace_set(0, 0); trace_mark_sorted(0);
  f[1] = 1; trace_set(1, 1); trace_mark_sorted(1);
  for (int i = 2; i <= n; i++) {
    trace_compare(i - 1, i - 2);          /* die beiden Vorgänger */
    f[i] = f[i - 1] + f[i - 2];
    trace_set(i, f[i]);
    trace_mark_sorted(i);
  }
  trace_found(n);
  trace_done();
  trace_finish();

  printf("fib(%d) = %d\n", n, f[n]);
  return 0;
}
