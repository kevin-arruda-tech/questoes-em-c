/* Questão 10 - Uma loja deseja analisar as vendas realizadas durante cinco dias. 
Crie um programa que leia os valores das vendas e implemente três funções: calcularTotal, 
que receba os valores e retorne a soma das vendas; calcularMedia, que receba o total e a 
quantidade de dias e retorne a média diária; e contarVendasAcimaDaMedia, que receba os valores 
das vendas e a média e retorne quantos dias tiveram vendas acima da média. Ao final, apresente 
o total vendido, a média diária e a quantidade de dias acima da média.*/

#include <stdio.h>

#define DIAS 5

float calcularTotal(float vendas[], int quantidade) {
    float total = 0;
    int i;

    for (i = 0; i < quantidade; i++) {
        total += vendas[i];
    }

    return total;
}

float calcularMedia(float total, int quantidade) {
    return total / quantidade;
}

int contarVendasAcimaDaMedia(float vendas[], int quantidade, float media) {
    int contador = 0;
    int i;

    for (i = 0; i < quantidade; i++) {
        if (vendas[i] > media) {
            contador++;
        }
    }

    return contador;
}

int main() {
    float vendas[DIAS];
    float total, media;
    int acimaDaMedia;
    int i;

    for (i = 0; i < DIAS; i++) {
        printf("Digite o valor das vendas do dia %d: ", i + 1);
        scanf("%f", &vendas[i]);
    }

    total = calcularTotal(vendas, DIAS);
    media = calcularMedia(total, DIAS);
    acimaDaMedia = contarVendasAcimaDaMedia(vendas, DIAS, media);

    printf("\nTotal vendido: R$ %.2f\n", total);
    printf("Média diária: R$ %.2f\n", media);
    printf("Dias com vendas acima da média: %d\n", acimaDaMedia);

    return 0;
}