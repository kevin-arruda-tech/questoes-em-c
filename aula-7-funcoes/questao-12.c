/* Questão 12 – Sistema de estoque simplificado: Uma loja possui oito produtos, e cada produto tem uma
quantidade disponível em estoque. Crie um programa que armazene essas quantidades em um vetor e
implemente três funções: calcularTotalEstoque, que retorne a soma das quantidades de todos os produtos;
contarEstoqueBaixo, que retorne quantos produtos possuem menos de cinco unidades; e buscarProduto, que
receba o vetor e o código de um produto e retorne sua posição quando encontrado ou -1 caso não exista.
Considere que os produtos possuem códigos de 1 a 8 e faça a conversão adequada dos códigos para os
índices do vetor.*/

#include <stdio.h>

#define PRODUTOS 8

int calcularTotalEstoque(int estoque[], int quantidade) {
    int total = 0;
    int i;

    for (i = 0; i < quantidade; i++) {
        total += estoque[i];
    }

    return total;
}

int contarEstoqueBaixo(int estoque[], int quantidade) {
    int contador = 0;
    int i;

    for (i = 0; i < quantidade; i++) {
        if (estoque[i] < 5) {
            contador++;
        }
    }

    return contador;
}

int buscarProduto(int estoque[], int quantidade, int codigo) {
    int indice = codigo - 1;

    if (indice >= 0 && indice < quantidade) {
        return indice;
    }

    return -1;
}

int main() {
    int estoque[PRODUTOS];
    int total, baixo, codigo, posicao;
    int i;

    for (i = 0; i < PRODUTOS; i++) {
        printf("Digite a quantidade em estoque do produto %d: ", i + 1);
        scanf("%d", &estoque[i]);
    }

    total = calcularTotalEstoque(estoque, PRODUTOS);
    baixo = contarEstoqueBaixo(estoque, PRODUTOS);

    printf("\nTotal em estoque: %d unidades\n", total);
    printf("Produtos com menos de 5 unidades: %d\n", baixo);

    printf("\nDigite o código do produto que deseja buscar (1 a 8): ");
    scanf("%d", &codigo);

    posicao = buscarProduto(estoque, PRODUTOS, codigo);

    if (posicao != -1) {
        printf("Produto %d encontrado na posição %d do vetor, com %d unidades em estoque.\n",
               codigo, posicao, estoque[posicao]);
    } else {
        printf("Produto %d não encontrado.\n", codigo);
    }

    return 0;
}