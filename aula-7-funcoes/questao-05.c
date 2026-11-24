/* Questão 5 - Crie uma função chamada ehPar que receba um número 
inteiro e retorne 1 caso ele seja par ou 0 caso seja ímpar. No programa 
principal, leia um número e informe se ele é par ou ímpar utilizando o 
resultado da função. */

#include <stdio.h>

int ehPar(int numero) {
    if (numero % 2 == 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    int n;

    printf("Digite um número inteiro: ");
    scanf("%d", &n);

    if (ehPar(n) == 1) {
        printf("O número %d é par.\n", n);
    } else {
        printf("O número %d é ímpar.\n", n);
    }

    return 0;
}