/////////////////////////////////////////////////////
//                                                 //
//  ATIVIDADE PRATICA 3 --- MERGESORT              //
//  FLÁVIO AUGUSTO ALÓ TORRES                      //
//  Num. de matrícula: 2020030477  @ UNIFEI        //
//  Feito em 14/05/2021                            //
//                                                 //
/////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "mergesort.h"
#include <time.h>

void geraNumerosAleatorios(int qtNumeros, char nomeArquivo[]){
  int aleatorio;
  //srand(time(NULL));
  FILE *file;
  file = fopen(nomeArquivo, "w");

  for(int i=0; i<qtNumeros; i++){

    aleatorio = rand()%5000 + 1;
    fprintf(file, "%d ", aleatorio);

  }
  fclose(file);
}

void carregaVetor(int vet[], int tam, char nomeArquivo[]){
  FILE *file;
  file = fopen(nomeArquivo, "r");

  for(int i=0; i<tam; i++){
    fscanf(file, "%d", &vet[i]);
  }
  fclose(file);
}

void imprimeVetor(int vet[], int tam){
  for(int i=0; i<tam; i++){
    printf("%d ", vet[i]);
  }
  printf("\n");
}


//Código adaptado de: //https://www.geeksforgeeks.org/merge-sort/
void merge(int vet[], int inicio, int meio, int fim){

    int i, j, k;
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;
 
    /* create temp arrays */
    int L[n1], R[n2];
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = vet[inicio + i];
    for (j = 0; j < n2; j++)
        R[j] = vet[meio + 1 + j];
 
    i = 0;
    j = 0; 
    k = inicio; 

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vet[k] = L[i];
            i++;
        }
        else {
            vet[k] = R[j];
            j++;
        }
        k++;
    }
 
    while (i < n1) {
        vet[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        vet[k] = R[j];
        j++;
        k++;
    }
}

//Código adaptado de: //https://www.geeksforgeeks.org/merge-sort/
void mergeSort(int vet[], int inicio, int fim)
{
    if (inicio < fim) {
       
        int m = inicio + (fim - inicio) / 2;
 
        //arruma as duas partes
        mergeSort(vet, inicio, m);
        mergeSort(vet, m + 1, fim);
 
        merge(vet, inicio, m, fim);
    }
}

