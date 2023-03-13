
#ifndef BOLHA_BOLHA_H
#define BOLHA_BOLHA_H

void geraNumerosAleatorios(int qtNumeros, char nomeArquivo[]);
//Essa função gera qtNumeros números inteiros aleatórios e salva no arquivo nomeArquivo.

void carregaVetor(int vet[], int tam, char nomeArquivo[]);
//Essa função lê o arquivo gerado pela função geraNumerosAleatorios e carrega os números em um vetor;

void bolha(int vet[], int tam);
//Essa função recebe o vetor que foi carregado pela função carregaVetor e o ordena
// usando o algoritmo Bolha.

void bolhaInteligente(int vet[], int tam);
//Essa função recebe o vetor que foi carregado pela função carregaVetor e o ordena
// usando o algoritmo Bolha Inteligente.

void imprimeVetor(int vet[], int tam);
//Essa função imprime na tela os valores de um vetor de inteiros
//A saída deve ser em linha. Exemplo : 1 2 3 4 5

#endif //BOLHA_BOLHA_H