#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
    char nomeItem[100];
    int peso;
    int valor;
} Item;


int max(int a, int b) {
    return (a > b) ? a : b;
}

void knapsack(Item itens[], int quantidadeItens, int capacidade) {
    int i, w;
    int memoization[quantidadeItens + 1][capacidade + 1];

    for (i = 0; i <= quantidadeItens; i++) {
        for (w = 0; w <= capacidade; w++) {
            if (i == 0 || w == 0) {
                memoization[i][w] = 0;
            } else if (itens[i - 1].peso <= w) {
                memoization[i][w] = max(itens[i - 1].valor + memoization[i - 1][w - itens[i - 1].peso], memoization[i - 1][w]);
            } else {
                memoization[i][w] = memoization[i - 1][w];
            }
        }
    }

    printf("Valor máximo: %d\n", memoization[quantidadeItens][capacidade]);
    printf("Itens selecionados: \n");

    w = capacidade;
    for (i = quantidadeItens; i > 0 && memoization[i][w] != 0; i--) {
        if (memoization[i][w] != memoization[i - 1][w]) {
            printf("%s \n", itens[i - 1].nomeItem);
            w -= itens[i - 1].peso;
        }
    }

    printf("\n");
}

int main() {

    FILE *inputFile;
    char inputFilename[] = "itens.csv";

    Item itens[100];
    char line[100];
    int quantidadeItens = 0;

    inputFile = fopen(inputFilename, "r");
    if (inputFile == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    // Lê os dados do arquivo de entrada
    while (fgets(line, sizeof(line), inputFile)) {
        char *token = strtok(line, ",");
        strncpy(itens[quantidadeItens].nomeItem, token, sizeof(itens[quantidadeItens].nomeItem));
        token = strtok(NULL, ",");
        itens[quantidadeItens].peso = atoi(token);
        token = strtok(NULL, ",");
        itens[quantidadeItens].valor = atoi(token);
        quantidadeItens++;
    }

    fclose(inputFile);

    int peso[] = {2, 3, 4, 5};
    int valor[] = {3, 4, 5, 6};
    int capacidade = 30;
    int n = sizeof(peso) / sizeof(peso[0]);

    knapsack(itens, quantidadeItens, capacidade);

    return 0;
}