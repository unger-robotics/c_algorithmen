/* ju -- 2026 -- fibonacci.c
 * Naive rekursive Fibonacci: fib(n) = fib(n-1) + fib(n-2). Der Aufrufbaum
 * zeigt, dass dieselben Teilprobleme vielfach berechnet werden (exponentiell) —
 * die Motivation für dynamische Programmierung (siehe dynprog/fibonacci_dp).
 */
#include <stdio.h>
#include "trace.h"

static int idc = 0;

static int fib(int n, int parent, const char *seite) {
  int id = idc++;
  trace_node(id, n, parent, seite);   /* Knoten = ein Aufruf fib(n) */
  if (n < 2) return n;
  int l = fib(n - 1, id, "left");
  int r = fib(n - 2, id, "right");
  return l + r;
}

int main(int argc, char **argv) {
  trace_init(argc, argv);
  trace_begin("fibonacci", "Fibonacci (Aufrufbaum)", "tree");
  trace_init_layout("tree");
  trace_note("Rekursive Fibonacci: jeder Knoten ist ein Aufruf fib(n).");

  int n = 5;
  int ergebnis = fib(n, -1, NULL);
  trace_done();
  trace_finish();

  printf("fib(%d) = %d\n", n, ergebnis);
  return 0;
}
