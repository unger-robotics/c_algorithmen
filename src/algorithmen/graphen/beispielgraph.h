/* ju -- 2026 -- beispielgraph.h
 * Gemeinsamer Beispielgraph für BFS/DFS/Dijkstra: 6 Knoten (A..F) mit festen
 * Koordinaten (0..100) und ungerichteten, gewichteten Kanten. graph_aufbauen()
 * meldet Knoten und Kanten an den Trace und füllt die Gewichtsmatrix g_adj.
 */
#ifndef BEISPIELGRAPH_H
#define BEISPIELGRAPH_H
#include "trace.h"

#define GN 6
static const char *G_LABEL[GN] = {"A", "B", "C", "D", "E", "F"};
static const int   G_X[GN]     = {12, 50, 30, 72, 18, 60};
static const int   G_Y[GN]     = {25, 12, 52, 40, 85, 82};

#define GE 8
static const int G_EDGE[GE][3] = {  /* from, to, gewicht */
  {0, 1, 2}, {0, 2, 4}, {1, 3, 5}, {2, 3, 1},
  {2, 4, 3}, {2, 5, 6}, {3, 5, 2}, {4, 5, 4}
};

static int g_adj[GN][GN];   /* Gewichtsmatrix, 0 = keine Kante */

static void graph_aufbauen(void) {
  for (int i = 0; i < GN; i++) trace_gnode(i, G_LABEL[i], G_X[i], G_Y[i]);
  for (int e = 0; e < GE; e++) {
    int a = G_EDGE[e][0], b = G_EDGE[e][1], w = G_EDGE[e][2];
    trace_gedge(a, b, w, 0);
    g_adj[a][b] = w; g_adj[b][a] = w;
  }
}

#endif
