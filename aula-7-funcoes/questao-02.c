/* Questão 2 - Crie uma função chamada calcularDobro que receba um número inteiro como parâmetro e retorne o
seu dobro. No programa principal, leia um número, chame a função e exiba o resultado. */

#include <stdio.h>

int calcularDobro(int numero) {
    return numero * 2;
}

int main() {
    int n, resultado;

    printf("Digite um número inteiro: ");
    scanf("%d", &n);

    resultado = calcularDobro(n);

    printf("O dobro de %d é %d\n", n, resultado);

    return 0;
}
