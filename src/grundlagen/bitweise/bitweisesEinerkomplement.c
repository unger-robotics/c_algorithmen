/* ju - 14.1.18 - bitweisesEinerkomplement.c
   bitweises Einerkomplement
*/
#include <stdio.h>
int main(void){
	char *message = "\nbitweises Einerkomplement\n\n";
	char *tblKopf    = "|                |      |             |    | \n";
	char *tblStrich  = "|:---------------|-----:|------------:|---:| \n";
	int zahl1 = 0b00001010; // 10
	int a = ~zahl1;

	printf("%s",message);	

	printf("%s",tblKopf);
	printf("%s",tblStrich);
	printf("| 2er Komplement | ~%3d | 0b0000'1010 |    | \n", zahl1);
	printf("| 1er Komplement |      | 0b1111'0101 | +1 | \n");
	printf("| Erg.           |  %3d | 0b1111'0110 |    | \n", a);
  return 0;
}
/* Ausgabe 
bitweises Einerkomplement

|                |      |             |    | 
|:---------------|-----:|------------:|---:| 
| 2er Komplement | ~ 10 | 0b0000'1010 |    | 
| 1er Komplement |      | 0b1111'0101 | +1 | 
| Erg.           |  -11 | 0b1111'0110 |    |
*/
