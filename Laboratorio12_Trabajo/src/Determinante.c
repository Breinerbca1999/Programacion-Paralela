#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "timer.h"

double calcularParte(double **m, int b, int rank);
void LLenarMatrizInferior(double **A,double **U, double **L, int dx);
void HallarMatrizIdentidad(double **A,double **U,double **L,int dx);
int Signo(int a,int dx);
double Determinante(double **A, int dx);
void MostrarMatriz(double **A, int dx);
double Repartir(double **A,int dx);

int main(int argc, char *argv[]) {
	double detTotal = 0;
	srand(time(NULL));
	int n;
	printf("Ingrese el valor de N: ");
	scanf("%d", &n);
	double **A = (double **) malloc(sizeof(double*) * n);
	for (int h = 0; h < n; h++)
		A[h] = (double *) malloc(sizeof(double) * n);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			A[i][j] = rand() % 5+1;
			//printf("A[%d][%d]:",i,j);
			//scanf("%f",A[i][j]);
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%f ", A[i][j]);
		}
		printf("\n");
	}

	//int numThreads,rank;
	omp_set_num_threads(n);

#pragma omp parallel
	{
		int rank = omp_get_thread_num();
		int numHilos = omp_get_num_threads();
#pragma omp critical
		detTotal += calcularParte(A,n,rank);
		printf("-----------------------\n");
	}
	printf("Con Hilos: %lf", detTotal);
	//double total=Repartir(A,n);
	return 0;
}

double Repartir(double **A,int dx)
{
	double total=0;
	for(int rank=0;rank<dx;rank++)
	{
		total+=calcularParte(A,dx,rank);
		printf("--------------------\n");
	}
	printf("\nEl determinante total fue: %f \n",total);
	return total;
}


double calcularParte(double **A, int dx,int rank) {

	double ni = (double) dx;
	int c;

	if (dx == 2)

		return A[0][0] * A[1][1] - A[1][0] * A[0][1];

	else {
		double **Cofactor = (double **) malloc(sizeof(double*) * (ni - 1));
		for (int h = 0; h < (dx - 1); h++)
			Cofactor[h] = (double *) malloc(sizeof(double) * (ni - 1));

		for (int i = 1; i < dx; i++) {

			c = 0;

			for (int j = 0; j < dx; j++) {

				if (j != rank) {
					Cofactor[i - 1][c] = A[i][j];
					c++;
				}
			}
		}

		double **Li = (double **) malloc(sizeof(double*) * (ni - 1));
		for (int h = 0; h < (dx - 1); h++)
			Li[h] = (double *) malloc(sizeof(double) * (ni - 1));

		double **Ui = (double **) malloc(sizeof(double*) * (ni - 1));
		for (int h = 0; h < (dx - 1); h++)
			Ui[h] = (double *) malloc(sizeof(double) * (ni - 1));

		printf("\nMostrando Matriz COFACTOR : \n:");
		MostrarMatriz(Cofactor, dx - 1);


		 LLenarMatrizInferior(Cofactor,Ui,Li,dx-1);
		 HallarMatrizIdentidad(Cofactor,Ui,Li,dx-1);
		 printf("\nMostrando Matriz L \n:");
		 MostrarMatriz(Li,dx-1);
		 printf("\nMostrando Matriz U \n:");
		 MostrarMatriz(Ui,dx-1);
		 printf("\nMostrando Matriz A \n:");
		 MostrarMatriz(Cofactor,dx-1);

		 printf("LA DETERMINANTE DE L ES:%f \n",Determinante(Li,dx-1));
		 printf("LA DETERMINANTE DE U ES:%f \n",Determinante(Ui,dx-1));
		 double Determinant=Determinante(Li,dx-1)*Determinante(Cofactor,dx-1);
		 printf("LA DETERMINANTE DE A ES:%f \n",Determinant);

		 /*
		 for(int q = 0; q<(dx-1); q++)

		 free(A[q]);

		 for(int q = 0; q<(dx-1); q++)

		 free(Li[q]);

		  for(int q = 0; q<(dx-1); q++)

		 free(Ui[q]);

		 free(Cofactor);
		 free(Li);
		 free(Ui);
		*/
		 return Signo(-1,2+rank)*A[0][rank]*Determinant;

		//return 1;
	}
}


//void LLenarMatrizInferior(double **A,double **L,double **U,int dx)
void LLenarMatrizInferior(double **A,double **U,double **L,int dx)
{
	for(int i=0;i<dx;i++)
	{
		for(int j=0;j<dx;j++)
		{
			if(i==j)
			{
				L[i][j]=1;
				U[i][j]=A[i][j];
			}else{
				L[i][j]=0;
				U[i][j]=A[i][j];
			}
		}
	}
}

void HallarMatrizIdentidad(double **A, double **U,double **L, int dx) {
	int i = 0, j = 0;
	int w = 0, y = 0;
	double mult = 0;
	while (i < dx) {       //i,j son para avanzar en forma (1,1);(2,2).....(n,n)
		w = i + 1;
		while (w < dx) {
			mult = A[w][j] / A[i][j];
			A[w][j] = 0;
			U[w][j]=A[w][j];
			y = j + 1;
			while (y < dx) {
				A[w][y] = A[w][y] - (mult) * (A[i][y]);         //E2-mult*E1
				U[w][y]=A[w][y];
				y++;
			}
			//Para Guardar el L
			L[w][i] = mult;
			w++;
		}
		i++;
		j++;
	}
}

double Determinante(double **A, int dx) {
	double a = 1;
	for (int i = 0; i < dx; i++) {
		a *= A[i][i];
	}
	return a;
}

void MostrarMatriz(double **A, int dx) {
	for (int i = 0; i < dx; i++) {
		for (int j = 0; j < dx; j++) {
			//cout<<"A["<<i<<"]["<<j<<"]:"<<A[i][j];
			printf("A[%d][%d]:%f \t", i, j, A[i][j]);
			//cout<<"\t";
		}
		//cout<<"\n";
		printf("\n");
	}
}

int Signo(int a,int dx)
{
	int signo=1;
	for(int i=0;i<dx;i++)
	{
		signo*=a;
	}
	return signo;
}
