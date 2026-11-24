/* Atividade 1: Crie um algoritmo para gerenciar o estoque
de uma loja de eletrônicos. Cada item possui codigo (int),
nome (char[50]) e preco (float).
O que o algoritmo deve fazer:
a) Receber os dados de 3 produtos via teclado,
armazená-los em um vetor de struct.
b) Salvar esses dados em um arquivo de texto chamado
estoque.txt (um produto por linha).
c) Fechar o arquivo, abri-lo novamente para leitura e
exibir os produtos na tela com um layout organizado */

#include <stdio.h>
#include <stdlib.h>

#define QTD_PRODUTOS 3
#define MAX_NOME 50

typedef struct {
    int codigo;
    char nome[MAX_NOME];
    float preco;
} Produto;

int main() {
    Produto estoque[QTD_PRODUTOS];
    FILE *arquivo;

    for (int i = 0; i < QTD_PRODUTOS; i++) {
        printf("Produto %d:\n", i + 1);
        printf("Codigo: ");
        scanf("%d", &estoque[i].codigo);

        printf("Nome: ");
        scanf(" %49[^\n]", estoque[i].nome);

        printf("Preco: ");
        scanf("%f", &estoque[i].preco);
        printf("\n");
    }

    arquivo = fopen("estoque.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo estoque.txt para escrita.\n");
        return 1;
    }

    for (int i = 0; i < QTD_PRODUTOS; i++) {
        fprintf(arquivo, "%d;%s;%.2f\n", estoque[i].codigo, estoque[i].nome, estoque[i].preco);
    }

    fclose(arquivo);

    arquivo = fopen("estoque.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo estoque.txt para leitura.\n");
        return 1;
    }

    Produto lido;
    printf("============================================================\n");
    printf("%-10s | %-30s | %-12s\n", "CODIGO", "NOME DO PRODUTO", "PRECO (R$)");
    printf("============================================================\n");

    while (fscanf(arquivo, "%d;%49[^;];%f\n", &lido.codigo, lido.nome, &lido.preco) == 3) {
        printf("%-10d | %-30s | R$ %9.2f\n", lido.codigo, lido.nome, lido.preco);
    }

    printf("============================================================\n");

    fclose(arquivo);

    return 0;
}