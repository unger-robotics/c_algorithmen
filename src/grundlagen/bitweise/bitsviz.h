/* ju -- 2026 -- bitsviz.h
   Kleine Helfer für die Bit-Visualisierung (view "bits"). */
#ifndef BITSVIZ_H
#define BITSVIZ_H
#include <stdio.h>
#include "trace.h"

/* schreibt die n niederwertigsten Bits von v als 0/1 nach out (MSB zuerst). */
static inline void bits_of(unsigned v, int *out, int n) {
  for (int i = 0; i < n; i++) out[i] = (int)((v >> (n - 1 - i)) & 1u);
}

/* gibt die Bits gruppiert (Vierergruppen) auf stdout aus. */
static inline void print_bits(const int *b, int n) {
  for (int i = 0; i < n; i++) {
    putchar('0' + (b[i] < 0 ? 0 : b[i]));
    if ((n - 1 - i) % 4 == 0 && i < n - 1) putchar(' ');
  }
}

#endif
