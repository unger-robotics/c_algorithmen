/* ju -- 5-12-2016 -- eingabe_user_pruefen.c */
/* eingabe_user_pruefen 

User - Eingabepruefung
- Wahr, Solange kein End of File = EOF = Strg D bzw Z und keine Enter
- Wahr, wenn ckeck != 0 (richtiger Datentyp, nur bei Zahlen!)
- Dezimalzahl von 0 bis 255 (0 auto. durch unsigned int)
- Buchstabe: ((zeichen1 >= 'A') && (zeichen1 <= 'Z')) || ((zeichen1 >= 'a') && (zeichen1 <= 'z'))
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

//const double PI   = 3.14159265;
//const double MWST = 19; // 7% oder 19%

int main(void){
	printf("eingabe_user_pruefen\n");
	char antwort;
	int clear_puffer, check, error = false;
	//ein Zeichen
	char zeichen1, zeichen2, zeichen3;
	//Zeichenketten
	const int max_feld = 50;
	int i=0;
	char zeichen , cFeld[max_feld];
	//Zahlen
	unsigned int dez_zahl1=0, dez_zahl2=0;
	
	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

	do{
		system("clear"); // system("cls");
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		
		//Eingabe ein Zeichen
		do{
			printf("Eingabe1 - Zeichen: "); 
			check = scanf("%c",&zeichen1);
			if( !(((zeichen1 >= 'A') && (zeichen1 <= 'Z')) || ((zeichen1 >= 'a') && (zeichen1 <= 'z'))) )
				{error = true; printf("	Fehler! kein Buchstabe\n"); }	
			else
				error = false; //Buchstabe		
		}while(((clear_puffer = getchar()) != EOF && clear_puffer != '\n') || error != false || (check != 1));	
		do{
			printf("Eingabe2 - Zeichen: "); 
			check = scanf("%c",&zeichen2);
			if( !(((zeichen2 >= 'A') && (zeichen2 <= 'Z')) || ((zeichen2 >= 'a') && (zeichen2 <= 'z'))) )
				{error = true; printf("	Fehler! kein Buchstabe\n"); }
			else
				error = false; //Buchstabe		
		}while(((clear_puffer = getchar()) != EOF && clear_puffer != '\n') || error != false || (check != 1));	
		do{
			printf("Eingabe3 - Zeichen: "); 
			check = scanf("%c",&zeichen3);
			if( !(((zeichen3 >= 'A') && (zeichen3 <= 'Z')) || ((zeichen3 >= 'a') && (zeichen3 <= 'z'))) )
				{error = true; printf("	Fehler! kein Buchstabe\n"); }
			else
				error = false; //Buchstabe		
		}while(((clear_puffer = getchar()) != EOF && clear_puffer != '\n') || error != false || (check != 1));	
		//Eingabe ueberpruefen Zeichen
		printf("Eingabe pruefen - Zeichen: %c %c %c\n\n",zeichen1, zeichen2, zeichen3);

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		//Eingabe Zeichenkette, Texte
		printf("Eingabe Text [max. 50 Zeichen!] Beenden mit [Strg D bzw. Strg Z]:\n	");
		while((zeichen = getchar()) != EOF){ //Beenden mit Strg D bzw. Strg Z = EOF
			if(i < max_feld) // 50 Zeichen
				cFeld[i++] = zeichen;
			else{
				printf("\n	Fehler! Maximale Feldlaenge ueberschritten.\n");
				return 1;
			}
		}
		cFeld[i] = 0;
		//Eingabe ueberpruefen Zeichenkette, Text
		printf("Eingabe pruefen - Text: %s\n\n",cFeld);
		
		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		//Eingabe Zahlen
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
		//Eingabe ueberpruefen Zahlen
		printf("Eingabe pruefen - Zahlen: %d %d\n\n",dez_zahl1, dez_zahl2); 		

		//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		do{
			printf("\n\nNoch einmal? [j/n] "); 
			scanf("%c", &antwort);
		}while(((clear_puffer = getchar()) != EOF && clear_puffer != '\n'));			
	}while((antwort == 'j') || (antwort == 'J'));

	//int clear_puffer;
	//while( (clear_puffer = getchar()) != EOF && clear_puffer != '\n');
	getchar(); //Speicherkontrolle
	return 0;
}




