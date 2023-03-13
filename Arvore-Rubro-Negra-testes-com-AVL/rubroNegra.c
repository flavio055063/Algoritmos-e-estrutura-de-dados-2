#include "rubroNegra.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// FLÁVIO AUGUSTO ALÓ TORRES - 2020030477
// CÓDIGO RUBRO NEGRA MODULARIZADO
// ALG EST II - PROF VANESSA @UNIFEI

struct no{
  int chave;
  struct no *esq;
  struct no *dir;
  struct no *pai;
  char cor; 
};

struct arvore{
  struct no *sentinelaRaiz;
  struct no *sentinelaFolha;
};

arvore *criaArvore(){

  arvore *A = (arvore*)malloc(sizeof(arvore));

  if(!A)
  {
    printf("Erro ao alocar memoria!");
    EXIT_FAILURE;
  }

  no *sentinela = (no*)malloc(sizeof(no));

  if(!sentinela)
  {
    printf("Erro ao alocar memoria!");
    EXIT_FAILURE;
  }

  sentinela->chave = -1000;
  sentinela->esq = NULL;
  sentinela->dir = NULL;
  sentinela->pai = NULL;
  sentinela->cor = 'p';
  A->sentinelaRaiz = sentinela;

  no *sentinelaFolha = (no*)malloc(sizeof(no));

  if(!sentinelaFolha)
  {
    printf("Erro ao alocar memoria!");
    EXIT_FAILURE;
  }

  sentinelaFolha->chave = -1000;
  sentinelaFolha->esq = NULL;
  sentinelaFolha->dir = NULL;
  sentinelaFolha->pai = NULL;
  sentinelaFolha->cor = 'p';
  A->sentinelaFolha = sentinelaFolha;

  return A;
}

void insereNo(arvore *A, int chave){

  no *aux;
  no *pai;

  no *novoNo = (no*)malloc(sizeof(no));

  if(!novoNo)
  {
    printf("Erro ao alocar memoria!");
    EXIT_FAILURE;
  }

  novoNo->chave = chave;
  novoNo->esq = A->sentinelaFolha; //toda folha aponta para A->sentinelaFolha
  novoNo->dir = A->sentinelaFolha; //toda folha aponta para A->sentinelaFolha
  novoNo->pai = NULL;
  novoNo->cor = 'v'; //todo novo nó é vermelho

  //colocar novo nó no lugar adequado
  if(A->sentinelaRaiz->dir == NULL) //ainda não há raiz
  {
    A->sentinelaRaiz->dir = novoNo;
    novoNo->pai = A->sentinelaRaiz;
    novoNo->cor = 'p'; //raiz é preta.
    return;
  }

  aux = A->sentinelaRaiz->dir;
  pai = A->sentinelaRaiz;

  while(aux != A->sentinelaFolha)
  {
    pai = aux;
    if(chave < aux->chave)
      aux = aux->esq;
    else
      aux = aux->dir;
  }

  if(chave < pai->chave){
    pai->esq = novoNo;
  }else{
    pai->dir = novoNo;
  }

  novoNo->pai = pai;
  if(novoNo->pai->cor == 'v'){
    balanceamentoInsercao(A, novoNo);
  }
  return;

}

