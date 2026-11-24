/* 3. Desenvolva um algoritmo em linguagem C que leia 15 números inteiros e armazene-os em um vetor.
a) Em seguida, o programa deverá identificar quais números aparecem mais de uma vez e contar a
quantidade de ocorrências de cada um.
b) Para os números que forem primos e apresentarem quantidade ímpar de ocorrências, o programa deverá
calcular a soma de todas as ocorrências daquele número e solicitar ao usuário o cadastro de nomes de
animais correspondentes a essa soma.
c) Já para os números que apresentarem quantidade par de ocorrências, o programa deverá utilizar a posição
que ocupam no vetor para estabelecer uma correspondência com os nomes dos animais previamente
cadastrados pelo usuário.
d) Ao final, o programa deverá apresentar os nomes dos animais correspondentes às regras identificadas
durante o processamento.
a) Exemplo de saída: (deveria ter um imagem aqui, mas eu não tenho como fazer upload dela no código) */

#include <stdio.h>

#define TAM 15
#define MAX_ANIMAIS 30
#define TAM_NOME 30

int ehPrimo(int numero) {
    int i;

    if (numero < 2) {
        return 0;
    }

    for (i = 2; i * i <= numero; i++) {
        if (numero % i == 0) {
            return 0;
        }
    }

    return 1;
}

int contarOcorrencias(int vetor[], int tamanho, int distintos[], int contagem[], int primeiraPos[]) {
    int n = 0;
    int i, j, achou;

    for (i = 0; i < tamanho; i++) {
        achou = 0;

        for (j = 0; j < n; j++) {
            if (distintos[j] == vetor[i]) {
                contagem[j]++;
                achou = 1;
                break;
            }
        }

        if (!achou) {
            distintos[n] = vetor[i];
            contagem[n] = 1;
            primeiraPos[n] = i + 1;
            n++;
        }
    }

    return n;
}

void exibirAnimal(int indice, char animais[][TAM_NOME], int qtdAnimais, int *contador) {
    (*contador)++;

    if (indice >= 1 && indice <= qtdAnimais) {
        printf("%d. %s.\n", *contador, animais[indice - 1]);
    } else {
        printf("%d. Não existe correspondência.\n", *contador);
    }
}

int main() {
    int numeros[TAM];
    int distintos[TAM], contagem[TAM], primeiraPos[TAM];
    char animais[MAX_ANIMAIS][TAM_NOME];
    int qtdDistintos, qtdAnimais;
    int soma, contador = 0;
    int i;

    for (i = 0; i < TAM; i++) {
        printf("Digite o número %d: ", i + 1);
        scanf("%d", &numeros[i]);
    }

    qtdDistintos = contarOcorrencias(numeros, TAM, distintos, contagem, primeiraPos);

    printf("\nNúmero | Ocorrências | Classificação\n");
    for (i = 0; i < qtdDistintos; i++) {
        printf("%6d | %11d | ", distintos[i], contagem[i]);

        if (contagem[i] == 1) {
            printf("Não repetido\n");
        } else if (ehPrimo(distintos[i]) && contagem[i] % 2 != 0) {
            printf("Primo - ímpar\n");
        } else if (ehPrimo(distintos[i]) && contagem[i] % 2 == 0) {
            printf("Primo - par\n");
        } else if (contagem[i] % 2 == 0) {
            printf("Par\n");
        } else {
            printf("Ímpar\n");
        }
    }

    do {
        printf("\nQuantos animais deseja cadastrar (1 a %d)? ", MAX_ANIMAIS);
        scanf("%d", &qtdAnimais);
    } while (qtdAnimais < 1 || qtdAnimais > MAX_ANIMAIS);

    for (i = 0; i < qtdAnimais; i++) {
        printf("Nome do animal %d: ", i + 1);
        scanf(" %29[^\n]", animais[i]);
    }

    printf("\nAnimais cadastrados:\n");
    for (i = 0; i < qtdAnimais; i++) {
        printf("%d. %s\n", i + 1, animais[i]);
    }

    printf("\nSaída:\n");
    for (i = 0; i < qtdDistintos; i++) {
        if (contagem[i] > 1) {
            if (ehPrimo(distintos[i]) && contagem[i] % 2 != 0) {
                soma = distintos[i] * contagem[i];
                exibirAnimal(soma, animais, qtdAnimais, &contador);
            } else if (contagem[i] % 2 == 0) {
                exibirAnimal(primeiraPos[i], animais, qtdAnimais, &contador);
            }
        }
    }

    if (contador == 0) {
        printf("Nenhuma regra foi aplicada.\n");
    }

    return 0;
}