//
// Created by vanes on 07/07/2021.
//

#include "btree.h"
#include <stdio.h>
#include <stdlib.h>

struct noB{
    int *chaves;
    struct noB **ponteiros;
    struct noB *pai;
    int ocupacao;
    int folha; // 0 não é folha; 1 é folha
};

struct arvore{
    struct noB *sentinela;
    int ordem; // representa o número de filhos que o nó pode ter
};

arvoreB * criaArvore(int ordem)
{
    arvoreB *A = (arvoreB*)malloc(sizeof(arvoreB));
    if (!A)
    {
        printf("Erro ao alocar memoria");
        return NULL;
    }
    noB *sent = NULL;
    A->ordem = ordem;
    A->sentinela = sent;
    return A;
}

noB *alocaNo(arvoreB *A, int f)
{
    noB *novoNo = (noB*)malloc(sizeof(noB));
    if (!novoNo)
    {
        printf("Erro ao alocar memoria");
        return NULL;
    }

    novoNo->chaves = (int*) calloc(A->ordem - 1, sizeof(int));
    if (!novoNo->chaves)
    {
        printf("Erro ao alocar memoria");
        return NULL;
    }

    novoNo->ponteiros = (noB**)calloc(A->ordem, sizeof(noB*));
    novoNo->ocupacao = 0;
    novoNo->folha = f;
    novoNo->pai = NULL;
    return novoNo;
}

void insereElemento(arvoreB *A, int chave)
{
    noB *aux = A->sentinela;
    int i;
    if(aux == NULL) //árvore está vazia
    {
        aux = alocaNo(A, 1);
        aux->chaves[0] = chave;
        aux->ocupacao = 1;
        A->sentinela = aux;
        aux->pai = A->sentinela;
        return;
    }
    while(aux->folha == 0) //Procurar a folha correta
    {
        i = 0;
        while ((aux->chaves[i] < chave) && (i < aux->ocupacao))
        {
            i++;
        }
        aux = aux->ponteiros[i];
    }
    i = aux->ocupacao;
    if (i < A->ordem - 1)  // A folha possui espaço para armazenar o elemento
    {
        while ((chave < aux->chaves[i - 1]) && (i > 0)) {
            aux->chaves[i] = aux->chaves[i - 1];
            i--;
        }
        aux->chaves[i] = chave;
        aux->ocupacao++;
    }
    else
    {
        split(A, aux, chave);
    }
    return;
}

void split(arvoreB *A, noB *noCheio, int chave)
{
    int meio = (A->ordem - 1)/2;
    int Vmeio = noCheio->chaves[meio];
    int i, j = 0;
    noB *irmao = alocaNo(A, noCheio->folha);
    noB *novaRaiz;
    //SPLIT DE RAIZ
    if (noCheio == A->sentinela)
    {
        novaRaiz = alocaNo(A, 0);
        //subir o elemento do meio
        novaRaiz->ocupacao = 1;
        novaRaiz->chaves[0] = Vmeio;
        A->sentinela = novaRaiz;
        novaRaiz->pai = A->sentinela;
        novaRaiz->ponteiros[0] = noCheio;
        novaRaiz->ponteiros[1] = irmao;
        noCheio->ocupacao--;
        noCheio->pai = novaRaiz;
    }
    //SPLIT DE NÓ INTERMEDIÁRIO OU FOLHA
    else
    {
        i = noCheio->pai->ocupacao;
        if (i == A->ordem-1) // não tem lugar no pai
        {
            split(A, noCheio->pai, Vmeio);
            i = 0;
            while (noCheio->pai->chaves[i] < Vmeio)
            {
                i++;
            }
            noCheio->pai->ponteiros[i+1] = irmao;
            noCheio->ocupacao--;
        }
        else
        {
            while ((i > 0) && (Vmeio < noCheio->pai->chaves[i - 1])) //encontra o lugar certo no pai
            {
                noCheio->pai->chaves[i] = noCheio->pai->chaves[i - 1];
                noCheio->pai->ponteiros[i + 1] = noCheio->pai->ponteiros[i];
                i--;
            }
            noCheio->pai->chaves[i] = Vmeio;
            noCheio->pai->ponteiros[i + 1] = irmao;
            noCheio->pai->ocupacao++;
            noCheio->ocupacao--;
        }
    }
    irmao->pai = noCheio->pai;
    //copiar os elementos maior que o meio para o irmão
    //atualizar os ponteiros
    for(i=meio+1; i<A->ordem -1; i++, j++)
    {
        irmao->chaves[j] = noCheio->chaves[i];
        irmao->ponteiros[j] = noCheio->ponteiros[i];
        if(irmao->ponteiros[j] != NULL)
            irmao->ponteiros[j]->pai = irmao;
        irmao->ocupacao++;
        noCheio->ocupacao--;
    }
    irmao->ponteiros[j] = noCheio->ponteiros[i];
    if(irmao->ponteiros[j] != NULL)
        irmao->ponteiros[j]->pai = irmao;
    //inserir a chave no local correto no noCheio ou irmão
    if(chave < Vmeio)
    {
        i = noCheio->ocupacao;
        while ((i > 0) && (chave < noCheio->chaves[i - 1])) {
            noCheio->chaves[i] = noCheio->chaves[i - 1];
            i--;
        }
        noCheio->chaves[i] = chave;
        noCheio->ponteiros[i+1] = noCheio->ponteiros[i];
        noCheio->ocupacao++;
    }
    else
    {
        i = irmao->ocupacao;
        while ((i > 0) && (chave < irmao->chaves[i - 1])) {
            irmao->chaves[i] = irmao->chaves[i - 1];
            i--;
        }
        irmao->chaves[i] = chave;
        irmao->ocupacao++;
    }
    return;
}

