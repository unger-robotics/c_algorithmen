/* ju - 15.1.18 - bitweisesODER.c 
   bitweises ODER (|)
*/
#include <stdio.h>
int main(void){
	char *message = "\nbitweises ODER (|)\n\n";
	char *tblKopf    = "| **Operanden** | **Dezimal** | **Binär**   | \n";
	char *tblStrich  = "|:--------------|------------:|------------:| \n";
	int zahl1 = 0b00001010; // = 10
	int zahl2 = 0b00001100; // = 12
	int oder  = zahl1 | zahl2;

	printf("%s",message);

	printf("%s",tblKopf);
	printf("%s",tblStrich);
	printf("|               | %3d         | 0b0000'1010 | \n",zahl1);
	printf("| ODER          | %3d         | 0b0000'1100 | \n",zahl2);
	printf("| Erg.          | %3d         | 0b0000'1110 | \n",oder);
  return 0;
}
/* Ausgabe
bitweises ODER (|)

| **Operanden** | **Dezimal** | **Binär**   | 
|:--------------|------------:|------------:| 
|               |  10         | 0b0000'1010 | 
| ODER          |  12         | 0b0000'1100 | 
| Erg.          |  14         | 0b0000'1110 | 
*/

