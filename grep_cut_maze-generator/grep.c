#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void elibereaza(char **text, int n) {
	for (int i = 0; i < n; i++) {
		free(text[i]);
	}
	free(text);
}

void greplinie(char *linie, char *cuvant) {
	//char *salveaza = (char*) linie;
	char *instr;
	instr = strstr(linie, cuvant); //verific daca in linie se afla cuvantul;
	if (instr != NULL) {		   //daca da, incep sa afisez linie caracter 
		while (instr != NULL) {	   //cu caracter pana la cuvantul cautat;
			while (linie < instr) {
				printf("%c", *linie); 
				linie++;
			}					   
			if (linie < instr + strlen(cuvant)) {
				printf("[0;31m%s[m", cuvant);
				linie = linie + strlen(cuvant);
			}  //cand ajung la cuvantul cautat il afisez 
			instr = strstr(linie, cuvant); //ma uit daca mai exista alt cuvant
			if (instr == NULL) {		   //cautat,iar daca nu afisez restul
				printf("%s", linie);	   //liniei;
			}
		}
	}
}

void grep(char **text, int n, char *cuvant) {
	for (int i = 0; i < n; i++) { //parcurg textul linie cu linie;
		greplinie(text[i], cuvant); //caut cuvantul in fiecare linie;
	}
}

char *alocalinie(char *linie) {
	char *alocat = (char*) malloc ((strlen(linie)+1) * sizeof(char));
	if(alocat == NULL) {
		return NULL;   //aloc si verific daca s-a facut alocarea;
	}
	strcpy(alocat, linie);  //copiez intr-un vector auxiliar linia;
	return alocat;			
}

char **citire(int n) {
	char linie[200]; //am un vector fix in care initialstochez fiecare linie;
	char **text = (char**) malloc (n * sizeof(char*)); //aloc fiecare pointer;
	if(text == NULL) { 
		return NULL; 	//verific daca s-a facut alocarea;
	}
	for(int i = 0; i < n; i++) {
		fgets(linie, 200, stdin);  //scanez linia;
		text[i] = alocalinie(linie); //copiez linie in text[i];
	}
	return text;
}

int main() {

	int n; //nr de linii;
	char cautat[31]; //cuantul cautat;
	char **text = NULL;     //aici stochez liniile;
	char strnr[100]; //scanez n-ul ca string si apoi il fac in cu atoi;

	fgets(cautat, 31, stdin); //scanez cuvantul cautat;
	fgets(strnr, 31, stdin);  //scanez n-ul;
	cautat[strlen(cautat) - 1] = 0; //adaug terminator de sir cuvantului cautat;
	n = atoi(strnr); //convertesc;
	text = citire(n); //citesc liniile;
	grep(text, n, cautat); //caut cuvantul si il afisez(apeland alte functii);
	elibereaza(text, n); //eliberez memoria;
	
	return 0;
}
