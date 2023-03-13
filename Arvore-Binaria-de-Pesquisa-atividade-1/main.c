#include <stdio.h>
#include <stdlib.h>
#include "ABP.h"

int main(void) {

  int chave = 142;
  arvore *A = criaArvore();
  insereArquivo(A, "arquivo.txt");
  no *raiz = retornaRaiz(A);
  percorreArvore(raiz);
  no *elemento = retornaNo(A, chave);
  imprimeDados(elemento);

  return 0;
}