/* 1. Uma equipe está organizando um sorteio beneficente e precisa analisar os números registrados durante o
planejamento da compra dos produtos. Para isso, desenvolva um algoritmo em linguagem C que leia 12
números inteiros e armazene-os em um vetor. Em seguida, o programa deverá:
a) Contar quantas vezes cada número aparece no vetor.
b) Os números cuja quantidade de ocorrências for ímpar representarão as quantidades de produtos que
deverão ser comprados para o sorteio beneficente.
c) Os números cuja quantidade de ocorrências for par deverão ser armazenados em um segundo vetor, que
deverá ser organizado em ordem decrescente.
d) Para cada número cuja quantidade de ocorrências for ímpar, o programa deverá solicitar o cadastro dos
produtos que serão comprados, informando o nome e o preço unitário de cada produto.
e) Após o cadastro, os produtos deverão ser apresentados em ordem alfabética pelo nome. Ao final, o
programa deverá apresentar:
a) Os 12 números informados pelo usuário.
b) Cada número distinto e a quantidade de vezes que aparece no vetor.
c) Os produtos cadastrados para compra, com seus respectivos nomes e preços, organizados em ordem
alfabética.
d) Os números cuja quantidade de ocorrências seja par, armazenados em um segundo vetor e apresentados
em ordem decrescente.*/

#include <stdio.h>
#include <string.h>

#define TAM 12

typedef struct {
    char nome[50];
    float preco;
    int quantidade;
} Produto;

int contarOcorrencias(int vetor[], int tamanho, int distintos[], int contagem[]) {
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
            n++;
        }
    }

    return n;
}

void ordenarDecrescente(int vetor[], int tamanho) {
    int i, j, aux;

    for (i = 0; i < tamanho - 1; i++) {
        for (j = 0; j < tamanho - 1 - i; j++) {
            if (vetor[j] < vetor[j + 1]) {
                aux = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = aux;
            }
        }
    }
}

void ordenarProdutos(Produto produtos[], int tamanho) {
    int i, j;
    Produto aux;

    for (i = 0; i < tamanho - 1; i++) {
        for (j = 0; j < tamanho - 1 - i; j++) {
            if (strcmp(produtos[j].nome, produtos[j + 1].nome) > 0) {
                aux = produtos[j];
                produtos[j] = produtos[j + 1];
                produtos[j + 1] = aux;
            }
        }
    }
}

int main() {
    int numeros[TAM];
    int distintos[TAM], contagem[TAM];
    int pares[TAM];
    Produto produtos[TAM];
    int qtdDistintos, qtdPares = 0, qtdProdutos = 0;
    int i;

    for (i = 0; i < TAM; i++) {
        printf("Digite o número %d: ", i + 1);
        scanf("%d", &numeros[i]);
    }

    qtdDistintos = contarOcorrencias(numeros, TAM, distintos, contagem);

    for (i = 0; i < qtdDistintos; i++) {
        if (contagem[i] % 2 == 0) {
            pares[qtdPares] = distintos[i];
            qtdPares++;
        } else {
            printf("\nCadastro do produto para o número %d (quantidade a comprar: %d)\n",
                   distintos[i], distintos[i]);
            printf("Nome do produto: ");
            scanf(" %49[^\n]", produtos[qtdProdutos].nome);
            printf("Preço unitário: R$ ");
            scanf("%f", &produtos[qtdProdutos].preco);
            produtos[qtdProdutos].quantidade = distintos[i];
            qtdProdutos++;
        }
    }

    ordenarProdutos(produtos, qtdProdutos);
    ordenarDecrescente(pares, qtdPares);

    printf("\n===== RESULTADOS =====\n");

    printf("\nNúmeros informados:\n");
    for (i = 0; i < TAM; i++) {
        printf("%d ", numeros[i]);
    }
    printf("\n");

    printf("\nOcorrências de cada número:\n");
    for (i = 0; i < qtdDistintos; i++) {
        printf("Número %d: %d vez(es)\n", distintos[i], contagem[i]);
    }

    printf("\nProdutos para compra (ordem alfabética):\n");
    if (qtdProdutos == 0) {
        printf("Nenhum produto cadastrado.\n");
    }
    for (i = 0; i < qtdProdutos; i++) {
        printf("%s - Quantidade: %d - Preço unitário: R$ %.2f\n",
               produtos[i].nome, produtos[i].quantidade, produtos[i].preco);
    }

    printf("\nNúmeros com ocorrência par (ordem decrescente):\n");
    if (qtdPares == 0) {
        printf("Nenhum número com ocorrência par.\n");
    }
    for (i = 0; i < qtdPares; i++) {
        printf("%d ", pares[i]);
    }
    printf("\n");

    return 0;
}