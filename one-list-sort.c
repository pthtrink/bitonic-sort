#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define TAMANHO_DA_LISTA1 16

void compara(int l[], int i, int j, int d) {    
    int aux;    
    if(d == (l[i] > l[j])) {    
        aux = l[i];    
        l[i] = l[j];    
        l[j] = aux;    
    }    
}    

void bitonicMerge(int l[], int lowerIndex, int qtd, int d) {    
    int k;    
    if(qtd > 1) {    
        k = qtd / 2;    
        for (int i = lowerIndex; i < lowerIndex+k; i++)    
            compara(l, i, i+k, d);    
        bitonicMerge(l, lowerIndex, k, d);    
        bitonicMerge(l, lowerIndex+k, k, d);    
    }    
}  

void bitonicSort(int l[], int lowerIndex, int qtd, int d) { 
    int k;    
    if(qtd > 1) {    
        k = qtd / 2;    
        bitonicSort(l, lowerIndex, k, 1);
        bitonicSort(l, lowerIndex+k, k, 0);
        bitonicMerge(l, lowerIndex, qtd, d);
    }    
}    


int main(int argc, char *argv[]) {

    int lista1[TAMANHO_DA_LISTA1];

    int ranque, num_procs;
    double tempo_inicial, tempo_final;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &ranque);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs); 

    if(ranque == 0) {
        for (int i = 0; i < TAMANHO_DA_LISTA1; i++) {
            lista1[i] = rand() % 100;
        }
        printf("\nLista antes do sort:\n");
        for (int i = 0; i < TAMANHO_DA_LISTA1; i++) {
            printf("%d ", lista1[i]);
        }
        printf("\n");
    }

    tempo_inicial = MPI_Wtime(); 

    int tam1 = TAMANHO_DA_LISTA1 / num_procs;

    MPI_Scatter(lista1, tam1, MPI_INT, lista1, tam1, MPI_INT, 0, MPI_COMM_WORLD);

    if(ranque % 2 == 0) {
        bitonicSort(lista1, 0, tam1, 1);
    }
    else {
        bitonicSort(lista1, 0, tam1, 0);
    }
    
    MPI_Gather(lista1, tam1, MPI_INT, lista1, tam1, MPI_INT, 0, MPI_COMM_WORLD);

    if(ranque == 0) {
        bitonicSort(lista1, 0, TAMANHO_DA_LISTA1, 1);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    tempo_final = MPI_Wtime();
    if(ranque == 0) {
        printf("\nLista 1: Foram gastos %3.5f segundos\n",tempo_final-tempo_inicial);
    }

    MPI_Finalize();   
        
    if(ranque == 0) {
        printf("\nLista após o sort:\n");
        for (int i = 0; i < TAMANHO_DA_LISTA1; i++) {
            printf("%d ", lista1[i]);
        }
        printf("\n");
    }

    return 0;
}
