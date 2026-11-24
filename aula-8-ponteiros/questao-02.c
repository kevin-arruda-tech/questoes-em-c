/* 2. Desenvolva um algoritmo em linguagem C que leia 10 valores inteiros e identifique quais são positivos e
pares e quais são negativos e ímpares. Os valores que atenderem a cada uma dessas condições deverão ser
armazenados em vetores distintos. Ao final, o programa deverá apresentar os dois conjuntos de valores,
organizados em ordem crescente.*/

#include <stdio.h>

#define TAM 10

void ordenarCrescente(int vetor[], int tamanho) {
    int i, j, aux;

    for (i = 0; i < tamanho - 1; i++) {
        for (j = 0; j < tamanho - 1 - i; j++) {
            if (vetor[j] > vetor[j + 1]) {
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

void exibirVetor(int vetor[], int tamanho) {
    int i;

    if (tamanho == 0) {
        printf("Nenhum valor.\n");
        return;
    }

    for (i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

int main() {
    int valores[TAM];
    int positivosPares[TAM], negativosImpares[TAM];
    int qtdPP = 0, qtdNI = 0;
    int i;

    for (i = 0; i < TAM; i++) {
        printf("Digite o valor %d: ", i + 1);
        scanf("%d", &valores[i]);

        if (valores[i] > 0 && valores[i] % 2 == 0) {
            positivosPares[qtdPP] = valores[i];
            qtdPP++;
        } else if (valores[i] < 0 && valores[i] % 2 != 0) {
            negativosImpares[qtdNI] = valores[i];
            qtdNI++;
        }
    }

    ordenarCrescente(positivosPares, qtdPP);
    ordenarCrescente(negativosImpares, qtdNI);

    printf("\nPositivos e pares (ordem crescente):\n");
    exibirVetor(positivosPares, qtdPP);

    printf("\nNegativos e ímpares (ordem crescente):\n");
    exibirVetor(negativosImpares, qtdNI);

    return 0;
}