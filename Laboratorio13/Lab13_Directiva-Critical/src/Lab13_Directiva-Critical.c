/*
 ============================================================================
 Name        : Lab13_Directiva-Critical.c
 Author      : FISI
 Version     :
 Copyright   : Your copyright notice
 Description : Hello OpenMP World in C
 ============================================================================
 */

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int EsPrimo(int n);
int Fibo(int nums);

int main (int argc, char *argv[]) {

  int rank, numHilos;
  //int x=0;
  int total=0;
  int entreLocal=0;

  int n;
  printf("Ingrese el valor de Hilos: ");
  scanf("%d", &n);

  int m;
  printf("Ingrese el valor de la cantidad de la suma de n pares : ");
 scanf("%d", &m);

  omp_set_num_threads(n);

  /* This creates a team of threads; each thread has own copy of variables  */
#pragma omp parallel private(numHilos, rank)
 {
		int rank = omp_get_thread_num();
		int numHilos = omp_get_num_threads();

   int x=0;
   for (int i =0;i<m;i++){


		//#pragma omp critical
	   //x+=2;
	   //x+=Fibo(i);
	   x+=EsPrimo(i);

     // #pragma omp critical
	   entreLocal+=x;
	   ///printf("local: %d \t",x);
   }

   //printf("local: %d \t",x);
   //printf("Entre Local: %d \n",entreLocal);
   total+=entreLocal;

 }
 //printf(" \n total: %d",total);
 printf("\n Total Local fue : %d \n",entreLocal);

 return 0;
}


int EsPrimo(int n)
{
	int bandera=0;
	int suma=0;

	//if(n==2) return 1;
	for(int i = 2; i< n ; i++){
		if (n%i==0)
		{
			 bandera=1;
			 suma=i;
		}
		//suma+=i;
	}


	if(bandera==0)
	{
		return 0;
	}else{
		return suma;
	}
}


int Fibo(int nums)
{

	int contador=0;
	int i=0;
	int suma=0;

	while(contador<nums)
	{
		if(EsPrimo(i)==1){
			contador++;
			suma+=i;
		}
		i++;
	}
	return suma;
}
