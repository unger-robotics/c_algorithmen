/* ju - 15.1.18 - logik.c
   Logik in C: UND (&) - ODER (|) - XOR (^) - NEG (!)
*/
#include <stdio.h>
int main(void){
	char *msg    = "\nLogik in C: UND (&) - ODER (|) - XOR (^) - NEG (!)\n";
	char *tblKopf    = "| **E1** | **E2** | **UND** | **ODER** | **XOR** |\n";
	char *tblStrich  = "|-------:|-------:|--------:|---------:|--------:|\n";
	char *tbl2Kopf   = "| **E1** | **NEG** | \n";
	char *tbl2Strich = "|-------:|--------:| \n";
	int E1 = 0, E2 = 0;
	int UND, ODER, XOR, NEG;

	printf("%s",msg);

	// UND (&) - ODER (|) - XOR (^)
	printf("\n%s",tblKopf);
	printf("%s",tblStrich);
	for( E1 = 0; E1 <= 1 ; E1++){
		for( E2 = 0; E2 <= 1 ; E2++){
			UND  = E1 & E2;
			ODER = E1 | E2;
			XOR  = E1 ^ E2;
			printf("| %6d | %6d | %7d | %8d | %7d | \n", E1, E2, UND, ODER, XOR);
		}
	}
	
	// NEG (!)
	printf("\n%s",tbl2Kopf);
	printf("%s",tbl2Strich);
	for( E1 = 0; E1 <= 1 ; E1++){
		NEG  = E1;
		printf("| %6d | %7d | \n", E1, !NEG);
	}
  return 0;
}
/* Ausgabe
Logik in C: UND (&) - ODER (|) - XOR (^) - NEG (!)

| **E1** | **E2** | **UND** | **ODER** | **XOR** |
|-------:|-------:|--------:|---------:|--------:|
|      0 |      0 |       0 |        0 |       0 | 
|      0 |      1 |       0 |        1 |       1 | 
|      1 |      0 |       0 |        1 |       1 | 
|      1 |      1 |       1 |        1 |       0 | 

| **E1** | **NEG** | 
|-------:|--------:| 
|      0 |       1 | 
|      1 |       0 |
*/

