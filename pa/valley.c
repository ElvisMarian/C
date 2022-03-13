#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int main() {
	int N, i;
	double rez = 0;
	double suma = 0;
	double referinta = INT_MAX;
	int index;
	double nr_of_heights = 0;;

	scanf("%d", &N);

	double *heights = (double*)malloc(sizeof(double) * N);
	// citirea
	for(i = 0 ; i < N; i++) {
		scanf("%lf", &heights[i]);
		if(heights[i] < referinta) {
			referinta = heights[i];
			index = i;
		}
	}
	// daca cel mai mic element e la sfarsit
	if(index == N - 1) {
		rez += heights[N - 2] - heights[index];
		heights[N - 2] = heights[index];
		printf("%ld", (long)rez);
		return 0;
	}
	// daca cel mai mic element e la inceput
	if(index == 0) {
		rez += heights[1] - heights[0];
		heights[1] = heights[0];
		printf("%ld", (long)rez);
		return 0;
	}
	referinta = heights[0];
	// pentru prefix
	for (i = 1; i <= index; i++) {
		if(referinta >= heights[i]) {
			rez += suma - (nr_of_heights * referinta);
			suma = 0;
			nr_of_heights = 0;
			referinta = heights[i];
		} else {
			suma += heights[i];
			nr_of_heights++;
		}
	}
	referinta = heights[N - 1];
	// pentru sufix
	for (i = N - 2; i >= index; i--) {
		if(referinta >= heights[i]) {
			rez += suma - (referinta * nr_of_heights);
			suma = 0;
			nr_of_heights = 0;
			referinta = heights[i];
		} else {
			suma += heights[i];
			nr_of_heights++;
		}
	}
	printf("%ld", (long)rez);
	free(heights);
}
