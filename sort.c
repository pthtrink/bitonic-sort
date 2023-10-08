#include <stdio.h>
#include <stdlib.h>

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
    int k, i;    
    if (qtd > 1) {    
        k = qtd / 2;    
        for (i = lowerIndex; i < lowerIndex+k; i++)    
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


int main() {

    int lista1[TAMANHO_DA_LISTA1];
    int lista2[TAMANHO_DA_LISTA2];
    int lista3[TAMANHO_DA_LISTA3];
    
    /********** GERA LISTAS ***********/
    printf("Gerando listas...\n\n");
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
    
    /********** CHAMA SORT ***********/
    printf("Ordenando listas...\n\n");
    int qtd1 = sizeof(lista1)/sizeof(lista1[0]);   
    int direcao1 = 1;
    bitonicSort(lista1, 0, qtd1, direcao1);

    int qtd2 = sizeof(lista2)/sizeof(lista2[0]);   
    int direcao2 = 1;
    bitonicSort(lista2, 0, qtd2, direcao2);

    int qtd3 = sizeof(lista3)/sizeof(lista3[0]);   
    int direcao3 = 1;
    bitonicSort(lista3, 0, qtd3, direcao3);
        
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