void removeElemento(arvoreB *A, int chave)
{
    int i = 0;
    int posPai = -1;
    int j;
    int min = (A->ordem - 1)/2;
    int achou = 0;
    noB *aux = A->sentinela;
    if (aux == NULL) //arvore está vazia
    {
        return;
    }
    while ((aux != NULL) && (achou == 0) && (i<aux->ocupacao))
    {
        if (chave == aux->chaves[i]) {
            achou = 1;
            if (posPai == -1) {
                posPai = i;
                if (i == aux->ocupacao - 1)
                    posPai++;
            }
        }
        else
        {
            if (chave < aux->chaves[i]) {
                aux = aux->ponteiros[i];
                posPai = i;
                i = 0;
            } else {
                i = i + 1;
                if ((i == aux->ocupacao) && (chave > aux->chaves[i - 1])) {
                    aux = aux->ponteiros[i];
                    posPai = i;
                    i = 0;
                }
            }
        }
    }
    if (aux == NULL)
    {
        return; //elemento não encontrado na árvore
    }
    //VERIFICAR SE O ELEMENTO É DE UM NÓ INTERMEDIÁRIO
    if (aux->folha == 0)
    {
        //ENCONTRAR O SUCESSOR E REALIZAR A CÓPIA
        noB * sucessor = aux->ponteiros[i+1];
        while (sucessor->ponteiros[0] != NULL)
            sucessor = sucessor->ponteiros[0];
        //COPIAR
        aux->chaves[i] = sucessor->chaves[0];
        aux = sucessor;
        i = 0;
    }
    //REMOVER O ELEMENTO DO NÓ
    j = aux->ocupacao - 1;
    while (i < j)
    {
        aux->chaves[i] = aux->chaves[i+1];
        i++;
    }
    aux->ocupacao--;
    //VERIFICAR SE DESBALANCEOU
    while(aux->ocupacao < min)
    {
        //CHAMAR ROTAÇÃO OU MERGE
        if ((aux != aux->pai->ponteiros[0]) && (aux->pai->ponteiros[posPai - 1]->ocupacao > min)) // pode emprestar do irmão da esquerda
        {
            rotacaoEsq(aux, posPai);
        } else {
            if ((aux != aux->pai->ponteiros[aux->pai->ocupacao])  && (aux->pai->ponteiros[posPai + 1]->ocupacao > min)) // pode emprestar do irmão da direita
            {
                rotacaoDir(aux, posPai);
            } else {
                if ((posPai != 0) && (aux->pai->ponteiros[posPai - 1] != NULL))
                {
                    posPai--;
                    merge(A, aux->pai->ponteiros[posPai], aux, posPai);
                }
                else
                    merge(A, aux, aux->pai->ponteiros[posPai + 1], posPai);
                aux = aux->pai;
                if (aux == A->sentinela)
                    return;
                //Caso contrário, encontra nova posição no pai
                posPai = 0;
                while ((posPai < aux->pai->ocupacao) && (chave > aux->pai->chaves[posPai]))
                    posPai++;
            }
        }
    }
    return;
}

