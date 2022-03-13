#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct integ{
	int x;
	int y;	
}Integ;

#define SIZE 10
int out = 1;

Integ stack[SIZE * SIZE];     
int top = -1;    

int isempty() {

   if(top == -1)
      return 1;
    return 0;
}
   
int isfull() {

   	if(top == SIZE * SIZE)
      return 1;
    return 0;
}

int peekX() {
   return stack[top].x;
}

int peekY() {
   return stack[top].y;
}

void pop() {	
   if(!isempty()) {
      top = top - 1;   
   } else {
      printf("Stack is empty.\n");
   }
}

int push(Integ data) {

   if(!isfull()) {
      top = top + 1;   
      stack[top].x = data.x;
      stack[top].y = data.y;
   } else
      printf("Stack is full.\n");
}

int validMove(int number, int matrix[SIZE][SIZE], int x, int y) {
	switch (number) {
		case 0: 	//up
			if(matrix[x-1][y] == 1  &&
				matrix[x-1][y-1] == 1 &&
				matrix[x-1][y+1] == 1)
				if(x != 1)
					if(matrix[x-2][y] == 1)
						return 1;
			return 0;
		case 1 : 	//down
			if(matrix[x+1][y] == 1 &&
				matrix[x+1][y-1] ==1 &&
				matrix[x+1][y+1] == 1)
				if(x != SIZE - 2)
					if(matrix[x+2][y] == 1)
						return 1;
			return 0;
		case 2: 	//left
			if(matrix[x][y-1] == 1 &&
				matrix[x+1][y-1] == 1 &&
				matrix[x-1][y-1] == 1)
				if(y != 1) 
					if(matrix[x][y-2] ==1)
						return 1;
					return 0;
		case 3:		//right
			if(matrix[x][y+1] == 1 &&
				matrix[x+1][y+1] == 1 &&
				matrix[x-1][y+1] == 1)
				if(y != SIZE - 2) 
					if(matrix[x][y+2] == 1)
						return 1;
					return 0;
		default:
			printf("Error\n");
			break;
	}
	return 0;
}

int maze(int m[SIZE][SIZE], int x, int y) {
	int nextCell;
	int xx, yy;
	nextCell = rand() % 4;
	int checks = 20;

	while(!validMove(nextCell, m, x, y)) {
		nextCell = rand() % 4;
		checks--;
		if(checks == 0) {
			if(out == 1) {
				out = 0;
				//when you finish the maze
				m[x][y] = 5;
			}
			if(!isempty()) {
				xx = peekX();
				yy = peekY();
				pop();
				return maze(m, xx, yy);
			}
			return 0;
		}
	}
	Integ stacky;
	stacky.x = x;
	stacky.y = y;
	push(stacky);
	switch (nextCell) {
		case 0: m[x-1][y] = 0; return maze(m, x-1, y); break;
		case 1: m[x+1][y] = 0; return maze(m, x+1, y); break;
		case 2: m[x][y-1] = 0; return maze(m, x, y-1); break;
		case 3: m[x][y+1] = 0; return maze(m, x, y+1); break;
		default: printf("Eroare\n"); break;
	}
		return 0;
 }
int main(int argc, char const *argv[])
{
	int m[SIZE][SIZE];
	srand(time(0));
	
	int x =  1 + (rand() % (SIZE - 2));
	int y = 1 + (rand() % (SIZE - 2));

	//3 is startpoint
	printf("X:%d\n", x);
	printf("Y:%d\n", y);

	for(int i = 0; i < SIZE; i++) {
		for(int j = 0; j < SIZE; j++)
			m[i][j] = 1;
	}

	m[x][y] = 3;

	maze(m, x, y);

	for(int i = 0; i < SIZE; i++) {
		printf("\n");
	for(int j = 0; j < SIZE; j++)
		printf("%d ",m[i][j]);
	}
	return 0;
}