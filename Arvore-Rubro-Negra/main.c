#include <stdio.h>
#include <stdlib.h>
#include "rubroNegra.h"

int main(void) {
  
  arvore *A = criaArvore();

  insereArquivo(A, "arquivo.txt");
  percorreArvore(A, retornaRaiz(A));
  printf("\n%d\n", profundidade(A, retornaRaiz(A)));

  removeNo(A, 7);
  removeNo(A, 11);
  removeNo(A, 144);
  removeNo(A, 75);
  removeNo(A, 73);
  removeNo(A, 150);
  removeNo(A, 35);
  removeNo(A, 33);
  removeNo(A, 3);
  removeNo(A, 65);
  printf("\n");
  percorreArvore(A, retornaRaiz(A));
  printf("\n%d\n", profundidade(A, retornaRaiz(A)));
  return 0;
}