void rotacaoEsq(noB * noRem, int pos)
{
    noB * irmao = noRem->pai->ponteiros[pos-1];
    int ocpNoRem = noRem->ocupacao;
    int ocpNoIrmao = irmao->ocupacao;
    int i = ocpNoRem;

    while(i > 0)
    {
        noRem->chaves[i] = noRem->chaves[i-1];
        noRem->ponteiros[i+1] = noRem->ponteiros[i];
        i--;
    }
    noRem->ponteiros[i+1] = noRem->ponteiros[i];
    noRem->chaves[i] = noRem->pai->chaves[pos - 1];
    noRem->ocupacao++;
    noRem->pai->chaves[pos - 1] = irmao->chaves[ocpNoIrmao-1];
    noRem->ponteiros[0] = irmao->ponteiros[ocpNoIrmao];
    if (noRem->ponteiros[0] != NULL)
        noRem->ponteiros[0]->pai = noRem;
    irmao->ocupacao--;
    return;
}

void rotacaoDir(noB * noRem, int pos)
{
    noB * irmao = noRem->pai->ponteiros[pos+1];
    int ocpNoIrmao = irmao->ocupacao;
    int i = 0;
    noRem->chaves[noRem->ocupacao] = noRem->pai->chaves[pos];
    noRem->ocupacao++;
    noRem->pai->chaves[pos] = irmao->chaves[0];
    noRem->ponteiros[noRem->ocupacao] = irmao->ponteiros[0];
    if(!noRem->folha)
        noRem->ponteiros[noRem->ocupacao]->pai = noRem;
    while (i < ocpNoIrmao - 1)
    {
        irmao->chaves[i] = irmao->chaves[i + 1];
        irmao->ponteiros[i] = irmao->ponteiros[i+1];
        i++;
    }
    irmao->ponteiros[i] = irmao->ponteiros[i+1];
    irmao->ocupacao--;
    return;
}

void merge(arvoreB *A, noB * noEsq, noB * noDir, int pos)
{
    int i = noEsq->ocupacao;
    int j;
    noB *pai = noEsq->pai;
    //UNIR OS DADOS NO noEsq
    noEsq->chaves[i] = pai->chaves[pos];
    noEsq->ocupacao++;
    pai->ocupacao--;
    i++;
    for (j=0; j < noDir->ocupacao; j++)
    {
        noEsq->chaves[i] = noDir->chaves[j];
        noEsq->ponteiros[i] = noDir->ponteiros[j];
        if(noEsq->ponteiros[i] != NULL)
            noEsq->ponteiros[i]->pai = noEsq;
        noEsq->ocupacao++;
        i++;
    }
    noEsq->ponteiros[i] = noDir->ponteiros[j];
    if(noEsq->ponteiros[i] != NULL)
        noEsq->ponteiros[i]->pai = noEsq;
    if ((pai->ocupacao == 0) && (pai == A->sentinela))
    {
        A->sentinela = noEsq;
        noEsq->pai = A->sentinela;
        free(pai);
        free(noDir);
        return;
    }
    //SHIFT NOS DADOS DO PAI
    for (i = pos; i < noEsq->pai->ocupacao; i++)
    {
        noEsq->pai->chaves[i] = noEsq->pai->chaves[i + 1];
        noEsq->pai->ponteiros[i+1] = noEsq->pai->ponteiros[i + 2];
    }
    free(noDir);
    return;
}

void imprimeArvore(noB *raiz)
{
    int i;
    if (raiz == NULL)
        return;
    for (i = 0; i < raiz->ocupacao; i++)
    {
        printf("%d - %d\t", raiz->chaves[i], raiz->pai->chaves[0]);
    }
    printf("\n");
    i = 0;
    while (i <= raiz->ocupacao)
    {
        imprimeArvore(raiz->ponteiros[i]);
        i++;
    }
}


noB* retornaRaiz(arvoreB *A)
{
    return A->sentinela;
}