#ifndef ABP_H
#define ABP_H

typedef struct no no;
typedef struct arvore arvore;


arvore* criaArvore();
//Cria a estrutura árvore que contém um nó sentinela.

void insereNo(arvore *A, int chave);
//Insere um nó na árvore, cujo valor da raiz está no atributo chave.

void insereArquivo(arvore *A, char nomeArquivo[]);
//Esta função lê um arquivo e insere os valores lidos na árvore.
//A função chama a insereNo para cada valor lido no arquivo.

void removeNo(arvore *A, int chave);
//Remove um nó da árvore. O valor a ser removido está no atributo chave.

void percorreArvore(no *raiz);
//Imprime na tela o percorrimento em ordem na árvore.
//Os elementos devem ser impressos em linha, com um espaço entre eles.

no *retornaRaiz(arvore *A);
//Retorna a raiz da árvore a partir da sentinela.

no *retornaNo(arvore *A, int chave);
//Retorna o elemento (nó) da árvore que possui a chave informada.

void imprimeDados(no *elemento);
//Imprime os dados de um nó da seguinte forma:
//Chave:xx
//Esq:xx
//Dir:xx
//Pai:xx
//Se o filho da esquerda e/ou da direita for nulo, escreve "NULO"


#endif //ABP_H