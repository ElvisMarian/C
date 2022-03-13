#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

typedef struct pc {
	double power;
	double cost;
} c;

c **pc;
c **aux;
	// merge sort
void merge_sort(int i, int j) {
    if (j <= i) {
        return;
    }
    int mid = (i + j) / 2;

    merge_sort(i, mid);
    merge_sort(mid + 1, j);

    int left = i;
    int right = mid + 1;
    int k;

    for (k = i; k <= j; k++) {
        if (left == mid + 1) {
            (aux[k])->power = (pc[right])->power;
            (aux[k])->cost = (pc[right])->cost;
            right++;
        } else if (right == j + 1) {
            (aux[k])->power = (pc[left])->power;
            (aux[k])->cost = (pc[left])->cost;
            left++;
        } else if ((pc[left])->power < (pc[right])->power) {
            (aux[k])->power = (pc[left])->power;
            (aux[k])->cost = (pc[left])->cost;
            left++;
        } else {
            (aux[k])->power = (pc[right])->power;
            (aux[k])->cost = (pc[right])->cost;
            right++;
        }
    }

    for (k = i; k <= j; k++) {
        (pc[k])->power = (aux[k])->power;
        (pc[k])->cost = (aux[k])->cost;
    }
}

int main() {
	int N;
	double B;
	int i, rez;
	double suma = 0;

	scanf("%d%lf", &N, &B);
	double sume[N];

	pc = (c**)malloc(sizeof(c*) * N);
	aux = (c**)malloc(sizeof(c*) * N);
	// citirea
	for(i = 0 ; i < N; i++) {
		pc[i] = (c*) malloc(sizeof(c));
		aux[i] = (c*) malloc(sizeof(c));
		scanf("%lf%lf", &pc[i]->power, &pc[i]->cost);
	}
	merge_sort(0, N - 1);
	// crearea vectorului de sume partiale
	for (i = 0 ; i < N; i++) {
		suma += pc[i]->cost;
		sume[i] = suma;
	}
	// rezultatul initial e cel mai mic Pi
	rez = pc[0]->power;
	for (i = 1; i < N; i++) {
		// daca am aceeasi putere de procesare trec mai departe
		if (pc[i - 1]->power == pc[i]->power)
			continue;
	// daca am o putere de procesare diferita verific daca pot ajunge
	// la ea si incerc sa ajung direct
		if (B - (pc[i]->power - pc[i - 1]->power) * sume[i - 1] > 0) {
			B -= (pc[i]->power - pc[i - 1]->power) * sume[i - 1];
			rez += (int)(pc[i]->power - pc[i-1]->power);
		} else {
			while (1) {
				// daca nu cresc cat mai pot si vad unde pot ajunge
				B -= sume[i - 1];
				if (B < 0) {
					printf("%d", rez);
					return 0;
				}
				rez++;
			}
		}
	}
	// daca inca mai am bani si am ajuns la aceeasi putere de procesare
	// le cresc pe toate cat mai pot
	if (B >= 0)
		rez +=  (int) (B / sume[i - 1]);
	printf("%d", rez);
}
