#include "file.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int create_root(Directory **fs)
{
	*fs = (Directory *) malloc(sizeof(Directory));
	(*fs)->name = "/"; //creez root-ul
	(*fs)->director = NULL;
	(*fs)->file = NULL;
	(*fs)->parentDir = NULL;
	if (!fs)
		return -1;
}

void delete_root(Directory **fs)
{
	free(*fs); //sterg root-ul
}

void touch(Directory **curent, char *name, char *content)
{
	int i = 0;
	fl *fisier = malloc(sizeof(*fisier));
	File *f = (File *) malloc(sizeof(File));
	//aloc memorie
	f->name = (char *) malloc((strlen(name) + 1) * sizeof(char));
	f->data = (char *) malloc((strlen(content) + 1) * sizeof(char));
	//f este fisierul meu,fisier pointeaza catre lista de fisiere
	f->size = strlen(content);
	f->dir = *curent; //pun datele in f
	strcpy(f->name, name);
	strcpy(f->data, content);
	f->size = strlen(content);
	fisier->fis = f;
	if ((*curent)->file == NULL) {
		(*curent)->file = fisier;
		fisier->next = NULL; //daca lista e goala
	} else {
		fl *aux = (*curent)->file;
		fl *head = aux;
		fl *temp = (*curent)->file;

		while (aux && (i + 1)) {
			if (strcmp(aux->fis->name, f->name) <= 0) {
				if (aux->next == NULL) {

					aux->next = fisier;	//cand fisierul
					fisier->next = NULL;	//e ultimul;
					i = -2;
				} else {
					aux = aux->next;
				}
			} else {
				char *test = (*curent)->file->fis->name;

				if (strcmp(test, f->name) > 0) {
					fisier->next = temp;
					//cand fisierul devine primul;
					(*curent)->file = fisier;
					 // devine primul;
					i = -2;
				} else {
					head->next = fisier;
					fisier->next = aux;
					//cand fisierul e pus intre 2 fisiere
					i = -2;
				}
			}

			if (i) //head merge in spate si aux in fata
				head = head->next; //ca sa pot pune
			i++; //un fisier intre alte doua fisiere
		}
	}
}

void mkdir(Directory **curent, char *name)
{
	dl *direct = (dl *) malloc(sizeof(dl));
	Directory *d = (Directory *) malloc(sizeof(Directory));

	d->name = (char *) malloc((strlen(name) + 1) * sizeof(char));
	d->director = (dl *) malloc(sizeof(dl));//aloc memorie
	d->file = (fl *) malloc(sizeof(fl));
	d->parentDir = *curent;
	d->director = NULL; //pun datele sau setez pe NULL
	d->file = NULL;
	strcpy(d->name, name);
	direct->dir = d;
	if ((*curent)->director == NULL) {
		(*curent)->director = direct;
		direct->next = NULL; //daca lista e goala
	} else {
		dl *aux = (*curent)->director;
		dl *head = aux;
		int i = 0;

		while (aux && (i + 1)) {
			char *test = (*curent)->director->dir->name;

			if (strcmp(aux->dir->name, d->name) <= 0) {
				if (aux->next == NULL) {
					aux->next = direct;
					//cand directorul e ultimul;
					direct->next = NULL;
					i = -2;
				} else {
					aux = aux->next;
				}
			} else if (strcmp(test, d->name) > 0) {
				direct->next = aux;
				//cand directorul devine primul;
				(*curent)->director = direct;
				i = -2;
			} else {
				head->next = direct;
				direct->next = aux;
				//cand directorul e pus intre 2 fisiere
				i = -2;
			}

			if (i) //la fel ca la fisiere (sa pot)
				head = head->next;
			i++; //pune un director intre alte doua direcoare
		}
	}
}

void ls(Directory *curent)
{
	fl *fisier = curent->file;

	while (fisier) { //cat timp exista fisier
		printf("%s ", fisier->fis->name); //afisez
		fisier = fisier->next; //si parcurg lista
	}

	dl *direct = curent->director;

	while (direct) { //cat timp am director valid
		printf("%s ", direct->dir->name);
		direct = direct->next;//printez si merg mai departe
	}
}

void pwd(Directory *curent, Directory *root)
{
	if (curent == root) //daca direct curent e root
		printf("/");
	else {
		if (curent->parentDir != root)
			pwd(curent->parentDir, root);
		//merg recursiv si afisez
		printf("/%s", curent->name);
	}
}

void cd(Directory **curent, char *name)
{
	dl *jumper = (*curent)->director;
	//jumper parcurge lista si compara numele directorului--
	while (jumper) { //cautat cu numele fiecarui director
		if (strcmp(jumper->dir->name, name) == 0) {
			(*curent) = jumper->dir;
			return; // daca l-am gasit el devine curent
		}
		jumper = jumper->next; //daca nu merg mai departe
	}
	if (strcmp(name, "..") == 0) { //cazul in care vreau
		(*curent) = (*curent)->parentDir; //sa merg in parinte
		return; //direcorul curent va fi acum direct parinte
	}

}

