/* ju -- 2026 -- mergesort.c
 * Mergesort (top-down): teile das Feld rekursiv in zwei Hälften und füge die
 * sortierten Hälften wieder zusammen (merge). Stabil, Laufzeit O(n log n),
 * braucht O(n) Zusatzspeicher.
 */
#include <stdio.h>
#include "trace.h"

static int a[]   = {5, 2, 8, 1, 9, 3, 7, 4, 6};
static int n     = (int)(sizeof a / sizeof a[0]);
static int tmp[16];

/* Führt die zwei bereits sortierten Hälften [lo..mid] und [mid+1..hi] zusammen. */
static void merge(int lo, int mid, int hi) {
  for (int k = lo; k <= hi; k++) tmp[k] = a[k];   // beide Hälften in den Puffer kopieren
  int i = lo, j = mid + 1, k = lo;                // i: linke Hälfte, j: rechte Hälfte, k: Schreibposition
  // Solange in beiden Hälften noch etwas liegt, das jeweils kleinere Element nach
  // vorne schreiben. "<=" nimmt bei Gleichstand das linke zuerst -> Mergesort ist stabil.
  while (i <= mid && j <= hi) {
    trace_compare(i, j);
    if (tmp[i] <= tmp[j]) { a[k] = tmp[i]; trace_set(k, tmp[i]); i++; }
    else                  { a[k] = tmp[j]; trace_set(k, tmp[j]); j++; }
    k++;
  }
  // Eine Hälfte ist erschöpft; der Rest der anderen ist schon sortiert und wird angehängt.
  while (i <= mid) { a[k] = tmp[i]; trace_set(k, tmp[i]); i++; k++; }
  while (j <= hi)  { a[k] = tmp[j]; trace_set(k, tmp[j]); j++; k++; }
}

static void mergesort(int lo, int hi) {
  if (lo >= hi) return;
  int mid = (lo + hi) / 2;
  mergesort(lo, mid);
  mergesort(mid + 1, hi);
  merge(lo, mid, hi);
}

static void drucke(const char *titel) {
  printf("%s", titel);
  for (int i = 0; i < n; i++) printf("%d ", a[i]);
  printf("\n");
}

int main(int argc, char **argv) {
  trace_init(argc, argv);
  trace_begin("mergesort", "Mergesort", "array");
  trace_init_array(a, n);
  trace_note("Mergesort: rekursiv halbieren und sortierte Hälften zusammenführen.");

  mergesort(0, n - 1);

  for (int i = 0; i < n; i++) trace_mark_sorted(i);
  trace_done();
  trace_finish();
  drucke("Sortiert: ");
  return 0;
}
