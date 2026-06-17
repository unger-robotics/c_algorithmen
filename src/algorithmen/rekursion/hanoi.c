/* ju -- 2026 -- hanoi.c
 * Türme von Hanoi: bewege n Scheiben von 'von' nach 'nach' über 'ueber'.
 * Lösung rekursiv: erst n-1 Scheiben beiseite, größte Scheibe ans Ziel, dann
 * n-1 Scheiben darauf. Es sind 2^n - 1 Züge nötig. Der Aufrufbaum zeigt die
 * Zerlegung in Teilprobleme.
 */
#include <stdio.h>
#include "trace.h"

static int idc = 0;
static int zuege = 0;

static void hanoi(int n, char von, char nach, char ueber, int parent, const char *seite) {
  int id = idc++;
  trace_node(id, n, parent, seite);    /* Knoten = ein Aufruf hanoi(n, ...) */
  if (n == 1) {
    char buf[64];
    snprintf(buf, sizeof buf, "Scheibe 1: %c -> %c", von, nach);
    trace_note(buf);
    zuege++;
    return;
  }
  hanoi(n - 1, von, ueber, nach, id, "left");   // 1. obere n-1 Scheiben auf den Hilfsstab
  char buf[64];
  snprintf(buf, sizeof buf, "Scheibe %d: %c -> %c", n, von, nach);
  trace_note(buf);                              // 2. die größte Scheibe direkt ans Ziel
  zuege++;
  hanoi(n - 1, ueber, nach, von, id, "right");  // 3. die n-1 Scheiben vom Hilfsstab nachziehen
}

int main(int argc, char **argv) {
  trace_init(argc, argv);
  trace_begin("hanoi", "Türme von Hanoi", "tree");
  trace_init_layout("tree");
  trace_note("Türme von Hanoi: rekursiv n-1 Scheiben umlagern, größte bewegen, wieder auflegen.");

  int n = 3;
  hanoi(n, 'A', 'C', 'B', -1, NULL);
  trace_done();
  trace_finish();

  printf("Türme von Hanoi mit %d Scheiben: %d Züge.\n", n, zuege);
  return 0;
}
