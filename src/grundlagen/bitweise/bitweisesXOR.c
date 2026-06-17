/* ju - 15.1.18 - bitweisesXOR.c 
   bitweises XOR (^)
*/
#include <stdio.h>
int main(void){
	char *message = "\nbitweises XOR (^)\n\n";
	char *tblKopf    = "| **Operanden** | **Dezimal** | **Binär**   | \n";
	char *tblStrich  = "|:--------------|------------:|------------:| \n";
	int zahl1 = 0b00001010; // = 10
	int zahl2 = 0b00001100; // = 12
	int xor = zahl1 ^ zahl2;

	printf("%s",message);

	printf("%s",tblKopf);
	printf("%s",tblStrich);
	printf("|               | %3d         | 0b0000'1010 | \n",zahl1);
	printf("| XOR           | %3d         | 0b0000'1100 | \n",zahl2);
	printf("| Erg.          | %3d         | 0b0000'0110 | \n",xor);
  return 0;
}
/* Ausgabe
bitweises XOR (^)

| **Operanden** | **Dezimal** | **Binär**   | 
|:--------------|------------:|------------:| 
|               |  10         | 0b0000'1010 | 
| XOR           |  12         | 0b0000'1100 | 
| Erg.          |   6         | 0b0000'0110 | 
*/


