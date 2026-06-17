// ju -- 2026 -- test_meinefkt.c
// Unit-Tests fuer die reinen Funktionen aus lib/meineFkt.c. Diese Funktionen
// werden von keinem Demo-Programm aufgerufen (nur mitkompiliert), daher pruefen
// weder Golden- noch Sanitizer-Tests ihre Korrektheit -- genau das holt dieser
// Test nach. Klassisch assert-basiert: Exit 0 = ok, Abbruch via assert = Fehler.

#include <assert.h>
#include <stdio.h>
#include "meineFkt.h"

int main(void) {
  // fac: Fakultaet, rekursiv. Vertrag: i <= 0 liefert 1 (Grenzfall ist drin).
  assert(fac(0) == 1);
  assert(fac(1) == 1);
  assert(fac(5) == 120);
  assert(fac(-3) == 1);

  // quersumme: Ziffernsumme von z zur Basis b.
  assert(quersumme(0, 10) == 0);     // leere Schleife
  assert(quersumme(123, 10) == 6);   // 1+2+3
  assert(quersumme(5, 2) == 2);      // 101b -> 1+0+1

  // quadriere / drittePotenz: Vorzeichen korrekt mitnehmen.
  assert(quadriere(0) == 0);
  assert(quadriere(-5) == 25);
  assert(drittePotenz(3) == 27);
  assert(drittePotenz(-2) == -8);

  // potenziere: x hoch y, Vertrag x,y >= 0. Bewusst kein Overflow-Fall (UB).
  assert(potenziere(2, 0) == 1UL);
  assert(potenziere(0, 0) == 1UL);   // dokumentierte Konvention 0^0 = 1
  assert(potenziere(2, 10) == 1024UL);
  assert(potenziere(10, 5) == 100000UL);

  printf("test_meinefkt: OK\n");
  return 0;
}
