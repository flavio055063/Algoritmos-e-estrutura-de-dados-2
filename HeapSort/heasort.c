#include <stdio.h>
#include <stdlib.h>
#include "heapsort.h"
#include <time.h>

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

// adaptado de:
// https://www.geeksforgeeks.org/heap-sort/
void heap(int vet[], int tam, int i)
{
    int aux; //auxiliar de troca
    int maior = i; // inicializa o maior como raiz
    int l = 2 * i + 1; // esquerda = 2*i + 1
    int r = 2 * i + 2; // direita = 2*i + 2
 
    // se o filho da esquerda é maior do que a raiz
    if (l < tam && vet[l] > vet[maior])
        maior = l;
 
    // se o filho da direita é maior que o maior até agora
    if (r < tam && vet[r] > vet[maior])
        maior = r;
 
    // se o maior nao for a raiz
    if (maior != i) {
        aux = vet[i];
        vet[i] = vet[maior];
        vet[maior] = aux;
 
        // recursivamente "heapificar" a sub-árvore afetada
        heap(vet, tam, maior);
    }
}
 
// função principal do HeapSort
// adaptado de:
// https://www.geeksforgeeks.org/heap-sort/
void heapSort(int vet[], int tam)
{
    int aux;
    // Construir a heap (rearranjar o array)
    for (int i = tam/2 - 1; i >= 0; i--){
        heap(vet, tam, i);
    }
    // extrair um elemento da heap um por um
    for (int i = tam - 1; i > 0; i--) {
        // mover a atual raiz para o fim
        aux = vet[0];
        vet[0] = vet[i];
        vet[i] = aux;
 
        // chamar a função max heap na heap reduzida
        heap(vet, i, 0);
    }
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
void mergeSort(int vet[], int inicio, int fim){
    if (inicio < fim) {
       
        int m = inicio + (fim - inicio) / 2;
 
        //arruma as duas partes
        mergeSort(vet, inicio, m);
        mergeSort(vet, m + 1, fim);
 
        merge(vet, inicio, m, fim);
    }
}


