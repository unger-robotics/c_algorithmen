/* // ju -- https://bw1.eu -- 26-Dez-18  -- eingabe-user-pruefen-v02.c */
/*
  User - Eingabepruefung
  - Wahr, wenn ckeck != 0 (richtiger Datentyp, nur bei Zahlen!)
  - Dezimalzahl von 0 bis 255 (0 auto. durch unsigned int)
	unsigned int - 16-bit - 0 … 65535
*/
#include <stdio.h>
int main(void){
	printf("Eingabe pruefen\n");
	char antwort;
	int clear_puffer, check;
	// Zahlen
	unsigned int dez_zahl1=0, dez_zahl2=0;

	do{
		// Eingabe Zahlen
		do{
			printf("Eingabe1 - Dezimalzahl von 0 bis 255: "); 
			check = scanf("%d",&dez_zahl1);
			if((check != 1) || (dez_zahl1 > 255))
				printf("	Fehler! Zahl\n");
		}while(((clear_puffer = getchar()) != EOF && clear_puffer != '\n') || (check != 1) || (dez_zahl1 > 255));		
	
		do{
			printf("Eingabe2 - Dezimalzahl von 0 bis 255: "); 
			check = scanf("%d",&dez_zahl2);
			if((check != 1) || (dez_zahl2 > 255))
				printf("	Fehler! Zahl\n");
		}while(((clear_puffer = getchar()) != EOF && clear_puffer != '\n') || (check != 1) || (dez_zahl2 > 255));	
		// Eingabe pruefen 
		printf("Eingabe pruefen - Zahlen: %d %d\n\n",dez_zahl1, dez_zahl2); 		

		//++++++++++++
		do{
			printf("\n\nNoch einmal? [j/n] "); 
			scanf("%c", &antwort);
		}while(((clear_puffer = getchar()) != EOF && clear_puffer != '\n'));			
	}while((antwort == 'j') || (antwort == 'J'));

	//int clear_puffer;
	//while( (clear_puffer = getchar()) != EOF && clear_puffer != '\n');
	//getchar(); //Speicherkontrolle
	return 0;
}