void rm(Directory **curent, char *name)
{
	int nul = 0, iesire = 1; //iesire ma scoate din while
	char *text = "Cannot remove";
	File *f = (*curent)->file->fis;
	fl *fi = (*curent)->file;
	fl *aux = (*curent)->file;
	//auxiliare
	while (fi && iesire) {
		if (strcmp(f->name, name) == 0) {
			if (strcmp((*curent)->file->fis->name, name) == 0)
				nul = 1; //daca fisierul meu e primul sete
			//il setez pe "nul"
			free(f->name);
			free(f->data);//eliberez memoria
			free(f->dir);
			fi->fis = NULL;
			free(f);
			if (fi->next) {
				if (nul) //daca nul e 1 atunci schimb legaturile
					(*curent)->file = (*curent)->file->next;
				//curent va pointa catre al doilea element
				aux->next = fi->next;
				fi->next = NULL;
				free(fi); //eliberez memoria
				iesire = 0;
			} else {
				free(fi);
				aux->next = NULL;
				if (nul)
					(*curent)->file = NULL;
				iesire = 0;
			}
		} else {
			if (fi->next) {
				aux = fi; //merg mai departe
				fi = fi->next;
				f = fi->fis;
			} else {
				printf("%s '%s': No such file!\n", text, name);
				iesire = 0; //afisez eroare si ies din while
			}
		}
	}
}

void rmdir(Directory **curent, char *name)
{
	int nul = 0, iesire = 1;
	char *text1 = "Cannot remove";
	char *text2 = "No such directory!";
	Directory *d = (*curent)->director->dir;
	dl *di = (*curent)->director;
	dl *aux = (*curent)->director;
	//auxiliare
	while (d->name != NULL && iesire) {
		if (strcmp(d->name, name) == 0) {
			if (strcmp((*curent)->director->dir->name, name) == 0)
				nul = 1; //daca  directorul e primul in lista
			//il setez pe "nul"
			free(d->name);
			free(d->director);
			free(d->file);//eliberez
			free(d);
			if (di->next && nul)
				(*curent)->director = (*curent)->director->next;
			if (di->next) { //merg mai departe
				aux->next = di->next;
				di->next = NULL;
				free(di);
				iesire = 0; //ies
			} else {
				free(di);
				aux->next = NULL;
				if (nul) //lista mea acum e goala
					(*curent)->director = NULL;

				iesire = 0;
			}
		} else {
			if (di->next) {
				aux = di;
				di = di->next;
				d = di->dir;
			} else {
				printf("%s '%s': %s\n", text1, name, text2);
				iesire = 0; //afisez eroarea si ies din while
			}
		}
	}
}

void tree(Directory *curent, int ind)
{
	if (!curent) //daca curent nu e valid
		return;
	fl *fisier = curent->file;
	dl *aux = curent->director;

	for (int i = 0; i < ind ; i++)
		printf(" "); //afisez spatiu pt director
	printf("%s\n", curent->name); //afisez directorul
	while (fisier) {
		for (int i = 0; i < ind + 4; i++)
			printf(" "); //afisez fisierele
		printf("%s\n", fisier->fis->name);
		fisier = fisier->next; //merg mai departe
	}

	while (aux) {
		tree(aux->dir, ind + 4);
		aux = aux->next; //apelez recursiv
	}
}

void main(void)
{
	Directory *root = NULL; //root-ul
	Directory *curent = NULL; //direct curent
	dl *helper = NULL; //ma ajuta la pwd
	char command[100]; //aici stochez comanda
	char *name;
	char *content;
	char *token; //numele functiei pe care o voi executa
	char *text = "Cannot remove"; //text
	Directory *aux = curent;
	char *test = "Cannot move to";
	char *test2 = "No such directory!";
	int size, ind = 0; //ind ma ajuta la tree


	while (fgets(command, 100, stdin)) { //astept permanent
		token = strtok(command, "\n "); //comanda si intru
		if (strcmp(token, "create") == 0) { //in functia
			create_root(&root);		//corespunzatoare
			curent = root;
		} else if (strcmp(token, "delete") == 0) {
			delete_root(&root);
			return; //ies din program
		} else if (strcmp(token, "touch") == 0) {
			name = strtok(NULL, "\n ");
			content = strtok(NULL, "\n ");
			touch(&curent, name, content);
		} else if (strcmp(token, "mkdir") == 0) {
			name = strtok(NULL, "\n ");
			mkdir(&curent, name);
		} else if (strcmp(token, "ls") == 0) {
			ls(curent);
			printf("\n");
		} else if (strcmp(token, "pwd") == 0) {
			helper = root->director;
			pwd(curent, root);
			printf("\n");
		} else if (strcmp(token, "cd") == 0) {
			aux = curent;
			name = strtok(NULL, "\n ");
			cd(&curent, name);
			if (aux == curent)
				printf("%s '%s': %s\n", test, name, test2);
		} else if (strcmp(token, "rm") == 0) {
			name = strtok(NULL, "\n ");
			if (curent->file != NULL)
				rm(&curent, name);
			else
				printf("%s '%s': No such file!\n", text, name);
		} else if (strcmp(token, "rmdir") == 0) {
			name = strtok(NULL, "\n ");
			if (curent->director != NULL)
				rmdir(&curent, name);
			else
				printf("%s '%s': %s\n", text, name, test2);

		} else if (strcmp(token, "tree") == 0) {
			tree(curent, 0);
		}
	}
}