void removeNo(arvore *A, int chave){

  no *aux;
  no *sucessor;
  no *x;

  //encontrar elemento na arvore
  aux = A->sentinelaRaiz->dir;
  while((aux != A->sentinelaFolha) && (aux->chave != chave))
  {
    if(chave < aux->chave)
      aux = aux->esq;
    else
      aux = aux->dir;
  }

  if(aux == A->sentinelaFolha)
  {
    printf("elemento não encontrado na árvore.\n");
    return;
  }

  //etapa de remover o nó
  if((aux->esq != A->sentinelaFolha) && (aux->dir != A->sentinelaFolha))
  {
    sucessor = aux->dir;

    while(sucessor->esq != A->sentinelaFolha)
      sucessor = sucessor->esq;
  
    aux->chave = sucessor->chave;
    aux = sucessor;
  }

  if((aux->esq == A->sentinelaFolha) && (aux->dir == A->sentinelaFolha)) //nó é folha
  {
    if(aux->chave < aux->pai->chave)
      aux->pai->esq = A->sentinelaFolha;
    else
      aux->pai->dir = A->sentinelaFolha;

    if(aux->cor == 'p'){
      A->sentinelaFolha->pai = aux->pai;
      balanceamentoRemocao(A, A->sentinelaFolha);
    }

    A->sentinelaFolha->pai = NULL;
    free(aux);
    return;
  }

  if((aux->esq != A->sentinelaFolha) || (aux->dir != A->sentinelaFolha)) //nó possui um filho
  {

    if(aux->esq != A->sentinelaFolha){ //filho está a esquerda
      x = aux->esq;

      if(aux->chave < aux->pai->chave)
        aux->pai->esq = aux->esq;
      else
        aux->pai->dir = aux->esq;

      aux->esq->pai = aux->pai;
    }

    if(aux->dir != A->sentinelaFolha){
      x = aux->dir;

      if(aux->chave < aux->pai->chave)
        aux->pai->esq = aux->dir;
      else
        aux->pai->dir = aux->dir;

      aux->dir->pai = aux->pai;
    }

    if(aux->cor == 'p')
      balanceamentoRemocao(A, x);

    free(aux);
    return;
  }
}


void percorreArvore(arvore *A, no *raiz){

  if(raiz == A->sentinelaFolha)
    return;

  printf("%d-%c\n", raiz->chave, raiz->cor);
  percorreArvore(A, raiz->esq);
  percorreArvore(A, raiz->dir);

}


