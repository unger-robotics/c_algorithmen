/* ju -- 2026 -- rucksack.c
 * 0/1-Rucksackproblem mit dynamischer Programmierung (platzsparend, 1D):
 * dp[w] = bester Wert bei Kapazität w. Pro Gegenstand wird dp von hinten nach
 * vorne aktualisiert, damit jeder Gegenstand höchstens einmal zählt.
 * Laufzeit O(nGegenstaende * W).
 */
#include <stdio.h>
#include "trace.h"

int main(int argc, char **argv) {
  int W = 10;
  int gewicht[] = {2, 3, 4, 5};
  int wert[]    = {3, 4, 5, 6};
  int anzahl = (int)(sizeof gewicht / sizeof gewicht[0]);
  int dp[32] = {0}, init[32] = {0};

  trace_init(argc, argv);
  trace_begin("rucksack", "0/1-Rucksack (DP)", "array");
  trace_init_array(init, W + 1);
  trace_note("dp[w] = bester Wert bei Kapazität w; Index = Kapazität 0..W.");

  for (int g = 0; g < anzahl; g++) {
    char buf[80];
    snprintf(buf, sizeof buf, "Gegenstand %d: Gewicht %d, Wert %d", g + 1, gewicht[g], wert[g]);
    trace_note(buf);
    for (int w = W; w >= gewicht[g]; w--) {
      trace_compare(w, w - gewicht[g]);
      int kandidat = dp[w - gewicht[g]] + wert[g];
      if (kandidat > dp[w]) { dp[w] = kandidat; trace_set(w, dp[w]); }
    }
  }
  trace_found(W);
  trace_done();
  trace_finish();

  printf("Maximaler Wert bei Kapazität %d: %d\n", W, dp[W]);
  return 0;
}
