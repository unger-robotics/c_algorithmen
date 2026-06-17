/* ju -- https://bw1.eu -- 26-Dez-18 -- logik-v02.c
   Logik in C: UND (&) - ODER (|) - XOR (^) - NEG (!)
*/
#include <stdio.h>
int main(void){
	char *msg    = "\nLogik in C\n\nUND (&) - ODER (|) - XOR (^) - NEG (!)\n";
	int E1 = 0, E2 = 0;
	int UND, ODER, XOR, NEG;

	printf("%s",msg);

	// UND (&) - ODER (|) - XOR (^)
  char *tblKopf    = "  E1  E2  UND  ODER  XOR  \n";
	printf("\n%s",tblKopf);
	for( E1 = 0; E1 <= 1 ; E1++){
		for( E2 = 0; E2 <= 1 ; E2++){
			UND  = E1 & E2;
			ODER = E1 | E2;
			XOR  = E1 ^ E2;
			printf("  %d  %d  %d  %d  %d  \n", E1, E2, UND, ODER, XOR);
		}
	}
	
	// NEG (!)
  char *tbl2Kopf   = "  E1  NEG  \n";
	printf("\n%s",tbl2Kopf);
	for( E1 = 0; E1 <= 1 ; E1++){
		NEG  = E1;
		printf("  %d  %d  \n", E1, !NEG);
	}
  return 0;
}
/* Ausgabe

*/

