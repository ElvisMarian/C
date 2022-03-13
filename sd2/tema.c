#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 3
#define MAX 50

typedef struct arbore {
	char **matrix;
	struct arbore *next;
	struct arbore *list;
} arbore;

int diagaonale(char **matrix) {
	if (matrix[1][1] != '-') {
		if (matrix[0][0] == matrix[1][1] && matrix[1][1] == matrix[2][2])
			return 1;
		else if (matrix[0][2] == matrix[1][1] && matrix[1][1] == matrix[2][0] )
			return 1;
	}
	return 0;
}

int verifyWin(char **matrix, int i, int j) {
	if (diagaonale(matrix))
		return 1;
	if (i == 0)
		// jos 2
		if (matrix[i][j] == matrix[i+1][j] && matrix[i][j] == matrix[i+2][j])
			return 1;
		// sus+jos
	if (i == 1)
		if (matrix[i][j] == matrix[i-1][j] && matrix[i][j] == matrix[i+1][j])
			return 1;
		// sus 2
	if (i == 2)
		if (matrix[i][j] == matrix[i-1][j] && matrix[i][j] == matrix[i-2][j])
			return 1;
		// dr 2
	if (j == 0)
			if (matrix[i][j] == matrix[i][j+1] && matrix[i][j] == matrix[i][j+2])
			return 1;
		// st + dr
	if (j == 1)
			if (matrix[i][j] == matrix[i][j-1] && matrix[i][j] == matrix[i][j+1])
			return 1;
		// st 2
	if (j == 2)
			if (matrix[i][j] == matrix[i][j-1] && matrix[i][j] == matrix[i][j-2])
			return 1;
	return 0;
}

	// alocam un nod de arbore care are matricea trimisa de noi
arbore *nod_arbore_nou(char **matrix) {
	int i, j;
	arbore *nou = malloc(sizeof(*nou));
	nou->matrix = (char **)malloc(sizeof(char *)*SIZE);
	for (i = 0; i < SIZE; i++)
		(nou->matrix)[i] = (char *)malloc(sizeof(char)*SIZE);
	nou->next = nou->list = NULL;
	// copiem matricea
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++)
			nou->matrix[i][j] = matrix[i][j];
	}
	return nou;
}

void addToList(arbore **nod, char **matrix) {
	arbore *aux = (*nod)->list;
	// verificam daca nodul curent exista
	if (!(*nod))
		return;
	// verificam daca lista exista sau nu
	if ((*nod)->list) {
		// pune nodul la finalul listei
		while (aux->next)
			aux = aux->next;
		aux->next = nod_arbore_nou(matrix);
	} else {
		(*nod)->list = nod_arbore_nou(matrix);
	}
}

	// eliberam memoria
void elibereaza(arbore *nod) {
	if (!nod)
		return;
	// reapelam functia pentru lista
	// din nodul curent
	elibereaza(nod->list);
	// reapelam pentru urmatorul element
	elibereaza(nod->next);
	// eliberam memoria alocata matricei
	for (int i = 0; i < SIZE; i++)
		free(nod->matrix[i]);
	free(nod->matrix);
	// eliberam memoria alocata nodului
	free(nod);
}
// printam createTree in fisier
void writeTree(arbore *root, int nr, FILE *fis_out) {
	// verificam daca nodul curent exist
	if (!root)
		return;
	while (root) {
		// printam matricea si numarul de tab-uri
		for (int i = 0; i < SIZE; i++) {
			for (int c = 0; c < nr; c++)
				fprintf(fis_out, "%s", "\t");
			for (int j = 0; j < SIZE; j++)
				if (j == SIZE - 1)
					fprintf(fis_out, "%c", root->matrix[i][j]);
				else
					fprintf(fis_out, "%c ", root->matrix[i][j]);
			fprintf(fis_out, "%s", "\n");
		}
		fprintf(fis_out, "%s", "\n");
		if (root->list) {
			nr++;
			// reapelam functia daca exista o lista in nodul curent
			writeTree(root->list, nr--, fis_out);
			}
		root = root->next;
	}
}
	// creem matricile de joc si le punem in arbore
void createTree(char *change, char **matrix, arbore **nod) {
	int i, j;
	char c;
	arbore *aux = NULL;
	// c reprezinta changea urmatoare
	if (change[0] == 'O')
		c = 'X';
	else
		c = 'O';
	// parcurgem matricea primita
	for (i = 0; i < SIZE; i++)
		for (j = 0; j < SIZE; j++) {
			if (matrix[i][j] == '-') {
				// completam cu changea corenodunzatoare
				matrix[i][j] = *change;
				// punem matricea in arbore
					addToList(&(*nod), matrix);
				// verificam daca s-a incheiat jocul
				if (verifyWin(matrix, i, j) == 0) {
					// daca nu s-a terminat jocul construim in continuare
					aux = (*nod)->list;
					while (aux->next)
						aux = aux->next;
					createTree(&c, matrix, &aux);
				}
					// punem din nou elementul '-'
					matrix[i][j] = '-';
			}
		}
}

int main(int argc, char **argv) {
	// verifica task
	if (strcmp(argv[1], "-c1") != 0)
		return 0;

	FILE *fis = fopen(argv[2], "r");
	FILE *fis_out = fopen(argv[argc-1], "w+");
	int i, j, k;
	char change[0], **matrix;
	char buff[50];
	// aloc memorie pentru matrice
	matrix =  (char **)malloc(sizeof(char *)*SIZE);
	for (i = 0; i < SIZE; i++)
		matrix[i] = (char *)malloc(sizeof(char)*SIZE);

	fgets(buff, MAX, fis);
	change[0] = buff[0];
	i = 0;
	// citesc matricea
	while (fgets(buff, MAX, fis) != NULL) {
		k = 0;
		for (j = 0; j < SIZE; j++) {
			matrix[i][j] = buff[k];
			k+=2;
		}
		i++;
	}
	arbore *root = nod_arbore_nou(matrix);
	// creez arborele
	createTree(change, matrix, &root);
	// scriu in fisier arborle
	writeTree(root, 0, fis_out);
	// eliberez memoria arborelui
	elibereaza(root);
	// eliberez memoria matricei
	for (i = 0; i < SIZE; i++)
		free(matrix[i]);
	free(matrix);
	// inchid fisierele
	fclose(fis_out);
	fclose(fis);
}
