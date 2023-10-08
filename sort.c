#include <stdio.h>
#include "mpi.h"

#define TAMANHO_DA_LISTA1 8
#define TAMANHO_DA_LISTA2 16
#define TAMANHO_DA_LISTA3 32


void compara(int l[], int i, int j, int d) {    
    int aux;    
    if (d == (l[i] > l[j])) {    
        aux = l[i];    
        l[i] = l[j];    
        l[j] = aux;    
    }    
}    

void bitonicMerge(int l[], int lowerIndex, int qtd, int d) {    
    int k;    
    if (qtd > 1) {    
        k = qtd / 2;    
        for (int i = lowerIndex; i < lowerIndex+k; i++)    
            compara(l, i, i+k, d);    
        bitonicMerge(l, lowerIndex, k, d);    
        bitonicMerge(l, lowerIndex+k, k, d);    
    }    
}  

void bitonicSort(int l[], int lowerIndex, int qtd, int d) { 
    int k;    
    if (qtd > 1) {    
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

    int meu_ranque, num_procs;
    double tempo_inicial, tempo_final;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &meu_ranque);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs); 
    
    // lista1
    MPI_Bcast(lista1, TAMANHO_DA_LISTA1, MPI_INT, 0, MPI_COMM_WORLD); // distribui o dado para todos os outros processos
    tempo_inicial = MPI_Wtime(); 
    int qtd1 = sizeof(lista1)/sizeof(lista1[0]);   

    int local_size1 = TAMANHO_DA_LISTA1 / num_procs;
    int* local_arr1 = (int*)malloc(local_size1 * sizeof(int));
    MPI_Scatter(lista1, local_size1, MPI_INT, local_arr1, local_size1, MPI_INT, 0, MPI_COMM_WORLD);

    bitonicSort(local_arr1, 0, local_size1, 1);

    MPI_Gather(local_arr1, local_size1, MPI_INT, lista1, local_size1, MPI_INT, 0, MPI_COMM_WORLD);

    tempo_final = MPI_Wtime();
    printf("Lista 1: Foram gastos %3.5f segundos\n",tempo_final-tempo_inicial);

    /*
    // lista2
    MPI_Bcast(lista2, TAMANHO_DA_LISTA2, MPI_INT, 0, MPI_COMM_WORLD); // distribui o dado para todos os outros processos
    tempo_inicial = MPI_Wtime(); 
    printf("Foram gastos %3.5f segundos\n",tempo_final-tempo_inicial);
    int qtd2 = sizeof(lista2)/sizeof(lista2[0]);   
    int direcao2 = 1;

    int local_size2 = TAMANHO_DA_LISTA2 / num_procs;
    int* local_arr2 = (int*)malloc(local_size2 * sizeof(int));
    MPI_Scatter(lista2, local_size2, MPI_INT, local_arr2, local_size2, MPI_INT, 0, MPI_COMM_WORLD);

    bitonicSort(local_arr2, 0, local_size2, direcao2);

    MPI_Gather(local_arr2, local_size2, MPI_INT, lista2, local_size2, MPI_INT, 0, MPI_COMM_WORLD);
    tempo_final = MPI_Wtime();
    printf("Lista 2: Foram gastos %3.5f segundos\n",tempo_final-tempo_inicial);


    // lista3
    MPI_Bcast(lista3, TAMANHO_DA_LISTA3, MPI_INT, 0, MPI_COMM_WORLD); // distribui o dado para todos os outros processos
    tempo_inicial = MPI_Wtime(); 
    int qtd3 = sizeof(lista3)/sizeof(lista3[0]);   
    int direcao3 = 1;
    
    int local_size3 = TAMANHO_DA_LISTA3 / num_procs;
    int* local_arr3 = (int*)malloc(local_size3 * sizeof(int));
    MPI_Scatter(lista3, local_size3, MPI_INT, local_arr3, local_size3, MPI_INT, 0, MPI_COMM_WORLD);

    bitonicSort(local_arr3, 0, local_size3, direcao3);

    MPI_Gather(local_arr3, local_size3, MPI_INT, lista3, local_size3, MPI_INT, 0, MPI_COMM_WORLD);

    tempo_final = MPI_Wtime();
    printf("Lista 3: Foram gastos %3.5f segundos\n",tempo_final-tempo_inicial); 

    */
    MPI_Finalize();   
        
    /********** PRINTA LISTAS DEPOIS ***********/
    printf("Listas após o sort:\n");
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
    

    return 0;
}


