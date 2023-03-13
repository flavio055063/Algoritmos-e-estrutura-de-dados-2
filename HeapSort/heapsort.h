// AQUIVO .H
// HEAPSORT

void geraNumerosAleatorios(int qtNumeros, char nomeArquivo[]);
//Essa função gera qtNumeros números inteiros aleatórios e salva no arquivo nomeArquivo.

void carregaVetor(int vet[], int tam, char nomeArquivo[]);
//Essa função lê o arquivo gerado pela função geraNumerosAleatorios e carrega os números em um vetor;

void imprimeVetor(int vet[], int tam);
//Essa função imprime na tela os valores de um vetor de inteiros
//A saída deve ser em linha. Exemplo : 1 2 3 4 5

void heapSort(int vet[], int tam);
//Função principal do heapSort

void heap(int vet[], int tam, int i);
//Função secundária do heapSort

void mergeSort(int vet[], int inicio, int fim);
//Função mergesort que divide recursivamente o vetor e chama a função merge.

void merge(int vet[], int inicio, int meio, int fim);
//Função que une vetores previamente ordenados em um vetor auxiliar.
//Ao final copia o vetor auxiliar para o vetor original
