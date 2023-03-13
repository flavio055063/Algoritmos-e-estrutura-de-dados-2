#include <stdio.h>
#include <stdlib.h>
#include "heapsort.h"
#include <time.h>

int inversoes = 0;

void geraNumerosAleatorios(int qtNumeros, char nomeArquivo[]){
  int aleatorio;
  //srand(time(NULL));
  FILE *file;
  file = fopen(nomeArquivo, "w");

  for(int i=0; i<qtNumeros; i++){

    aleatorio = rand()%500 + 1;
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
int merge(int vet[], int inicio, int meio, int fim){

    int inversoes = 0;
    int i, j, k;
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;
    int m = inicio + (fim - inicio) / 2;

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
            inversoes += (m - i);
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
  return inversoes;
}

//Código adaptado de: //https://www.geeksforgeeks.org/merge-sort/
int mergeSort(int vet[], int inicio, int fim){

    int inversoes = 0;

    if (inicio < fim) {
        int m = inicio + (fim - inicio) / 2;
 
        //arruma as duas partes
        inversoes += mergeSort(vet, inicio, m);
        inversoes += mergeSort(vet, m + 1, fim);
 
        inversoes += merge(vet, inicio, m, fim);
    }
    return inversoes;
}

int getInvCount(int arr[], int n)
{
    int inv_count = 0;
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (arr[i] > arr[j])
                inv_count++;
 
    return inv_count;
}