no *retornaRaiz(arvore *A){
  return A->sentinelaRaiz->dir;
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

void rotEsq(arvore *A, no *noDesbalanceado){

  no *filhoDir;
  no *esqFilho;

  filhoDir = noDesbalanceado->dir;
  esqFilho = filhoDir->esq;

  filhoDir->pai = noDesbalanceado->pai;
  if(filhoDir->chave < noDesbalanceado->pai->chave)
    noDesbalanceado->pai->esq = filhoDir;
  else
    noDesbalanceado->pai->dir = filhoDir;

  filhoDir->esq = noDesbalanceado;
  noDesbalanceado->pai = filhoDir;
  noDesbalanceado->dir = esqFilho;

  if(esqFilho != A->sentinelaFolha)
    esqFilho->pai = noDesbalanceado;
  
  return;
}


void rotDir(arvore *A, no *noDesbalanceado){

  no *filhoEsq;
  no *dirFilho;

  filhoEsq = noDesbalanceado->esq;
  dirFilho = filhoEsq->dir;

  filhoEsq->pai = noDesbalanceado->pai;

  if(filhoEsq->chave < noDesbalanceado->pai->chave)
    noDesbalanceado->pai->esq = filhoEsq;
  else
    noDesbalanceado->pai->dir = filhoEsq;

  filhoEsq->dir = noDesbalanceado;
  noDesbalanceado->pai = filhoEsq;
  noDesbalanceado->esq = dirFilho;

  if(dirFilho != A->sentinelaFolha)
    dirFilho->pai = noDesbalanceado;
  
  return;
}


void balanceamentoInsercao(arvore *A, no *noDesbalanceado){

  no *pai = noDesbalanceado->pai;
  no *avo = pai->pai;
  no *tio;

  if(noDesbalanceado->chave < avo->chave){

    tio = avo->dir;

    //regras da tabela
    if(tio->cor == 'v'){ //caso tio seja vermelho

      pai->cor = 'p';
      tio->cor = 'p';
      avo->cor = 'v';
      if(avo->pai->cor == 'v')
        balanceamentoInsercao(A, avo);

    }else{ //então tio é preto

      if(noDesbalanceado->chave >= pai->chave){ //caso 2
        noDesbalanceado = pai;
        rotEsq(A, noDesbalanceado);
        pai = noDesbalanceado->pai;
      }
      pai->cor = 'p';
      avo->cor = 'v';
      rotDir(A, avo);
    }
  }else{ // o nó desbalanceado está a direita do avô

    tio = avo->esq;
    //regras da tabela
    if(tio->cor == 'v'){

      pai->cor = 'p';
      tio->cor = 'p';
      avo->cor = 'v';
      if(avo->pai->cor == 'v')
        balanceamentoInsercao(A, avo);

    }else{ //o tio é preto

      if(noDesbalanceado->chave < pai->chave) //caso 2
      {
        noDesbalanceado = pai;
        rotDir(A, noDesbalanceado);
        pai = noDesbalanceado->pai;
      }
      pai->cor = 'p';
      avo->cor = 'v';
      rotEsq(A, avo);

    }
  }

  A->sentinelaRaiz->dir->cor = 'p';
  return;
}


void balanceamentoRemocao(arvore *A, no *noX){

  no *irmao;
  no *pai = noX->pai;

  while((noX != A->sentinelaRaiz->dir) && (noX->cor == 'p'))
  {
    if(pai->esq == noX){
      irmao = pai->dir;

      if(irmao->cor == 'v') //caso 1
      {
        irmao->cor = 'p';
        pai->cor = 'v';
        rotEsq(A, pai);
        irmao = pai->dir;
      }

      if((irmao->esq->cor == 'p') && irmao->dir->cor == 'p'){

        irmao->cor = 'v';
        noX = pai;

      }else{

        if((irmao->esq->cor == 'v') && (irmao->dir->cor == 'p')){
          irmao->esq->cor = 'p';
          irmao->cor = 'v';
          rotDir(A, irmao);
          irmao = pai->dir;
        }

        irmao->cor = pai->cor;
        pai->cor = 'p';
        irmao->dir->cor = 'p';
        rotEsq(A, pai);
        noX = A->sentinelaRaiz->dir;
      }
    }else{ //nó é filho da direita
      irmao = pai->esq;

      if(irmao->cor == 'v') // caso 1
      {
        irmao->cor = 'p';
        pai->cor ='v';
        rotDir(A, pai);
        irmao = pai->esq;
      }
      if((irmao->esq->cor == 'p') && (irmao->dir->cor == 'p')){
        irmao->cor = 'v';
        noX = pai;
      }else{
        if((irmao->esq->cor == 'p') && (irmao->dir->cor == 'v')){
          irmao->dir->cor = 'p';
          irmao->cor = 'v';
          rotEsq(A, irmao);
          irmao = pai->esq;
        }
        irmao->cor = pai->cor;
        pai->cor = 'p';
        irmao->esq->cor = 'p';
        rotDir(A, pai);
        noX = A->sentinelaRaiz->dir;
      }
    }
  }
  noX->cor = 'p';
  return;
}

int profundidade(arvore *A, no *raiz) {
    if( (!A->sentinelaRaiz->dir) || (raiz->pai == NULL) || (raiz->esq == A->sentinelaFolha && raiz->dir == A->sentinelaFolha) )
        return 0;
    else
        return 1 + maior(profundidade(A, raiz->esq), profundidade(A, raiz->dir));
}

int maior(int a, int b){
    if(a > b)
        return a;
    else
        return b;
}//maior

void geraNumerosAleatorios(int qtNumeros, char nomeArquivo[]){
  int aleatorio;
  //srand(time(NULL));
  FILE *file;
  file = fopen(nomeArquivo, "w");

  for(int i=0; i<qtNumeros; i++){
    //aleatorio = i;
    aleatorio = rand()%100000 + 1;
    fprintf(file, "%d ", aleatorio);

  }
  fclose(file);
}