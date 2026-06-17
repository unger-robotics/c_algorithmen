/* ju -- 2026 -- naive_suche.c
 * Naive Textsuche: das Muster an jeder Position des Textes anlegen und Zeichen
 * für Zeichen vergleichen. Schlechtester Fall O(n*m), einfach zu verstehen.
 */
#include <stdio.h>
#include <string.h>
#include "trace.h"

int main(int argc, char **argv) {
  char text[] = "ALGORITHMUS";
  char muster[] = "GOR";
  int n = (int)strlen(text), m = (int)strlen(muster);

  trace_init(argc, argv);
  trace_begin("naive_suche", "Naive Textsuche", "array");
  trace_init_string(text);
  trace_note("Muster \"GOR\" an jeder Position anlegen und vergleichen.");

  int pos = -1;
  for (int i = 0; i + m <= n; i++) {   // i = Startposition, an der das Muster angelegt wird
    trace_pointer("start", i);
    int passt = 1;
    for (int j = 0; j < m; j++) {
      trace_compare(i + j, i + j);
      // schon ein ungleiches Zeichen genügt: Muster um eine Position weiterschieben.
      if (text[i + j] != muster[j]) { passt = 0; break; }
    }
    if (passt) {
      for (int j = 0; j < m; j++) trace_mark_sorted(i + j);
      trace_found(i);
      pos = i;
      break;
    }
  }
  trace_done();
  trace_finish();

  if (pos >= 0) printf("Muster \"%s\" gefunden ab Position %d.\n", muster, pos);
  else          printf("Muster \"%s\" nicht gefunden.\n", muster);
  return 0;
}
