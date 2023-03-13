/////////////////////////////////////////////////////
//                                                 //
//  ATIVIDADE PRATICA 3 - MERGESORT                //
//  FLÁVIO AUGUSTO ALÓ TORRES                      //
//  Num. de matrícula: 2020030477  @ UNIFEI        //
//  Feito em 25/05/2021                            //
//                                                 //
/////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "mergesort.h"
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
  //printf("\n");
  mergeSort(vet, inicio, fim);
  imprimeVetor(vet,tam);
  return 0;
}