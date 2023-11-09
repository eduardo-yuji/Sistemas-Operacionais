#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <iostream>
#include "thread.h"
#include "mutex.h"

/*
Threads independentes, não geram inconsistência no resultado final,
no entanto os cout's parecem fora de ordem
*/

/* number of matrix columns and rows */
#define M 5
#define N 10
#define NUM_THREADS 10
 
sem_t sem;
int matrix[N][M];
int sum_total;
Mutex mutex;
 
/* thread function; it sums the values of the matrix in the row */
int SumValues(int i){

    mutex.lock();
    int n = (long) i; /* number of row */
    int total = 0; /* the total of the values in the row */
    int j;
    for (j = 0; j < M; j++)/* sum values in the "n" row */
        total += matrix[n][j];
    mutex.unlock();

    printf("The total in row %d is %d  \n", n, total);

    return total;
}

int main(int argc, char *argv[]){
    sum_total = 0;
    int i, j;
    int total = 0; /* the total of the values in the matrix */
    
  
    /* initialize the matrix */
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            matrix[i][j] = i * M + j;
 
    /* create threads */
    Thread * threads[NUM_THREADS];
    /* COLOQUE SEU CÓDIGO PARA CRIAR AS THREADS AQUI! */

      
    /* wait for terminate a threads */ 
    for(int i = 0; i < N; i++){
        threads[i] = new Thread(&SumValues,i);
    }
    for(int i = 0; i < N; i++){
        threads[i] -> join(&sum_total);
        total += sum_total;
    }

    /* COLOQUE SEU CÓDIGO PARA PEGAR O SOMATÓRIO DE LINHAS E TOTALIZAR A SOMA DA MATRIZ AQUI! */
 
     printf("The total values in the matrix is %d \n", total);
 

    return 0;
}