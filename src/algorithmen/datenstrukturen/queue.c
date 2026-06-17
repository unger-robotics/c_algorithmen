/* ju -- 2026 -- queue.c
 * Queue (Warteschlange, FIFO): enqueue hängt hinten an, dequeue nimmt vorne
 * weg. Wer zuerst kommt, geht zuerst. Hier mit verketteten Knoten gezeigt.
 */
#include <stdio.h>
#include "trace.h"

static int werte[64], ids[64];
static int kopf = 0, ende = 0, idc = 0;   /* [kopf, ende) ist belegt */

static void enqueue(int v) {
  int id = idc++;
  trace_node(id, v, -1, NULL);
  if (ende > kopf) trace_edge(ids[ende - 1], id);  /* next-Kante vom bisher letzten */
  werte[ende] = v; ids[ende] = id; ende++;
}
static int dequeue(void) {
  if (kopf >= ende) return -1;
  int id = ids[kopf], v = werte[kopf];
  trace_visit(id);
  trace_remove_node(id);
  kopf++;
  return v;
}

int main(int argc, char **argv) {
  trace_init(argc, argv);
  trace_begin("queue", "Queue (FIFO)", "tree");
  trace_init_layout("chain-h");
  trace_note("Queue: enqueue hängt hinten an, dequeue nimmt vorne weg.");

  enqueue(5); enqueue(3); enqueue(8); enqueue(1);
  trace_note("dequeue() entfernt das vorderste (zuerst eingefügte) Element.");
  dequeue(); dequeue();
  trace_note("enqueue(9) hängt hinten an.");
  enqueue(9);
  trace_done();
  trace_finish();

  printf("Queue von vorne: ");
  for (int i = kopf; i < ende; i++) printf("%d ", werte[i]);
  printf("\n");
  return 0;
}
