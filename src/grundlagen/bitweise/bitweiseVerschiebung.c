/* ju - 15.1.18 - bitweiseVerschiebung.c
   bitweise Verschiebung:
     x << y = Bits nach links  (Multiplikation mit 2^y)
     x >> y = Bits nach rechts (Ganzzahl-Division durch 2^y)
*/
#include "bitsviz.h"

int main(int argc, char **argv) {
  int W = 12, x = 41;
  int in[12], t[12];
  bits_of((unsigned)x, in, W);

  trace_init(argc, argv);
  trace_begin("bitweiseVerschiebung", "Bitweise Verschiebung (<< >>)", "bits");
  trace_init_none();
  trace_bitrow(0, "x = 41", in, W);
  trace_note("x << 1 verdoppelt, x >> 1 halbiert: die Bits wandern um eine Stelle.");

  char lbl[40];
  bits_of((unsigned)(x << 1), t, W); snprintf(lbl, sizeof lbl, "x << 1 = %d", x << 1);
  trace_note("Linksschieben um 1: alle Bits eine Position nach links (× 2)."); trace_bitrow(1, lbl, t, W);
  bits_of((unsigned)(x >> 1), t, W); snprintf(lbl, sizeof lbl, "x >> 1 = %d", x >> 1);
  trace_note("Rechtsschieben um 1: alle Bits eine Position nach rechts (÷ 2)."); trace_bitrow(2, lbl, t, W);
  bits_of((unsigned)(x << 2), t, W); snprintf(lbl, sizeof lbl, "x << 2 = %d", x << 2);
  trace_note("Linksschieben um 2 (× 4)."); trace_bitrow(3, lbl, t, W);
  bits_of((unsigned)(x << 3), t, W); snprintf(lbl, sizeof lbl, "x << 3 = %d", x << 3);
  trace_note("Linksschieben um 3 (× 8)."); trace_bitrow(4, lbl, t, W);

  trace_done();
  trace_finish();

  printf("\nBitweise Verschiebung\n\n");
  printf("x      = %3d = 0b", x);      print_bits(in, W); printf("\n");
  bits_of((unsigned)(x << 1), t, W); printf("x << 1 = %3d = 0b", x << 1); print_bits(t, W); printf("\n");
  bits_of((unsigned)(x >> 1), t, W); printf("x >> 1 = %3d = 0b", x >> 1); print_bits(t, W); printf("\n");
  bits_of((unsigned)(x << 2), t, W); printf("x << 2 = %3d = 0b", x << 2); print_bits(t, W); printf("\n");
  bits_of((unsigned)(x << 3), t, W); printf("x << 3 = %3d = 0b", x << 3); print_bits(t, W); printf("\n");
  return 0;
}
