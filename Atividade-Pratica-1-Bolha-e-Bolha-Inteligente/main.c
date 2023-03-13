#include <stdio.h>
#include <stdlib.h>
#include "bolha.h"
#include <time.h>

int main(void){
  char nomeArquivo[4] = "nome";
  int qtNumeros = 500;
  int tam = 500;
  int vet[500];

  geraNumerosAleatorios(qtNumeros, nomeArquivo);
  carregaVetor(vet, tam, nomeArquivo);
  imprimeVetor(vet, tam);
  bolhaInteligente(vet, tam);
  imprimeVetor(vet, tam);


}