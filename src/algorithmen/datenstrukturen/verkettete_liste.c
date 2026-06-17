/* ju -- 2026 -- verkettete_liste.c
 * Einfach verkettete Liste: jeder Knoten zeigt per next auf den nächsten.
 * Aufbau durch Anhängen, danach lineare Suche durch Durchlaufen der Kette.
 */
#include <stdio.h>
#include <stdlib.h>
#include "trace.h"

typedef struct Knoten { int wert; int id; struct Knoten *next; } Knoten;

int main(int argc, char **argv) {
  trace_init(argc, argv);
  trace_begin("verkettete_liste", "Verkettete Liste", "tree");
  trace_init_layout("chain-h");
  trace_note("Verkettete Liste: Knoten per next-Zeiger anhängen, dann suchen.");

  int werte[] = {4, 8, 15, 16, 23};
  int n = (int)(sizeof werte / sizeof werte[0]);
  Knoten *kopf = NULL, *last = NULL;

  for (int i = 0; i < n; i++) {
    Knoten *k = malloc(sizeof *k);
    if (!k) { perror("malloc"); exit(1); }   // bei Speichermangel sauber abbrechen
    k->wert = werte[i]; k->id = i; k->next = NULL;
    trace_node(i, werte[i], -1, NULL);
    // Hinten anhängen: next des bisher letzten Knotens auf den neuen zeigen lassen.
    // Beim ersten Knoten gibt es noch kein "last" -> er wird zum Kopf der Liste.
    if (last) { last->next = k; trace_edge(last->id, i); } else kopf = k;
    last = k;
  }

  int gesucht = 16;
  trace_note("Suche nach 16: Liste von vorne durchlaufen.");
  for (Knoten *k = kopf; k; k = k->next) {
    trace_visit(k->id);
    if (k->wert == gesucht) { trace_found(k->id); break; }
  }
  trace_done();
  trace_finish();

  printf("Liste: ");
  for (Knoten *k = kopf; k; k = k->next) printf("%d -> ", k->wert);
  printf("NULL\n");

  for (Knoten *k = kopf; k; ) { Knoten *nx = k->next; free(k); k = nx; }
  return 0;
}
