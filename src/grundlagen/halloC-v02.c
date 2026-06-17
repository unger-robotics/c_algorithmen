// ju -- https://bw1.eu -- 26-Dez-18  -- halloC-v02.c 
/* ju - 14.1.18 halloWelt.c */
#include <stdio.h>
#include <stdlib.h>   // rand()
#include <time.h>     // time()
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include "meineFkt.h" // eig. Bibliothek

#define DIM 6         // Array-DIMENSION
const float LICHT = 2.99793E8;
const float PI    = 3.1415926535897932384;
const float E     = 2.7182818284590452354;
const int SEK_PRO_TAG = (60 * 60 * 24);    // Sekunden pro Tag
int main(void){
	char *msg = "\nHallo Welt!\n\n";
	printf("%s",msg);
	//printf("\nBeenden mit [Enter]...\n");
	//getchar(); // Speicherkontrolle, haelt Programm im RAM
  return 0;
}
/* Ausgabe 

*/
