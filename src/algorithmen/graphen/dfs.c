/* ju -- 2026 -- dfs.c
 * Tiefensuche (DFS): folgt jedem Pfad so weit wie möglich, bevor zurück-
 * gegangen wird (hier rekursiv). Laufzeit O(V+E).
 */
#include <stdio.h>
#include "beispielgraph.h"

static int besucht[GN];
static int reihenfolge[GN], rlen;

static void dfs(int u) {
  besucht[u] = 1;
  trace_visit(u);
  reihenfolge[rlen++] = u;
  // In den ersten unbesuchten Nachbarn absteigen und erst danach den nächsten
  // probieren. Die Rekursion ist hier der (implizite) Stack der Tiefensuche.
  for (int v = 0; v < GN; v++)
    if (g_adj[u][v] && !besucht[v]) dfs(v);
}

int main(int argc, char **argv) {
  trace_init(argc, argv);
  trace_begin("dfs", "Tiefensuche (DFS)", "graph");
  trace_init_none();
  trace_note("DFS ab A: einem Pfad bis zum Ende folgen, dann zurückgehen.");
  graph_aufbauen();

  dfs(0);
  trace_done();
  trace_finish();

  printf("DFS-Reihenfolge ab A:");
  for (int i = 0; i < rlen; i++) printf(" %s", G_LABEL[reihenfolge[i]]);
  printf("\n");
  return 0;
}
