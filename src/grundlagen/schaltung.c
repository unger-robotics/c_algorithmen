/* ju -- 26-Dez-18 -- schaltung.c
   Berechnet Schaltkombinationen einer elektrischen Schaltung.
   Lampe = (s1||s2) && ((s3&&s4) || ((s5||s6)&&s7))
   Mit --trace <datei> werden alle 128 Schalterstellungen für den Web-Player
   aufgezeichnet (view "schaltung").
*/
#include <stdio.h>
#include "trace.h"

int main(int argc, char **argv) {
  int lampe = 0, schaltkombination = 0;
  int zaehler = 0;

  trace_init(argc, argv);
  trace_begin("schaltung", "Schaltung: (s1|s2)&((s3&s4)|((s5|s6)&s7))", "schaltung");
  trace_init_none();
  trace_note("Alle 128 Schalterstellungen durchprobieren; die Lampe leuchtet, wenn der Ausdruck wahr ist.");

  printf("|Zaehler | s1 | s2 | s3 | s4 | s5 | s6 | s7 | Lampe|\n");
  printf("---------------\n");
  for (int s1 = 0; s1 <= 1; s1++)
   for (int s2 = 0; s2 <= 1; s2++)
    for (int s3 = 0; s3 <= 1; s3++)
     for (int s4 = 0; s4 <= 1; s4++)
      for (int s5 = 0; s5 <= 1; s5++)
       for (int s6 = 0; s6 <= 1; s6++)
        for (int s7 = 0; s7 <= 1; s7++) {
          /* Schaltstellung berechnen */
          lampe = (s1 || s2) && ((s3 && s4) || ((s5 || s6) && s7));
          schaltkombination++;
          int s[7] = { s1, s2, s3, s4, s5, s6, s7 };
          trace_circuit(schaltkombination, s, 7, lampe);
          if (lampe == 1) {
            zaehler++;
            /* Ausgabe nur wenn die Lampe an ist! */
            printf("| %6d | %2d | %2d | %2d | %2d | %2d | %2d | %2d | %5d |\n",
                   zaehler, s1, s2, s3, s4, s5, s6, s7, lampe);
          }
        }

  trace_done();
  trace_finish();

  printf("Schaltkombination gesamt: %d - Lampe ON: %d\n", schaltkombination, zaehler);
  return 0;
}
