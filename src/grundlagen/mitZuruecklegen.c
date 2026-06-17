/* ju - 15.1.18 - mitZuruecklegen.c
   Urnenmodell mit Zuruecklegen - Lotto 6 aus 49 
*/
#include <stdio.h>
#include <stdlib.h> // rand()
#include <time.h>   // time()
#define DIM 6       // Array-DIMENSION
int main(void){
	char *message      = "\nUrnenmodell mit Zuruecklegen - Lotto 6 aus 49\n";
	char *md           = "\nAusgabe - Markdown\n\n";
	char *tblMdKopf    = "| **Ziehung** | **Inhalt** |\n";
	char *tblMdStrich  = "|------------:|-----------:|\n";
	char *tex          = "\nAusgabe - LaTeX\n\n";
	char *tblTexKopf   = "\\textbf{Ziehung} & \\textbf{Inhalt} \\\\ \n";
	char *csv          = "\nAusgabe - Excel\n\n";	
	char *tblCsvKopf   = "Ziehung;Inhalt\n";
	int ziehung[DIM]={0};  // Array mit 6 Zahlen
	int temp=0;
	srand((unsigned)time( NULL)); 

	// Array mit Zufallszahlen belegen
	for(int i = 0; i < DIM; i++) {
		temp=(int)rand()%49 + 1; // Zufallszahl zwischen 1-49
		ziehung[i]=temp;
	}

	printf("%s",message);

	// Ausgabe - Markdown
	printf("%s",md);
	printf("%s",tblMdKopf);
	printf("%s",tblMdStrich);
	for( int i = 0; i < DIM; i++){
		printf("| %11d | %10d |\n",i+1, ziehung[i]);
	}

	// Ausgabe - Latex
	printf("%s",tex);
	printf("%s",tblTexKopf);
	for( int i = 0; i < DIM; i++){
		printf("%d & %2d \\\\ \n",i+1, ziehung[i]);
	}

	// Ausgabe - Excel
	printf("%s",csv);	
	printf("%s",tblCsvKopf);
	for( int i = 0; i < DIM; i++){
		printf("%d;%d\n",i+1, ziehung[i]);
	}
	return 0;
}
/* Ausgabe
Urnenmodell - mit Zuruecklegen - Lotto 6 aus 49

Ausgabe - Markdown

| **Ziehung** | **Inhalt** |
|------------:|-----------:|
|           1 |         36 |
|           2 |         44 |
|           3 |         41 |
|           4 |         25 |
|           5 |         21 |
|           6 |         45 |

Ausgabe - LaTeX

\textbf{Ziehung} & \textbf{Inhalt} \\ 
1 & 36 \\ 
2 & 44 \\ 
3 & 41 \\ 
4 & 25 \\ 
5 & 21 \\ 
6 & 45 \\ 

Ausgabe - Excel

Ziehung;Inhalt
1;36
2;44
3;41
4;25
5;21
6;45
 */


