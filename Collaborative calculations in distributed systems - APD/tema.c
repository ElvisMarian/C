#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

#define P0 0
#define P1 1
#define P2 2

int min(int a, int b) {
	return (a > b) ? b : a;
}

int main(int argc, char *argv[]) {
	int rank;
	int nProcesses;
	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
	MPI_Status status;


	int index = 0;
	int start, end;
	int P = nProcesses - 3;
	int N = atoi(argv[1]);

	int *v = (int *)malloc(N * sizeof(int));
	int **topology =  malloc(3 * sizeof(int*));

	for(int i = 0; i < N; i++) {
		v[i] = i;
	}

	if(rank == P0) {

		FILE* f = fopen("cluster0.txt", "r");
        if(f == NULL) {
            printf("Eroare la deschiderea fisierului cluster%d.txt", rank);
            MPI_Finalize();
            return 0;
        }

		int len1, len2;
		int NoChilds;
		int parent = P0;

		fscanf(f, "%d", &NoChilds);
		topology[rank] = (int*) malloc (NoChilds * sizeof(int));

		for(int i = 0 ; i < NoChilds; i++) {
			fscanf(f, "%d", &topology[rank][i]);
			MPI_Send(&parent, 1, MPI_INT, topology[rank][i], 1, MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P0, topology[rank][i]);
		}
			//0 trimite datele din topologia lui catre 2
		MPI_Send(&NoChilds, 1, MPI_INT, 2, 1, MPI_COMM_WORLD);
		printf("M(%d,%d)\n", P0, 2);
		MPI_Send(topology[rank], NoChilds, MPI_INT, 2, 1, MPI_COMM_WORLD);
		printf("M(%d,%d)\n", P0, 2);

			//0 primeste datele de la 2
		MPI_Recv(&len1, 1, MPI_INT, 2, 1, MPI_COMM_WORLD, &status);
		topology[P1] = (int*) malloc (len1 * sizeof(int));
		MPI_Recv(topology[P1], len1, MPI_INT, 2, 1, MPI_COMM_WORLD, &status);

		MPI_Recv(&len2, 1, MPI_INT, 2, 2, MPI_COMM_WORLD, &status);
		topology[P2] = (int*) malloc (len2 * sizeof(int));
		MPI_Recv(topology[P2], len2, MPI_INT, 2, 2, MPI_COMM_WORLD, &status);

			//afisez topologia
		printf("%d -> %d:", P0, P0);
		for(int i = 0; i < NoChilds-1; i++) {
			printf("%d,", topology[P0][i]);
		}
		printf("%d %d:", topology[P0][NoChilds-1], P1);
		for(int i = 0; i < len1-1; i++) {
			printf("%d,", topology[P1][i]);
		}
		printf("%d %d:", topology[P1][len1-1], P2);
		for(int i = 0; i < len2-1; i++) {
			printf("%d,", topology[P2][i]);
		}
		printf("%d\n", topology[P2][len2-1]);

			//0 trimite topologia  copiilor
		for(int i = 0; i < NoChilds; i++) {
			MPI_Send(&len2, 1, MPI_INT, topology[P0][i], 2, MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P0, topology[P0][i]);

			MPI_Send(&len1, 1, MPI_INT, topology[P0][i], 1, MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P0, topology[P0][i]);

			MPI_Send(&NoChilds, 1, MPI_INT, topology[P0][i], 0, MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P0, topology[P0][i]);

			MPI_Send(topology[P2], len2, MPI_INT, topology[P0][i], 2, MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P0, topology[P0][i]);

			MPI_Send(topology[P1], len1, MPI_INT, topology[P0][i], 1, MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P0, topology[P0][i]);

			MPI_Send(topology[P0], NoChilds, MPI_INT, topology[P0][i], 0, MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P0, topology[P0][i]);
		}
			//impart intervalele si trimit workerilor lui 0
		for(index = 0 ; index < NoChilds; index++) {
			start = index * (double)N / P;
			end = min((index + 1) * (double)N / P, N);

			MPI_Send(&N, 1, MPI_INT, topology[P0][index], 0,MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P0, topology[P0][index]);

			MPI_Send(v, N, MPI_INT, topology[P0][index], 0, MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P0, topology[P0][index]);

			MPI_Send(&start, 1, MPI_INT, topology[P0][index], 0, MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P0, topology[P0][index]);

			MPI_Send(&end, 1, MPI_INT, topology[P0][index], 0, MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P0, topology[P0][index]);
		}

		MPI_Send(&N, 1, MPI_INT, P2, 2, MPI_COMM_WORLD);
		printf("M(%d,%d)\n", P0, P2);

			//trimit lui 2 datele
		for(index = NoChilds; index < nProcesses - 3; index++) {
			start = index * (double)N / P;
			end = min((index + 1) * (double)N / P, N);		

			MPI_Send(v, N, MPI_INT, P2, 2, MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P0, P2);

			MPI_Send(&start, 1, MPI_INT, P2, 2, MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P0, P2);

			MPI_Send(&end, 1, MPI_INT, P2, 2, MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P0, P2);
		}

		int *aux = (int *)calloc(N, sizeof(int));

			//primesc vectorii rezultati de la workerii lui 0
		for(index = 0 ; index < NoChilds; index++) {
			MPI_Recv(aux, N, MPI_INT, topology[P0][index], 0, MPI_COMM_WORLD, &status);
			MPI_Recv(&start, 1, MPI_INT, topology[P0][index], 0, MPI_COMM_WORLD, &status);
			MPI_Recv(&end, 1, MPI_INT, topology[P0][index], 0, MPI_COMM_WORLD, &status);

			for(int i = start; i < end; i++) {
				v[i] = aux[i];
			}
		}
			//primesc de la restul topologiei si asamblez rezultatele
		for(index =  NoChilds ; index < nProcesses-3; index++) {
			MPI_Recv(aux, N, MPI_INT, P2, 2, MPI_COMM_WORLD, &status);
			MPI_Recv(&start, 1, MPI_INT, P2, 2, MPI_COMM_WORLD, &status);
			MPI_Recv(&end, 1, MPI_INT, P2, 2, MPI_COMM_WORLD, &status);

			for(int i = start; i < end; i++) {
				v[i] = aux[i];
			}
		}

		printf("Rezultat: ");
		for(int i = 0 ;i < N-1; i++) {
			printf("%d ",v[i]);
		}
		printf("%d",v[N-1]);

		free(aux);
		for(int i = 0 ; i < 3; i++) {
			free(topology[i]);
		}

	} else if (rank == P1) {

		FILE* f = fopen("cluster1.txt", "r");
        if(f == NULL){
            printf("Eroare la deschiderea fisierului cluster%d.txt", rank);
            MPI_Finalize();
            return 0;
        }

		int index;
		int start, end, N;
		int len0, len2;
		int NoChilds;
		int parent = P1;
		fscanf(f, "%d", &NoChilds);

		topology[rank] = (int*) malloc (NoChilds * sizeof(int));

		for(int i = 0 ; i < NoChilds; i++) {
			fscanf(f, "%d", &topology[rank][i]);
			MPI_Send(&parent, 1, MPI_INT, topology[rank][i], 1, MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P1, topology[rank][i]);
		}

			//trimit topologia lui 1 lui 2
		MPI_Send(&NoChilds, 1, MPI_INT, 2, 1, MPI_COMM_WORLD);
		printf("M(%d,%d)\n", P1, P2);

		MPI_Send(topology[rank], NoChilds, MPI_INT, 2, 1, MPI_COMM_WORLD);
		printf("M(%d,%d)\n", P1, P2);

			//1 primeste topologia de la 2
		MPI_Recv(&len0, 1, MPI_INT, 2, 0, MPI_COMM_WORLD, &status);
		topology[P0] = (int*) malloc (len0 * sizeof(int));
		MPI_Recv(topology[P0], len0, MPI_INT, 2, 0, MPI_COMM_WORLD, &status);

		MPI_Recv(&len2, 1, MPI_INT, 2, 2, MPI_COMM_WORLD, &status);
		topology[P2] = (int*) malloc (len2 * sizeof(int));
		MPI_Recv(topology[P2], len2, MPI_INT, 2, 2, MPI_COMM_WORLD, &status);

			//afisez topologia
		printf("%d -> %d:", P1, P0);
		for(int i = 0; i < len0 - 1; i++) {
			printf("%d,", topology[P0][i]);
		}
		printf("%d %d:", topology[P0][len0 - 1], P1);
		for(int i = 0; i < NoChilds - 1; i++) {
			printf("%d,", topology[P1][i]);
		}
		printf("%d %d:", topology[P1][NoChilds - 1], P2);
		for(int i = 0; i < len2 - 1; i++) {
			printf("%d,", topology[P2][i]);
		}
		printf("%d\n", topology[P2][len2 - 1]);

		//trimit topologia workerilor lui 1
		for(int i = 0; i < NoChilds; i++) {
			MPI_Send(&len2, 1, MPI_INT, topology[P1][i], 2, MPI_COMM_WORLD);
			printf("M(%d,%d)\n",P1, topology[P1][i]);

			MPI_Send(&NoChilds, 1, MPI_INT, topology[P1][i], 1, MPI_COMM_WORLD);
			printf("M(%d,%d)\n",P1, topology[P1][i]);

			MPI_Send(&len0, 1, MPI_INT, topology[P1][i], 0, MPI_COMM_WORLD);
			printf("M(%d,%d)\n",P1, topology[P1][i]);

			MPI_Send(topology[P2], len2, MPI_INT, topology[P1][i], 2, MPI_COMM_WORLD);
			printf("M(%d,%d)\n",P1, topology[P1][i]);

			MPI_Send(topology[P1], NoChilds, MPI_INT, topology[P1][i], 1, MPI_COMM_WORLD);
			printf("M(%d,%d)\n",P1, topology[P1][i]);

			MPI_Send(topology[P0], len0, MPI_INT, topology[P1][i], 0, MPI_COMM_WORLD);
			printf("M(%d,%d)\n",P1, topology[P1][i]);
		}

		MPI_Recv(&N, 1, MPI_INT, P2, 1, MPI_COMM_WORLD, &status);
		int *aux = (int *)calloc(N, sizeof(int));

			//primesc informatiile de la 2 si le trimit workerilor lui 1
		for(index = 0 ; index < NoChilds; index++) {
			MPI_Recv(aux, N, MPI_INT, P2, 1, MPI_COMM_WORLD, &status);
			MPI_Recv(&start, 1, MPI_INT, P2, 1, MPI_COMM_WORLD, &status);
			MPI_Recv(&end, 1, MPI_INT, P2, 1, MPI_COMM_WORLD, &status);

			MPI_Send(&N, 1, MPI_INT, topology[P1][index], 1,MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P1, topology[P1][index]);

			MPI_Send(aux, N, MPI_INT, topology[P1][index], 1, MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P1, topology[P1][index]);

			MPI_Send(&start, 1, MPI_INT, topology[P1][index], 1, MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P1, topology[P1][index]);

			MPI_Send(&end, 1, MPI_INT, topology[P1][index], 1, MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P1, topology[P1][index]);
		}

			//primesc informatiile de la workerii lui 1 si le trimit lui 2
		for(index = 0 ; index < NoChilds; index++) {
			MPI_Recv(aux, N, MPI_INT, topology[P1][index], 1, MPI_COMM_WORLD, &status);
			MPI_Recv(&start, 1, MPI_INT, topology[P1][index], 1, MPI_COMM_WORLD, &status);
			MPI_Recv(&end, 1, MPI_INT, topology[P1][index], 1, MPI_COMM_WORLD, &status);

			MPI_Send(aux, N, MPI_INT, P2, 1, MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P1, P2);

			MPI_Send(&start, 1, MPI_INT, P2, 1, MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P1, P2);

			MPI_Send(&end, 1, MPI_INT, P2, 1, MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P1, P2);
		}

		free(aux);
		for(int i = 0 ; i < 3; i++) {
			free(topology[i]);
		}

	} else if(rank == P2) {

		FILE* f = fopen("cluster2.txt", "r");
        if(f == NULL){
            printf("Eroare la deschiderea fisierului cluster%d.txt", rank);
            MPI_Finalize();
            return 0;
        }

		int len0, len1;
		int NoChilds;
		int parent = P2;
		int index, N;
		int start, end;

		fscanf(f, "%d", &NoChilds);
		topology[rank] = (int*) malloc (NoChilds * sizeof(int));

		//le transmit workerilor cine este clusterul lor
		for(int i = 0 ; i < NoChilds; i++) {
			fscanf(f, "%d", &topology[rank][i]);
			MPI_Send(&parent, 1, MPI_INT, topology[rank][i], 1, MPI_COMM_WORLD);
			printf("M(%d,%d)\n",P2, topology[rank][i]);
		}

			//primesc de la 0 topologia
		MPI_Recv(&len0, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		topology[P0] = (int*) malloc (len0 * sizeof(int));
		MPI_Recv(topology[P0], len0, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);

			//primesc de la 1 topologia
		MPI_Recv(&len1, 1, MPI_INT, 1, 1, MPI_COMM_WORLD, &status);
		topology[P1] = (int*) malloc (len1 * sizeof(int));
		MPI_Recv(topology[P1], len1, MPI_INT, 1, 1, MPI_COMM_WORLD, &status);

		//2 a aflat topologia si o va afisa
		printf("%d -> %d:", P2, P0);
		for(int i = 0; i < len0-1; i++) {
			printf("%d,", topology[P0][i]);
		}
		printf("%d %d:", topology[P0][len0-1], P1);
		for(int i = 0; i < len1-1; i++) {
			printf("%d,", topology[P1][i]);
		}
		printf("%d %d:", topology[P1][len1-1], P2);
		for(int i = 0; i < NoChilds-1; i++) {
			printf("%d,", topology[P2][i]);
		}
		printf("%d\n", topology[P2][NoChilds-1]);

			//trimit lui 0 topologia
		MPI_Send(&len1, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
		printf("M(%d,%d)\n",P2, P0);

		MPI_Send(topology[P1], len1, MPI_INT, 0, 1, MPI_COMM_WORLD);
		printf("M(%d,%d)\n",P2, P0);

		MPI_Send(&NoChilds, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
		printf("M(%d,%d)\n",P2, P0);

		MPI_Send(topology[P2], NoChilds, MPI_INT, 0, 2, MPI_COMM_WORLD);
		printf("M(%d,%d)\n",P2, P0);

			//trimit lui 1 topologia
		MPI_Send(&len0, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		printf("M(%d,%d)\n",P2, P1);

		MPI_Send(topology[P0], len0, MPI_INT, 1, 0, MPI_COMM_WORLD);
		printf("M(%d,%d)\n",P2, P1);

		MPI_Send(&NoChilds, 1, MPI_INT, 1, 2, MPI_COMM_WORLD);
		printf("M(%d,%d)\n",P2, P1);

		MPI_Send(topology[P2], NoChilds, MPI_INT, 1, 2, MPI_COMM_WORLD);
		printf("M(%d,%d)\n",P2, P1);

			//trimit copiilor lui 2 topologia
		for(int i = 0; i < NoChilds; i++) {
			MPI_Send(&NoChilds, 1, MPI_INT, topology[P2][i], 2, MPI_COMM_WORLD);
			printf("M(%d,%d)\n",P2, topology[P2][i]);

			MPI_Send(&len1, 1, MPI_INT, topology[P2][i], 1, MPI_COMM_WORLD);
			printf("M(%d,%d)\n",P2, topology[P2][i]);

			MPI_Send(&len0, 1, MPI_INT, topology[P2][i], 0, MPI_COMM_WORLD);
			printf("M(%d,%d)\n",P2, topology[P2][i]);

			MPI_Send(topology[P2], NoChilds, MPI_INT, topology[P2][i], 2, MPI_COMM_WORLD);
			printf("M(%d,%d)\n",P2, topology[P2][i]);

			MPI_Send(topology[P1], len1, MPI_INT, topology[P2][i], 1, MPI_COMM_WORLD);
			printf("M(%d,%d)\n",P2, topology[P2][i]);

			MPI_Send(topology[P0], len0, MPI_INT, topology[P2][i], 0, MPI_COMM_WORLD);
			printf("M(%d,%d)\n",P2, topology[P2][i]);
		}

		MPI_Recv(&N, 1, MPI_INT, P0, 2, MPI_COMM_WORLD, &status);
		int *aux = (int *)malloc(N * sizeof(int));

			//primesc de la 0 si trimit workerilor vectorii si informatiile
		for(index = 0 ; index < NoChilds; index++) {
			MPI_Recv(aux, N, MPI_INT, P0, 2, MPI_COMM_WORLD, &status);
			MPI_Recv(&start, 1, MPI_INT, P0, 2, MPI_COMM_WORLD, &status);
			MPI_Recv(&end, 1, MPI_INT, P0, 2, MPI_COMM_WORLD, &status);

			MPI_Send(&N, 1, MPI_INT, topology[P2][index], 2,MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P2, topology[P2][index]);

			MPI_Send(aux, N, MPI_INT, topology[P2][index], 2, MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P2, topology[P2][index]);

			MPI_Send(&start, 1, MPI_INT, topology[P2][index], 2, MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P2, topology[P2][index]);

			MPI_Send(&end, 1, MPI_INT, topology[P2][index], 2, MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P2, topology[P2][index]);
		}

		MPI_Send(&N, 1, MPI_INT, P1, 1,MPI_COMM_WORLD);
		printf("M(%d,%d)\n", P2, P1);

			//primesc de la 0 si trimit lui 1 vectorul si informatiile
		for(index = 0; index < len1; index++) {
			MPI_Recv(aux, N, MPI_INT, P0, 2, MPI_COMM_WORLD, &status);
			MPI_Recv(&start, 1, MPI_INT, P0, 2, MPI_COMM_WORLD, &status);
			MPI_Recv(&end, 1, MPI_INT, P0, 2, MPI_COMM_WORLD, &status);

			MPI_Send(aux, N, MPI_INT, P1, 1, MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P2, P1);

			MPI_Send(&start, 1, MPI_INT, P1, 1, MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P2, P1);

			MPI_Send(&end, 1, MPI_INT, P1, 1, MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P2, P1);
		}

			//primesc informatiile de la workeri si le trimit lui 0
		for(index = 0 ; index < NoChilds; index++) {
			MPI_Recv(aux, N, MPI_INT, topology[P2][index], 2, MPI_COMM_WORLD, &status);
			MPI_Recv(&start, 1, MPI_INT, topology[P2][index], 2, MPI_COMM_WORLD, &status);
			MPI_Recv(&end, 1, MPI_INT, topology[P2][index], 2, MPI_COMM_WORLD, &status);

			MPI_Send(aux, N, MPI_INT, P0, 2, MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P2, P0);

			MPI_Send(&start, 1, MPI_INT, P0, 2, MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P2, P0);

			MPI_Send(&end, 1, MPI_INT, P0, 2, MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P2, P0);
		}

			//primesc informatiile de la 1 si le trimit lui 0
		for(index = 0; index < len1; index++) {
			MPI_Recv(aux, N, MPI_INT, P1, 1, MPI_COMM_WORLD, &status);
			MPI_Recv(&start, 1, MPI_INT, P1, 1, MPI_COMM_WORLD, &status);
			MPI_Recv(&end, 1, MPI_INT, P1, 1, MPI_COMM_WORLD, &status);

			MPI_Send(aux, N, MPI_INT, P0, 2, MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P2, P0);

			MPI_Send(&start, 1, MPI_INT, P0, 2, MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P2, P0);

			MPI_Send(&end, 1, MPI_INT, P0, 2, MPI_COMM_WORLD);
			printf("M(%d,%d)\n", P2, P0);
		}

		free(aux);
		for(int i = 0 ; i < 3; i++) {
			free(topology[i]);
		}

	} else {
		int len0, len1, len2;
		int parent;
		int index;
		int start;
		int end;
		int N;

			//primesc informatii despre parinte si topologie
		MPI_Recv(&parent, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);

		MPI_Recv(&len2, 1, MPI_INT, parent, 2, MPI_COMM_WORLD, &status);
		MPI_Recv(&len1, 1, MPI_INT, parent, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&len0, 1, MPI_INT, parent, 0, MPI_COMM_WORLD, &status);

		topology[P0] = (int*) malloc (len0 * sizeof(int));
		topology[P1] = (int*) malloc (len1 * sizeof(int));
		topology[P2] = (int*) malloc (len2 * sizeof(int));

		MPI_Recv(topology[P2], len2, MPI_INT, parent, 2, MPI_COMM_WORLD, &status);
		MPI_Recv(topology[P1], len1, MPI_INT, parent, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(topology[P0], len0, MPI_INT, parent, 0, MPI_COMM_WORLD, &status);

			//afisez topologia
		printf("%d -> %d:", rank, P0);
		for(int i = 0; i < len0-1; i++) {
			printf("%d,", topology[P0][i]);
		}
		printf("%d %d:", topology[P0][len0-1], P1);
		for(int i = 0; i < len1-1; i++) {
			printf("%d,", topology[P1][i]);
		}
		printf("%d %d:", topology[P1][len1-1], P2);
		for(int i = 0; i < len2-1; i++) {
			printf("%d,", topology[P2][i]);
		}
		printf("%d\n", topology[P2][len2-1]);

			//primesc informatii(vectorul,dimenziunea lui si intervalele)
		MPI_Recv(&N, 1, MPI_INT, parent, parent, MPI_COMM_WORLD, &status);
		int *aux = (int *) calloc(N, sizeof(int));

		MPI_Recv(aux, N, MPI_INT, parent, parent, MPI_COMM_WORLD, &status);
		MPI_Recv(&start, 1, MPI_INT, parent, parent, MPI_COMM_WORLD, &status);
		MPI_Recv(&end, 1, MPI_INT, parent, parent, MPI_COMM_WORLD, &status);

			//efectuez operatiile si trimit inapoi parintilor rezultatele
		for(int i = start; i < end; i++) {
			aux[i] *= 2;
		}

		MPI_Send(aux, N, MPI_INT, parent, parent, MPI_COMM_WORLD);
		printf("M(%d,%d)\n", rank, parent);

		MPI_Send(&start, 1, MPI_INT, parent, parent, MPI_COMM_WORLD);
		printf("M(%d,%d)\n", rank, parent);

		MPI_Send(&end, 1, MPI_INT, parent, parent, MPI_COMM_WORLD);
		printf("M(%d,%d)\n", rank, parent);

		free(aux);
		for(int i = 0 ; i < 3; i++) {
			free(topology[i]);
		}
	}

	free(v);
	free(topology);

	MPI_Finalize();

	return 0;
}
