/* ju - 15.1.18 - bitweiseVerschiebung.c
	 bitweise Verschiebung
	 x << y = Ganzzahl multiplikation mit 2
	 x >> y = Ganzzahl division mit 2
*/
#include <stdio.h>
int main(void){
	char *message = "\n**bitweise Verschiebung** \n\n"
									"x << y = Ganzzahl multiplikation mit 2 \n"
		   						"x >> y = Ganzzahl division mit 2 \n\n";
	int zahl = 0b00101001; // 41
	int a = zahl << 1;
	int b = zahl >> 1;
	int c = zahl << 2;
	int d = zahl << 3;

	printf("%s",message);
	printf("0b0010'1001 = %3d \n\n", zahl);

	printf("0b0010'1001 << 1 = 0b0000'0101'0010 = %3d \n", a);
	printf("0b0010'1001 >> 1 = 0b0000'0001'0100 = %3d \n", b);
	printf("0b0010'1001 << 2 = 0b0000'1010'0100 = %3d \n", c);
	printf("0b0010'1001 << 3 = 0b0001'0100'1000 = %3d \n", d);
  return 0;
}
/* Ausgabe
**bitweise Verschiebung** 

x << y = Ganzzahl multiplikation mit 2 
x >> y = Ganzzahl division mit 2 

0b0010'1001 =  41 

0b0010'1001 << 1 = 0b0000'0101'0010 =  82 
0b0010'1001 >> 1 = 0b0000'0001'0100 =  20 
0b0010'1001 << 2 = 0b0000'1010'0100 = 164 
0b0010'1001 << 3 = 0b0001'0100'1000 = 328 
*/



