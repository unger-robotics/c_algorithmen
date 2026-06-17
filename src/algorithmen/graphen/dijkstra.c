/* ju -- 2026 -- dijkstra.c
 * Dijkstra: kürzeste Wege von einem Startknoten in einem gewichteten Graphen
 * mit nichtnegativen Kanten. Wähle stets den nächsten unfertigen Knoten und
 * relaxiere seine Kanten. Laufzeit hier O(V^2).
 */
#include <stdio.h>
#include "beispielgraph.h"

#define INF 1000000000

int main(int argc, char **argv) {
  trace_init(argc, argv);
  trace_begin("dijkstra", "Dijkstra (kürzeste Wege)", "graph");
  trace_init_none();
  trace_note("Dijkstra ab A: Distanzen schätzen und über Kanten verbessern (relaxieren).");
  graph_aufbauen();

  int start = 0, ziel = 5;        /* A -> F */
  int dist[GN], fertig[GN] = {0}, vorg[GN];
  for (int i = 0; i < GN; i++) { dist[i] = INF; vorg[i] = -1; trace_set_dist(i, INF); }
  dist[start] = 0; trace_set_dist(start, 0);

  for (int it = 0; it < GN; it++) {
    // Greedy-Auswahl: unter den noch nicht "fertigen" Knoten den mit der kleinsten
    // bekannten Distanz nehmen. Bei nichtnegativen Kanten ist dessen dist endgültig.
    int u = -1, best = INF;
    for (int i = 0; i < GN; i++) if (!fertig[i] && dist[i] < best) { best = dist[i]; u = i; }
    if (u < 0) break;               // nur noch unerreichbare Knoten übrig
    fertig[u] = 1;
    trace_visit(u);
    // Kanten von u relaxieren: ist der Weg über u kürzer als die bisherige
    // Schätzung für v, wird dist[v] (und der Vorgänger) verbessert.
    for (int v = 0; v < GN; v++) {
      if (g_adj[u][v] && !fertig[v]) {
        trace_relax(u, v, dist[u] + g_adj[u][v]);
        if (dist[u] + g_adj[u][v] < dist[v]) {
          dist[v] = dist[u] + g_adj[u][v];
          vorg[v] = u;              // kürzester bekannter Weg zu v führt jetzt über u
          trace_set_dist(v, dist[v]);
        }
      }
    }
  }

  /* kürzesten Pfad zum Ziel rekonstruieren */
  int pfad[GN], plen = 0;
  for (int x = ziel; x >= 0; x = vorg[x]) pfad[plen++] = x;   // Vorgängerkette vom Ziel rückwärts ablaufen
  int rev[GN] = {0};
  for (int i = 0; i < plen; i++) rev[i] = pfad[plen - 1 - i];
  trace_path(rev, plen);
  trace_done();
  trace_finish();

  printf("Kürzeste Distanz A->%s: %d\n", G_LABEL[ziel], dist[ziel]);
  printf("Pfad:");
  for (int i = 0; i < plen; i++) printf(" %s", G_LABEL[rev[i]]);
  printf("\n");
  return 0;
}
