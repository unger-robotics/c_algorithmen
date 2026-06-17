/* ju -- 26-Dez-18 -- logik-v02.c
   Logik in C: UND (&) - ODER (|) - XOR (^) - NEG (!)  (Textausgabe)
*/
#include <stdio.h>
#include "trace.h"

int main(int argc, char **argv) {
  char *msg = "\nLogik in C\n\nUND (&) - ODER (|) - XOR (^) - NEG (!)\n";
  int E1 = 0, E2 = 0;
  int UND, ODER, XOR, NEG;

  /* --- Trace (view "logik"): Wahrheitstabelle zeilenweise --- */
  trace_init(argc, argv);
  trace_begin("logik-v02", "Logik: UND / ODER / XOR / NEG", "logik");
  trace_init_none();
  trace_note("Wahrheitstabelle: alle Eingangskombinationen E1,E2 durchgehen.");
  for (E1 = 0; E1 <= 1; E1++)
    for (E2 = 0; E2 <= 1; E2++) {
      int v[6] = { E1, E2, E1 & E2, E1 | E2, E1 ^ E2, !E1 };
      trace_truthrow(v, 6);
    }
  trace_done();
  trace_finish();

  printf("%s", msg);

  // UND (&) - ODER (|) - XOR (^)
  printf("\n  E1  E2  UND  ODER  XOR  \n");
  for (E1 = 0; E1 <= 1; E1++)
    for (E2 = 0; E2 <= 1; E2++) {
      UND = E1 & E2; ODER = E1 | E2; XOR = E1 ^ E2;
      printf("  %d  %d  %d  %d  %d  \n", E1, E2, UND, ODER, XOR);
    }

  // NEG (!)
  printf("\n  E1  NEG  \n");
  for (E1 = 0; E1 <= 1; E1++) {
    NEG = E1;
    printf("  %d  %d  \n", E1, !NEG);
  }
  return 0;
}
