#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

void knapsack(int pesos[], int valores[], int n, int capacidade) {
    int i, w;
    int memoization[n + 1][capacidade + 1];

    for (i = 0; i <= n; i++) {
        for (w = 0; w <= capacidade; w++) {
            if (i == 0 || w == 0) {
                memoization[i][w] = 0;
            } else if (pesos[i - 1] <= w) {
                memoization[i][w] = max(valores[i - 1] + memoization[i - 1][w - pesos[i - 1]], memoization[i - 1][w]);
            } else {
                memoization[i][w] = memoization[i - 1][w];
            }
        }
    }

    printf("Valor máximo: %d\n", memoization[n][capacidade]);
    printf("Itens selecionados: ");

    w = capacidade;
    for (i = n; i > 0 && memoization[i][w] != 0; i--) {
        if (memoization[i][w] != memoization[i - 1][w]) {
            printf("%d ", i - 1);
            w -= pesos[i - 1];
        }
    }

    printf("\n");
}

int main() {
    int pesos[] = {2, 3, 4, 5};
    int valores[] = {3, 4, 5, 6};
    int capacidade = 7;
    int n = sizeof(pesos) / sizeof(pesos[0]);

    knapsack(pesos, valores, n, capacidade);

    return 0;
}
