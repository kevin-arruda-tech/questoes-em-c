/* Questão 3 - Desenvolva uma função chamada maiorNumero que receba dois 
números inteiros e retorne o maior
deles. Caso os números sejam iguais, 
a função deverá retornar qualquer um dos valores */ 

#include <stdio.h>

int maiorNumero(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b; 
    }
}

int main() {
    int x, y, maior;

    printf("Digite o primeiro número: ");
    scanf("%d", &x);

    printf("Digite o segundo número: ");
    scanf("%d", &y);

    maior = maiorNumero(x, y);

    printf("O maior número é: %d\n", maior);

    return 0;
}