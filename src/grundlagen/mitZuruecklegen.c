/* ju - 15.1.18 - mitZuruecklegen.c
   Urnenmodell mit Zuruecklegen - Lotto 6 aus 49.
   Mit --trace <datei> werden die 6 Ziehungen für den Web-Player aufgezeichnet
   (view "lotto"); dabei wird ein fester Seed genutzt, damit der Trace
   reproduzierbar ist.
*/
#include <stdio.h>
#include <stdlib.h> // rand()
#include <time.h>   // time()
#include "trace.h"
#define DIM 6       // Anzahl Ziehungen

int main(int argc, char **argv) {
  trace_init(argc, argv);
  srand(trace_is_active() ? 12345u : (unsigned)time(NULL));

  int ziehung[DIM] = {0};
  for (int i = 0; i < DIM; i++) ziehung[i] = rand() % 49 + 1;  // Zufallszahl 1..49

  /* --- Trace (view "lotto"): 7x7-Gitter, Ziehungen hervorheben --- */
  int zahlen[49];
  for (int i = 0; i < 49; i++) zahlen[i] = i + 1;
  trace_begin("mitZuruecklegen", "Lotto 6 aus 49 (mit Zurücklegen)", "lotto");
  trace_init_array(zahlen, 49);
  trace_note("6-mal eine Zufallszahl 1..49 ziehen — mit Zurücklegen, Wiederholung möglich.");
  for (int i = 0; i < DIM; i++) {
    char buf[64];
    snprintf(buf, sizeof buf, "Ziehung %d von 6: Zahl %d", i + 1, ziehung[i]);
    trace_note(buf);
    trace_mark_sorted(ziehung[i] - 1);
  }
  trace_done();
  trace_finish();

  /* --- Terminal-Ausgabe (Markdown / LaTeX / CSV) --- */
  printf("\nUrnenmodell mit Zuruecklegen - Lotto 6 aus 49\n");

  printf("\nAusgabe - Markdown\n\n");
  printf("| **Ziehung** | **Inhalt** |\n");
  printf("|------------:|-----------:|\n");
  for (int i = 0; i < DIM; i++) printf("| %11d | %10d |\n", i + 1, ziehung[i]);

  printf("\nAusgabe - LaTeX\n\n");
  printf("\\textbf{Ziehung} & \\textbf{Inhalt} \\\\ \n");
  for (int i = 0; i < DIM; i++) printf("%d & %2d \\\\ \n", i + 1, ziehung[i]);

  printf("\nAusgabe - Excel\n\n");
  printf("Ziehung;Inhalt\n");
  for (int i = 0; i < DIM; i++) printf("%d;%d\n", i + 1, ziehung[i]);

  return 0;
}
