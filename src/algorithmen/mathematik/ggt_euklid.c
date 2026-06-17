/* ju -- 2026 -- ggt_euklid.c
 * Größter gemeinsamer Teiler nach Euklid: ggT(a,b) = ggT(b, a mod b), bis b 0
 * wird. Sehr schnell, Laufzeit O(log min(a,b)). Hier als zwei schrumpfende
 * Balken (a und b) dargestellt.
 */
#include <stdio.h>
#include "trace.h"

int main(int argc, char **argv) {
  int a = 48, b = 36;
  int arr[2] = { a, b };

  trace_init(argc, argv);
  trace_begin("ggt_euklid", "ggT (Euklid)", "array");
  trace_init_array(arr, 2);
  trace_pointer("a", 0);
  trace_pointer("b", 1);
  trace_note("ggT(a,b) = ggT(b, a mod b), bis b = 0.");

  while (b != 0) {
    trace_compare(0, 1);
    int r = a % b;
    a = b; b = r;
    trace_set(0, a);
    trace_set(1, b);
  }
  trace_mark_sorted(0);
  trace_done();
  trace_finish();

  printf("ggT(48, 36) = %d\n", a);
  return 0;
}
