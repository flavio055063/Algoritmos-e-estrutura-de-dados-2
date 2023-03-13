#include <stdio.h>
#include <stdlib.h>
#include "heapsort.h"
#include <time.h>

int main(void) {

  srand(time(NULL)); 

  int inicio, fim, qtNumeros, tam;
  int vet[15];
  inicio = 0;
  fim = 14;
  qtNumeros = 15;
  tam = 15;
  char nomeArquivo[16] = "arquivo.txt";


  geraNumerosAleatorios(qtNumeros, nomeArquivo);
  carregaVetor(vet, tam, nomeArquivo);
  imprimeVetor(vet,tam);

  printf("\n");

  heapSort(vet, tam);
  imprimeVetor(vet,tam);



  return 0;
}