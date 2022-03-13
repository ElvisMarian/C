#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void citire(int **fields_vector, int *n, char **del, char **out_del, int *m ){
	char fields[200];   //vectorul in care citesc indicii
	char n_string[10]; //vectorul in care pun dimensiunea sirului de indici
	char *tok = NULL;  //token-ul in care retin ceea ce returneaza strtok
	*del = (char *)malloc(10 * sizeof(char)); 	//aloc memorie pt delimitatorii
	*out_del = (char *)malloc(10 * sizeof(char));  //de intrare si de iesire
	fgets(*del, 10, stdin); //citesc delimitatorii
	if (*(fgets(n_string, 10, stdin)) == '\n') { //daca am citit "\n" mai citesc 
		fgets(n_string, 10, stdin);				 //inca odata 
	} else {
		(*del)[strlen(*del) - 1] = 0; //daca nu ii adaug terminator de sir
	}
	*n = atoi(n_string);	  //convertesc dimensiunea sirului de indici la int
	fgets(fields, 200, stdin); //citesc sirul de indici
	fields[strlen(fields) - 1] = 0; //adaug terminator de sir
	*fields_vector = (int *)malloc(*n * sizeof(int)); //aloc dinamic vectorul 
	if ((*fields_vector) == NULL) {    //in care voi memorasirul de indici 
		return;						   //si verific daca s-a facut alocarea
	} 
	tok = strtok(fields, ","); //memorez in tok primul string pana la ","
	(*fields_vector)[0] = atoi(tok); //apoi adaug elementul in vectorul meu
	for (int i = 1; i < *n; i++) {			
		tok = strtok(NULL, ",");   //fac acelasi lucru cu restul
		(*fields_vector)[i] = atoi(tok);
	}
 	fgets(*out_del, 10, stdin); 			//citesc delimitatorul de iesire
 	(*out_del)[strlen(*out_del) - 1] = 0;   //ii pun terminator de sir
	fgets(n_string, 10, stdin);     		//citesc nr de linii al textului 
	*m = atoi(n_string);					//n_string il convertesc la int
}

void cut(int **fields_vector, int *n, char **del, char **out_del, int *m) {
	int scris = 0;  //verific daca s-a mai scris un cuvant inainte
	int counter = 1; //variabila care numara 
	int j = 0;
	char *tok = NULL; //vectorul in care pun tokenii
	char linie[200];  //vectorul in care citesc linia
	for (int i = 0; i < *m; i++) { 
		fgets(linie, 200, stdin); //citesc fiecare linie
		if (linie[strlen(linie) - 1] == '\n') { //daca linia contine "\n" 
			linie[strlen(linie) - 1] = 0;		//il inlocuiesc cu "\0"
		}
		tok = strtok(linie, *del); //memorez primul string pana la delimitator 
		while (tok != NULL) {  //verific daca sirul exista
			while (j < *n && (*fields_vector)[j] != counter) { //parcurg de la 
				j++;  //j(0) pana la n si verific daca valoarea vectorului de  
			}		  // indice j este diferita de counter
			if (j != *n) {    //daca j este diferit de n si a fost scris un
				if (scris == 1) {	//string inainte pun delimitatorul de iesire
					printf("%s", *out_del);
				} else {
					scris = 1; //altfel afisez doar acel string si setez scris 
				}				//pe 1 astfel incat data viitoare sa se puna 
				printf("%s", tok); //delimitatorul de iesire; stringul
			}
			j = 0; //resetez variabila pt urmatorul ciclu
			counter++; //cresc numaratoarea pentru urmatorul ciclu
			tok = strtok(NULL, *del); //retin urmatorul cuvant in acel token
		}
		scris = 0; //resetez scris pentru urmatoarea linie
		printf("\n"); //pun newline pentru afisarea liniei urmatoare
		counter = 1; //resetez numaratoarea
	}
}
int main() {

	int n = 0;  		//dimensiunea sirului de indici
	int m = 0;			// numarul de linii
	char *out_del = NULL; //aici voi retine delimitatorul de iesire
	char *del  = NULL; 	  // aici retin delimitatorii principali
	int *fields_vector = NULL;	//aici retin sirul de indici
	citire(&fields_vector, &n, &del, &out_del, &m);
	cut(&fields_vector, &n, &del, &out_del, &m);
	free(fields_vector); //eliberez memoria de pe heap
	free(del);
	free(out_del);
}