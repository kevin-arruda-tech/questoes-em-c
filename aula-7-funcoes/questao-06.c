/* Questão 6 - Desenvolva uma calculadora que realize as quatro operações 
matemáticas básicas: adição,subtração, multiplicação e divisão. 
Implemente uma função para cada operação, recebendo dois números como
parâmetros e retornando o resultado. O programa deverá ler dois números 
e uma opção de operação, chamar afunção correspondente e exibir o resultado. 
Na divisão, verifique se o divisor é diferente de zero antes de realizar a
operação */

#include <stdio.h>

float somar(float a, float b) {
    return a + b;
}

float subtrair(float a, float b) {
    return a - b;
}

float multiplicar(float a, float b) {
    return a * b;
}

float dividir(float a, float b) {
    return a / b;
}

int main() {
    float num1, num2;
    int opcao;

    printf("Digite o primeiro número: ");
    scanf("%f", &num1);

    printf("Digite o segundo número: ");
    scanf("%f", &num2);

    printf("\nEscolha a operação:\n");
    printf("1 - Adição\n");
    printf("2 - Subtração\n");
    printf("3 - Multiplicação\n");
    printf("4 - Divisão\n");
    printf("Opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            printf("Resultado: %.2f\n", somar(num1, num2));
            break;
        case 2:
            printf("Resultado: %.2f\n", subtrair(num1, num2));
            break;
        case 3:
            printf("Resultado: %.2f\n", multiplicar(num1, num2));
            break;
        case 4:
            if (num2 != 0) {
                printf("Resultado: %.2f\n", dividir(num1, num2));
            } else {
                printf("Erro: não é possível dividir por zero.\n");
            }
            break;
        default:
            printf("Opção inválida.\n");
    }

    return 0;
}