//
// Created by vanes on 30/06/2021.
//

#ifndef INC_8_RN_RUBRONEGRA_H
#define INC_8_RN_RUBRONEGRA_H

typedef struct no no;
typedef struct arvore arvore;

arvore* criaArvore();

void insereNo(arvore *A, int chave);
//Insere um nó ná árvore rubro-negra
//Se o pai do nó inserido por vermelho, chama a função balanceamentoInsercao

void insereArquivo(arvore *A, char nomeArquivo[]);
//Lê os dados de um arquivo e os insere na árvore
//chamando a função insereNo

void percorreArvore(arvore *A, no *raiz);
//Percorre a árvore em pré-ordem : raiz, esq, dir

no *retornaRaiz(arvore *A);
//Retorna a raiz da árvore a partir da sentinela

void removeNo(arvore *A, int chave);
//Remove o nó da árvore
//Se o nó removido por preto, chama a função balanceamentoRemocao

void rotEsq(arvore *A, no *noDesbalanceado);
//Rotação à esquerda no noDesbalanceado

void rotDir(arvore *A, no *noDesbalanceado);
//Rotação à direita no noDesbalanceado

void balanceamentoInsercao(arvore *A, no *no);
//Aplica as regras para rebalancear a árvore após a inserção
//Olha a cor do tio

void balanceamentoRemocao(arvore *A, no *no);
//Aplica as regras para rebalancear a árvore após a remoção
//Olha a cor do irmão

int profundidade(arvore *A, no *raiz);
//Calcula a profundidade da árvore

int maior(int a, int b);
//Função auxiliar da função profundidade

void geraNumerosAleatorios(int qtNumeros, char nomeArquivo[]);


#endif //INC_8_RN_RUBRONEGRA_H