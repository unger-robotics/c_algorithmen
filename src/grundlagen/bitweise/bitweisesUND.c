/* ju - 15.1.18 - bitweisesUND.c 
   bitweises UND (&)
*/
#include <stdio.h>
int main(void){
	char *message = "\nbitweises UND (&)\n\n";
	char *tblKopf    = "| **Operanden** | **Dezimal** | **Binär**   | \n";
	char *tblStrich  = "|:--------------|------------:|------------:| \n";
	int zahl1 = 0b00001010; // = 10
	int zahl2 = 0b00001100; // = 12
	int und = zahl1 & zahl2;

	printf("%s",message);

	printf("%s",tblKopf);
	printf("%s",tblStrich);
	printf("|               | %3d         | 0b0000'1010 | \n",zahl1);
	printf("| UND           | %3d         | 0b0000'1100 | \n",zahl2);
	printf("| Erg.          | %3d         | 0b0000'1000 | \n",und);
  return 0;
}
/* Ausgabe
bitweises UND (&)

| **Operanden** | **Dezimal** | **Binär**   | 
|:--------------|------------:|------------:| 
|               |  10         | 0b0000'1010 | 
| UND           |  12         | 0b0000'1100 | 
| Erg.          |   8         | 0b0000'1000 | 
*/
