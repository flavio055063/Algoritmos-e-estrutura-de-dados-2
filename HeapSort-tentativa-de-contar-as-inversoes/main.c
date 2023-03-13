#include <stdio.h>
#include <stdlib.h>
#include "heapsort.h"
#include <time.h>



int main(void) {

  srand(time(NULL)); 

  int inicio, fim, qtNumeros, tam;
  int vet[10];
  inicio = 0;
  fim = 10;
  qtNumeros = 11;
  tam = 10;
  char nomeArquivo[16] = "arquivo.txt";


  geraNumerosAleatorios(qtNumeros, nomeArquivo);
  carregaVetor(vet, tam, nomeArquivo);
  imprimeVetor(vet,tam);

  printf("Inversoes corretas: %d", getInvCount(vet, tam));
  printf("\n");

  int inversoesErradas = mergeSort(vet, inicio, fim);
  printf("O numero de inversoes merge: %d\n", inversoesErradas);

  imprimeVetor(vet, tam);


  return 0;
}