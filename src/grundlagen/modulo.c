/* ju - 15.1.18 - modulo.c
   Modulo - Division mit Rest
*/
#include <stdio.h>
int main(void){
	char *message = "\nModulo - Division mit Rest\n\n";

	printf("%s",message);

	// Hinweis: im printf-Format steht %% für ein einzelnes Prozentzeichen.
	printf("7 %% 3 = %d\n", 7 % 3);   // 7 = 2*3 + 1  -> Rest 1
	printf("7 %% 7 = %d\n", 7 % 7);   // 7 = 1*7 + 0  -> Rest 0
  return 0;
}
/* Ausgabe
Modulo - Division mit Rest
7 % 3 = 1
7 % 7 = 0
*/


