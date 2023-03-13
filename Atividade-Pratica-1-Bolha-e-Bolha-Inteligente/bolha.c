//FLAVIO AUGUSTO ALO TORRES
//2020030477

#include <stdio.h>
#include <stdlib.h>
#include "bolha.h"
#include <time.h>


void geraNumerosAleatorios(int qtNumeros, char nomeArquivo[]){
  int aleatorio;
  srand(time(NULL));
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

void bolha(int vet[], int tam){
  int aux;
  for(int i=0; i<tam; i++){
    for(int j=0; j<tam-1; j++){
      if(vet[j]>vet[j+1]){
        aux = vet[j];
        vet[j] = vet[j+1];
        vet[j+1] = aux;
      }
    }
  }
}

void bolhaInteligente(int vet[], int tam){
  int aux;
  int x = tam;
  for(int i=0; i<tam; i++){
    for(int j=0; j<x-1; j++){
      if(vet[j]>vet[j+1]){
        aux = vet[j];
        vet[j] = vet[j+1];
        vet[j+1] = aux;
      }
    }
    x--;
  }
}

void imprimeVetor(int vet[], int tam){
  for(int i=0; i<tam; i++){
    printf("%d ", vet[i]);
  }
  printf("\n");
}