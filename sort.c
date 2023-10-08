#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

#define TAMANHO_DA_LISTA1 8
#define TAMANHO_DA_LISTA2 16
#define TAMANHO_DA_LISTA3 32


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
    int lista2[TAMANHO_DA_LISTA2];
    int lista3[TAMANHO_DA_LISTA3];

    int ranque, num_procs;
    double tempo_inicial, tempo_final;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &ranque);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs); 

    if(ranque == 0) {
        for (int i = 0; i < TAMANHO_DA_LISTA1; i++) {
            lista1[i] = rand() % 100;
        }
        for (int i = 0; i < TAMANHO_DA_LISTA2; i++) {
            lista2[i] = rand() % 100;
        }
        for (int i = 0; i < TAMANHO_DA_LISTA3; i++) {
            lista3[i] = rand() % 100;
        }
        /********** PRINTA LISTAS ANTES ***********/
        printf("Listas:\n");
        for (int i = 0; i < TAMANHO_DA_LISTA1; i++) {
            printf("%d ", lista1[i]);
        }
        printf("\n");
        for (int i = 0; i < TAMANHO_DA_LISTA2; i++) {
            printf("%d ", lista2[i]);
        }
        printf("\n");
        for (int i = 0; i < TAMANHO_DA_LISTA3; i++) {
            printf("%d ", lista3[i]);
        } 
        printf("\n\n");
        /******************************************/
    }

    // lista1
    tempo_inicial = MPI_Wtime(); 

    int tam1 = TAMANHO_DA_LISTA1 / num_procs;

    MPI_Scatter(lista1, tam1, MPI_INT, lista1, tam1, MPI_INT, 0, MPI_COMM_WORLD);
    bitonicSort(lista1, 0, tam1, 1);
    MPI_Gather(lista1, tam1, MPI_INT, lista1, tam1, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    tempo_final = MPI_Wtime();
    if(ranque == 0) {
        printf("Lista 1: Foram gastos %3.5f segundos\n\n",tempo_final-tempo_inicial);
    }

    
    // lista2
    tempo_inicial = MPI_Wtime(); 

    int tam2 = TAMANHO_DA_LISTA2 / num_procs;

    MPI_Scatter(lista2, tam2, MPI_INT, lista2, tam2, MPI_INT, 0, MPI_COMM_WORLD);
    bitonicSort(lista2, 0, tam2, 1);
    MPI_Gather(lista2, tam2, MPI_INT, lista2, tam2, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    tempo_final = MPI_Wtime();
    if(ranque == 0) {
        printf("Lista 2: Foram gastos %3.5f segundos\n\n",tempo_final-tempo_inicial);
    }


    // lista3
    tempo_inicial = MPI_Wtime(); 

    int tam3 = TAMANHO_DA_LISTA3 / num_procs;

    MPI_Scatter(lista3, tam3, MPI_INT, lista3, tam3, MPI_INT, 0, MPI_COMM_WORLD);
    bitonicSort(lista3, 0, tam3, 1);
    MPI_Gather(lista3, tam3, MPI_INT, lista3, tam3, MPI_INT, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    tempo_final = MPI_Wtime();
    if(ranque == 0) {
        printf("Lista 3: Foram gastos %3.5f segundos\n\n",tempo_final-tempo_inicial);
    }
    
    MPI_Finalize();   
        
    if(ranque == 0) {
        /********** PRINTA LISTAS DEPOIS ***********/
        printf("\nListas após o sort:\n");
        for (int i = 0; i < TAMANHO_DA_LISTA1; i++) {
            printf("%d ", lista1[i]);
        }
        printf("\n");
        for (int i = 0; i < TAMANHO_DA_LISTA2; i++) {
            printf("%d ", lista2[i]);
        }
        printf("\n");
        for (int i = 0; i < TAMANHO_DA_LISTA3; i++) {
            printf("%d ", lista3[i]);
        } 
        printf("\n\n");
    }

    return 0;
}
