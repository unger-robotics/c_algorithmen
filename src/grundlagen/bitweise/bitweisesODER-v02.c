/* ju -- 2026 -- bitweisesODER-v02.c
   bitweises ODER (|) — Tabelle mit Dezimal, Hexadezimal und Binaer.
   macOS-portiert: das Windows-spezifische itoa() wurde durch binstr() ersetzt.
*/
#include <stdio.h>
#include <stddef.h>

/* binstr: vorzeichenlose Zahl -> Binaerstring (Ersatz fuer itoa(zahl,puffer,2)).
   Fuehrende Nullen werden weggelassen; die Zahl 0 ergibt "0". */
static char *binstr(unsigned int wert, char *puffer, size_t n) {
  size_t i = 0;
  int begonnen = 0;
  for (int b = (int)(sizeof(wert) * 8) - 1; b >= 0 && i + 1 < n; b--) {
    unsigned int bit = (wert >> b) & 1u;
    if (bit) begonnen = 1;
    if (begonnen || b == 0) puffer[i++] = (char)('0' + bit);
  }
  puffer[i] = '\0';
  return puffer;
}

int main(void) {
  char puffer[33];
  unsigned int E1   = 12;        /* 0b1100 */
  unsigned int E2   = 10;        /* 0b1010 */
  unsigned int oder = E1 | E2;   /* 0b1110 = 14 */

  printf("\nbitweises ODER (|)\n\n");
  printf("  Operanden   DEZ   HEX   BIN\n");
  printf("  #           %3u   0x%x   0b%s\n", E1,   E1,   binstr(E1,   puffer, sizeof puffer));
  printf("  ODER        %3u   0x%x   0b%s\n", E2,   E2,   binstr(E2,   puffer, sizeof puffer));
  printf("  Erg.        %3u   0x%x   0b%s\n", oder, oder, binstr(oder, puffer, sizeof puffer));
  return 0;
}
/* Ausgabe
bitweises ODER (|)

  Operanden   DEZ   HEX   BIN
  #            12   0xc   0b1100
  ODER         10   0xa   0b1010
  Erg.         14   0xe   0b1110
*/
