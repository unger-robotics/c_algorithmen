/* ju - 15.1.18 - bitweisesODER.c
   bitweises ODER (|): Ergebnisbit ist 1, wenn mindestens ein Eingangsbit 1 ist.
*/
#include "bitsviz.h"

int main(int argc, char **argv) {
  int A = 10, B = 12, W = 8;
  int a[8], b[8], r[8];
  bits_of((unsigned)A, a, W);
  bits_of((unsigned)B, b, W);
  for (int i = 0; i < W; i++) r[i] = -1;

  trace_init(argc, argv);
  trace_begin("bitweisesODER", "Bitweises ODER (|)", "bits");
  trace_init_none();
  trace_bitrow(0, "A = 10", a, W);
  trace_bitrow(1, "B = 12", b, W);
  trace_bitrow(2, "A | B", r, W);
  trace_note("Spaltenweise: Ergebnisbit = (A-Bit) ODER (B-Bit), also 1 wenn mindestens eins 1 ist.");
  for (int c = 0; c < W; c++) { trace_bitcol(c); int v = a[c] | b[c]; trace_bitset(2, c, v); r[c] = v; }
  trace_done();
  trace_finish();

  printf("\nBitweises ODER (|)\n\n");
  printf("A    = %3d = 0b", A);     print_bits(a, W); printf("\n");
  printf("B    = %3d = 0b", B);     print_bits(b, W); printf("\n");
  printf("A|B  = %3d = 0b", A | B); print_bits(r, W); printf("\n");
  return 0;
}
