/* ju 11-12-2016 meineFkt.c */
/* Implementierung eig. C-Funktionsbibliothek	*/

#include "meineFkt.h"

//Funktion - Fakultaet
int fac( int i ) {
	if (i <= 0) return 1;
	return i * fac( i-1 );
}

//Funktion - Quersumme in beliebigem Zahlensystem
int quersumme(int z, int b) {//Definition einer Funktion
  int q = 0;
  while(z > 0){
    q += z % b;
    z /= b;
  }
  return q;
}

//Funktion - ganze Zahlen potenzieren
int quadriere(int z){
  return z*z;
}

//Funktion - dritte Potenz
int drittePotenz(int z){
  return z*z*z;
}

//Funktion - x hoch y, für x,y >= 0
/*
3 hoch 4 = 1* 3 * 3 * 3 * 3
         --- //trick
3 hoch 0 = 1
*/  
unsigned long potenziere(int x, int y){ //basis, exponent
  unsigned long r = 1;
  for(int i = 0; i < y; i++){
    r *= x;
  }
  return r;
}


