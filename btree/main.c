#include <stdio.h>
#include "btree.h"

int main() {
    arvoreB *A = criaArvore(6);
    insereElemento(A, 30);
    insereElemento(A, 20);
    insereElemento(A, 10);
    insereElemento(A, 5);
    insereElemento(A, 7);
    insereElemento(A, 18);
    insereElemento(A, 15);
    insereElemento(A, 12);
    insereElemento(A, 13);
    insereElemento(A, 14);
    imprimeArvore(retornaRaiz(A));
    removeElemento(A, 18);
    printf("\n");
    imprimeArvore(retornaRaiz(A));
    removeElemento(A, 7);
    printf("\n");
    imprimeArvore(retornaRaiz(A));
    removeElemento(A, 13);
    printf("\n");
    imprimeArvore(retornaRaiz(A));
    removeElemento(A, 15);
    printf("\n");
    imprimeArvore(retornaRaiz(A));
    removeElemento(A, 12);
    printf("\n");
    imprimeArvore(retornaRaiz(A));
    removeElemento(A, 10);
    printf("\n");
    imprimeArvore(retornaRaiz(A));
    return 0;
}