#include <stdio.h>
#include <stdlib.h>
#include "ABP.h"

//FLÁVIO AUGUSTO ALÓ TORRES - 2020030477
//FEITO NO DIA 21/06/2021
//ALGORITMO E ESTRUTURA DE DADOS 2
//ARVORE BINARIA DE PESQUISA/BUSCA - COM SENTINELA E PAI NA TAD
//PROF. VANESSA
//IMC - UNIFEI - MG


struct no{
  int chave;
  struct no *esq;
  struct no *dir;
  struct no *pai;
};

struct arvore{
  struct no* sentinela;
};

arvore* criaArvore(){

  //Alocação da struct arvore e da struct sentinela.
  arvore* A = (arvore*)malloc( sizeof(arvore) );
  no* sentinela = (no*)malloc( sizeof(no) );

  //verifica erros.
  if(!A || !sentinela){
    printf("\nErro de alocação de memória!\n\n\n");
    return 0; 
  }

  sentinela->chave = -1000;
  sentinela->esq = NULL;
  sentinela->dir = NULL;
  sentinela->pai = NULL;
  A->sentinela = sentinela;

  return A;
}

void insereNo(arvore *A, int chave){
  no* raiz = (no*)malloc( sizeof(no) );
  raiz = A->sentinela->dir;

  no* novo = (no*)malloc( sizeof(no) );
  novo->dir = NULL;
  novo->esq = NULL;
  novo->pai = NULL;
  novo->chave = chave;

  //Caso não exista raíz ainda, criar uma.
  if(A->sentinela->dir == NULL){ 
    A->sentinela->dir = novo;
    novo->pai = A->sentinela;
  }else{ //se existir, colocar na arvore.

    no *anterior = NULL;
    no *atual = A->sentinela->dir;

    //percorrer arvore
    while(atual != NULL){

      anterior = atual;

      if(chave >= atual->chave){
        atual = atual->dir;
      }else{
        atual = atual->esq;
      }
    }

    //processo de colocar o novo no lugar correto
    //tentar colocar ATUAL no lugar de NOVO para ver o que acontece.
    if(chave >= anterior->chave){
      anterior->dir = novo;
    }else{
      anterior->esq = novo;
    }

    //mostra qual é o pai do novo nó
    novo->pai = anterior;

  }
}

void insereArquivo(arvore *A, char nomeArquivo[]){

  int x;
  FILE *file;
  file = fopen(nomeArquivo, "r");

  while(fscanf(file, "%d", &x) != EOF){
    insereNo(A, x);
  }
  fclose(file);
}

void removeNo(arvore *A, int chave){

  no *remover = retornaNo(A, chave);
  no *sucessor;

  if(!remover){
    //não faz nada.
  }
  else{
    
    if(remover->esq == NULL && remover->dir == NULL){ //caso nao tenha filhos

      if(remover->pai->esq == remover){ //aqui
        remover->pai->esq = NULL;
      }else{
        remover->pai->dir = NULL;
      } //VERIFICAR O FUNCIONAMENTO DISSO !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
      free(remover);

    }else{

      if(remover->esq != NULL && remover-> dir == NULL){ //caso tenha um filho a esquerda

      if(remover->pai->esq == remover){
            remover->pai->esq = remover->esq;
            free(remover);
          }else{
            remover->pai->dir = remover->esq;
            free(remover);
          }

      }else{

        if(remover->esq == NULL && remover->dir != NULL){//caso tenha um filho a direita
          if(remover->pai->esq == remover){
            remover->pai->esq = remover->dir;
            free(remover);
          }else{
            remover->pai->dir = remover->dir;
            free(remover);
          }

        }else{ //caso tenha dois filhos

          sucessor = remover->dir; 

          while(sucessor->esq != NULL){ //filho mais a esquerda da subarvore da direita
              sucessor = sucessor->esq;
          }
          remover->chave = sucessor->chave;
          remover = sucessor;
          //free(remover);//OLHAR AQUI!!!!!!!!!!!!!!!!!!!!!!!!!!!!

        }
      }
    }
  }
}

no *retornaNo(arvore *A, int chave){
  no *atual = A->sentinela->dir;
  while(atual != NULL)
    {
        if(chave == atual->chave){
            return atual; //achou.
        }

        if(chave < atual->chave){
            atual = atual->esq;
        }else{
            atual = atual->dir;
        }
    }
  return NULL; //nao achou.
}

no *retornaRaiz(arvore *A){
  return A->sentinela->dir;
}

void percorreArvore(no *raiz){ //in-order

  if(raiz != NULL){

    percorreArvore(raiz->esq);
    printf("%d ", raiz->chave);
    percorreArvore(raiz->dir);

  }
  return;
}

void imprimeDados(no *elemento){

  no *atual = elemento;
  printf("Chave:%d\n", atual->chave);
  
  if(atual->esq == NULL){
    printf("Esq:NULO\n");
  }else{
    printf("Esq:%d\n", atual->esq->chave);
  }
  
  if(atual->dir == NULL){
    printf("Dir:NULO\n");
  }else{
    printf("Dir:%d\n", atual->dir->chave);
  }
  
  if(atual->pai == NULL){
    printf("Pai:NULO\n");
  }else{
    printf("Pai:%d\n", atual->pai->chave);
  }
  return;
}

void rotEsq(no *noDesbalanceado){

  no *filhoEsq;
  no *esqFilho;

  filhoEsq = noDesbalanceado->esq;
  dirFilho = filhoEsq->dir;

  filhoEsq->pai = noDesbalanceado->pai;
  noDesbalanceado->pai = filhoEsq;

  noDesbalanceado->esq = dirFilho;

  if(dirFilho != NULL){
    dirFilho->pai = noDesbalanceado;
  }

  noDesbalanceado->fb = 0;
  filhoEsq->fb = 0;


}
 

