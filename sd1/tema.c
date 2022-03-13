#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

typedef struct Node {
	//caracterul
	char character;
	//nr liniei pe care se afla nodul
	int nr_line;
	//pointer next
	struct Node *next;
	//pointer prev
	struct Node *prev;
}
node;
	//creez un nod pentru lista
node *create(char caracter)
{
	node *nod = (node *)malloc(sizeof(node));

	nod->next = NULL;
	nod->prev = NULL;
	nod->character = caracter;
	return nod;
}
	//inserez o linie in lista
void insert_line(node **list, char *command, node **cursor)
{
	node *aux = *list;
	node *temp;
	node *linie;
	//merg pana la capatul listei daca nu e vida
	if ((*list)->next != NULL)
		while (aux->next)
			aux = aux->next;
	//marchez numarul liniei curente
	linie = aux;
	//pentru fiecare caracter creez nod si pun in lista
	for (int i = 0; i < strlen(command); i++) {
		temp = create(*(command + i));
		aux->next = temp;
		temp->prev = aux;
		temp->nr_line = linie->nr_line + 1;
		aux = aux->next;
		*cursor = aux;
	}
}
	//fac scrierea in fisier
void print(node *list, FILE *out)
{
	node *temp = list->next;

	while (temp) {
		fprintf(out, "%c", temp->character);
		temp = temp->next;
	}
}
//duc cursorul la linia linie
void gotoline(node **cursor, node *l, int line)
{
	node *temp = l;

	while (temp->nr_line != line && temp)
		temp = temp->next;
	*cursor = temp->next;
}
//sterg o linie
void del_line(node **list, node **cursor, int line)
{
	node *aux = (*list)->next;
	node *temp;
	node *nod;

	while (aux->nr_line != line && aux)
		aux = aux->next;
	temp = aux->prev;
	temp->next = NULL;
	aux->prev = NULL;
	while (aux->nr_line == line && aux->next) {
		nod = aux;
		aux = aux->next;
		nod->prev = NULL;
		nod->next = NULL;
		aux->prev = NULL;
		free(nod);
	}
	if (aux->next == NULL) {
		temp->next = NULL;
		free(aux);
	} else {
		temp->next = aux;
		aux->prev = temp;
}
	*cursor = temp->next; // mut cursorul la inceputul liniei urmatoare
	while (temp) {
		temp->nr_line--; // actualizez nr liniilor
		temp = temp->next;
	}
}
	//sterg caracterul de dinaintea cursorului
void backspace(node **lista, node **cursor)
{
	node *temp = *cursor;
	node *aux;
	*cursor = (*cursor)->prev;
	temp->prev = NULL;
	if (temp->next == NULL) {
		(*cursor)->next = NULL;
		free(temp);
	} else {
		aux = temp->next;
		(*cursor)->next = aux;
		aux->prev = *cursor;
		temp->next = NULL;
		free(temp);
	}
}
	//duc cursorul la caracterul character de pe linia linie
void gc(node **cursor, node *list, int character, int line)
{
	*cursor = list;
	while ((*cursor)->nr_line != line && *cursor)
		*cursor = (*cursor)->next;
	for (int i = 1; i < character; i++)
		*cursor = (*cursor)->next;
}
//sterg un numar de caracter
void d(node **cursor, int nr_of_characters)
{
	node *aux = *cursor;
	node *temp = aux;
	node *nod1;

	for (int i = 0; i <= nr_of_characters; i++) {
		nod1 = aux;
		aux = aux->next;
		if (nod1 != *cursor) {
			temp->next = aux;
			nod1->prev = NULL;
			nod1->next = NULL;
			aux->prev = temp;
			free(nod1);
		}
	}
}
	//operatia undo
void undo(stack *stack_command, stack *stack_line, node **lista, node *cursor)
{
	if (stack_command->data[0] == ':' && stack_command->data[1] == ':')
		del_line(lista, &cursor, cursor->nr_line);
}
	//operatia redo
void redo(stack *stack_command, stack *stack_line, node *lista, node *cursor)
{
	if (stack_command->data[0] == 'u')
		insert_line(&lista, stack_line->data, &cursor);
}

void list_fee(node **lista)
{
	node *aux;

	while (*lista) {
		aux = *lista;
		*lista = (*lista)->next;
		free(aux);
	}
}

int main(void)
{
	//creez lista
	node *lista = create('/');
	//creez stivele pentru comenzi si linii
	stack *stack_command = NULL;
	stack *stack_line = NULL;
	//aici stochez comenzile
	char command[100];
	char *quit = "q\n";
	//daca insert_command e 1 atunci primesc comanda,altfel primesc text
	int insert_command = 0;
	FILE *file_in = fopen("editor.in", "r");
	FILE *file_out = fopen("editor.out", "w");

	lista->nr_line = 0;
	node *cursor;

	while (fgets(command, 100, file_in)) {
		//verific daca primesc q
		if (strcmp(command, quit) == 0) {
			break;
		//daca primesc ::i schimb indicatorul de comenzi
		} else if (command[0] == ':' && command[1] == ':') {
			insert_command = !insert_command;
		//daca e 0 atunci inserez linie si pun in stiva
		} else if (insert_command == 0) {
			stack_line = push(stack_line, command);
			insert_line(&lista, command, &cursor);
		//pentru comanda go to line
		} else if (command[0] == 'g' && command[1] == 'l'
			&& command[2] == ' ') {
			gotoline(&cursor, lista, atoi(&command[3]));
		//pentru comanda delete line
		} else if (command[0] == 'd' && command[1] == 'l') {
		/*delete line*/
			if (atoi(&command[3]))
				del_line(&lista, &cursor, atoi(&command[3]));
			else
				del_line(&lista, &cursor, cursor->nr_line);
		//pentru backspace
		} else if (command[0] == 'b') {
			backspace(&lista, &cursor);
		//pentru gc char [line]
		} else if (command[0] == 'g' && command[1] == 'c') {
			if (atoi(&command[5]))
				gc(&cursor, lista,
					atoi(&command[3]), atoi(&command[5]));
			else
				gc(&cursor, lista,
					atoi(&command[3]), cursor->nr_line);
		//daca primesc delete
		} else if (command[0] == 'd') {
			if (command[1] == '\n')
				backspace(&lista, &(cursor->next));
			else
				d(&cursor, atoi(&command[2]));
		//daca primesc save setez cursorul
		//la inceputul fisierului si scriu
		} else if (command[0] == 's') {
			rewind(file_out);
			print(lista, file_out);
		}
		//pentru undo
		else if (command[0] == 'u')
			undo(stack_command, stack_line, &lista, cursor);
		//pentru redo
		else if (command[0] == 'r')
			redo(stack_command, stack_line, lista, cursor);
		//daca trebuie sa inserez comanda o pun in stiva
		if (insert_command)
			stack_command = push(stack_command, command);
	}
	//eliberez memoria din stive si din lista
	stack_free(&stack_line);
	stack_free(&stack_command);
	list_fee(&lista);
	fclose(file_in);
	fclose(file_out);
}
