/* ju -- https://bw1.eu -- 26-Dez-18 -- bitweisesODER-v02.c 
   bitweises ODER (|)
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void){
	char *msg = "\nbitweises ODER (|)\n\n";
  char buffer[100];
	// unsigned int - 16-bit - 0 … 65535
	unsigned int E1 = 0;// 0b0000.1100 = 12
  unsigned int E2 = 65535; // 0b0000.0100 = 4
	unsigned int oder  = E1 | E2;

	printf("%s",msg);

  char *tblKopf    = "  Operanden  DEZ  HEX  BIN  \n";
	printf("%s",tblKopf);
	printf("  #  %d  0x%x  0b%s  \n", E1, E1, itoa(E1, buffer, 2));
	printf("  ODER  %d  0x%x  0b%s  \n", E2, E2, itoa(E2, buffer, 2));
	printf("  Erg.  %d  0x%x  0b%s  \n", oder, oder, itoa(oder, buffer, 2));
  return 0;
}
/* Ausgabe

*/

