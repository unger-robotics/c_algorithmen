/* ju - 14.1.18 - bitweisesEinerkomplement.c
   bitweises Einerkomplement (~): jedes Bit wird gekippt (0<->1).
   Das Zweierkomplement (Einerkomplement + 1) ergibt das negative Vorzeichen.
*/
#include "bitsviz.h"

int main(int argc, char **argv) {
  int A = 10, W = 8;
  int a[8], r[8];
  bits_of((unsigned)A, a, W);
  for (int i = 0; i < W; i++) r[i] = -1;

  trace_init(argc, argv);
  trace_begin("bitweisesEinerkomplement", "Einerkomplement (~)", "bits");
  trace_init_none();
  trace_bitrow(0, "Wert = 10", a, W);
  trace_bitrow(1, "~Wert", r, W);
  trace_note("Jedes Bit kippen: aus 0 wird 1, aus 1 wird 0.");
  for (int c = 0; c < W; c++) { trace_bitcol(c); int v = a[c] ? 0 : 1; trace_bitset(1, c, v); r[c] = v; }
  trace_note("~10 = 0b11110101 (unsigned 245). Als vorzeichenbehaftete 8-Bit-Zahl (+1) entspricht das -11.");
  trace_done();
  trace_finish();

  printf("\nEinerkomplement (~)\n\n");
  printf("Wert  =  %3d = 0b", A);   print_bits(a, W); printf("\n");
  printf("~Wert = %4d = 0b", ~A);   print_bits(r, W); printf("   (unsigned 8-Bit: 245, signed: -11)\n");
  return 0;
}
