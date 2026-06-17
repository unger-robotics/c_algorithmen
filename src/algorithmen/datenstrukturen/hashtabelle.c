/* ju -- 2026 -- hashtabelle.c
 * Hashtabelle mit Verkettung (Chaining): die Hashfunktion h(k)=k mod B legt
 * den Bucket fest; Kollisionen landen in einer Liste am selben Bucket.
 * Durchschnittlich O(1) für Einfügen und Suchen.
 */
#include <stdio.h>
#include "trace.h"

#define B 5

static int bucket_ids[B][32];
static int blen[B];
static int id2key[256];
static int idc = 0;

int main(int argc, char **argv) {
  trace_init(argc, argv);
  trace_begin("hashtabelle", "Hashtabelle (Chaining)", "tree");
  trace_init_layout("hash");
  trace_note("Hashtabelle: Schlüssel per h(k)=k mod 5 auf Buckets verteilen.");

  int keys[] = {12, 5, 22, 7, 17, 9};
  int n = (int)(sizeof keys / sizeof keys[0]);

  for (int i = 0; i < n; i++) {
    int k = keys[i], h = k % B, id = idc++;
    id2key[id] = k;
    trace_node(id, k, -1, NULL);
    bucket_ids[h][blen[h]++] = id;
    trace_bucket(h, bucket_ids[h], blen[h]);
  }

  int gesucht = 17, h = gesucht % B, pos = -1;
  trace_note("Suche 17: Bucket h(17)=2 durchlaufen.");
  for (int k = 0; k < blen[h]; k++) {
    int id = bucket_ids[h][k];
    trace_visit(id);
    if (id2key[id] == gesucht) { trace_found(id); pos = k; break; }
  }
  trace_done();
  trace_finish();

  for (int b = 0; b < B; b++) {
    printf("Bucket[%d]:", b);
    for (int k = 0; k < blen[b]; k++) printf(" %d", id2key[bucket_ids[b][k]]);
    printf("\n");
  }
  printf("17 %s (Bucket %d, Kettenposition %d)\n", pos >= 0 ? "gefunden" : "nicht gefunden", h, pos);
  return 0;
}
