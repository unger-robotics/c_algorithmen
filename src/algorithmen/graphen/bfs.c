/* ju -- 2026 -- bfs.c
 * Breitensuche (BFS): besucht Knoten ebenenweise mit einer Warteschlange.
 * Findet in ungewichteten Graphen die kürzeste Kantenanzahl. Laufzeit O(V+E).
 */
#include <stdio.h>
#include "beispielgraph.h"

int main(int argc, char **argv) {
  trace_init(argc, argv);
  trace_begin("bfs", "Breitensuche (BFS)", "graph");
  trace_init_none();
  trace_note("BFS ab A: Nachbarn in eine Warteschlange legen und der Reihe nach besuchen.");
  graph_aufbauen();

  int start = 0;
  int queue[GN], head = 0, tail = 0;
  int besucht[GN] = {0};
  int reihenfolge[GN], rlen = 0;

  queue[tail++] = start; besucht[start] = 1;
  while (head < tail) {
    trace_frontier(queue + head, tail - head);   /* aktuelle Warteschlange */
    int u = queue[head++];
    trace_visit(u);
    reihenfolge[rlen++] = u;
    for (int v = 0; v < GN; v++)
      if (g_adj[u][v] && !besucht[v]) { besucht[v] = 1; queue[tail++] = v; }
  }
  trace_done();
  trace_finish();

  printf("BFS-Reihenfolge ab A:");
  for (int i = 0; i < rlen; i++) printf(" %s", G_LABEL[reihenfolge[i]]);
  printf("\n");
  return 0;
}
