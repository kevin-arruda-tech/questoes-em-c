/* Questão 8 - Crie uma função chamada ehPrimo que receba um número 
inteiro e retorne 1 caso ele seja primo ou 0 caso contrário. O 
programa principal deverá solicitar um número e informar o resultado. 
Considere quenúmeros menores que 2 não são primos. Como desafio adicional, 
implemente a verificação testando os divisores somente até a raiz quadrada 
do número, sem utilizar a função sqrt().*/

#include <stdio.h>

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

int main() {
    int n;

    printf("Digite um número inteiro: ");
    scanf("%d", &n);

    if (ehPrimo(n)) {
        printf("O número %d é primo.\n", n);
    } else {
        printf("O número %d não é primo.\n", n);
    }

    return 0;
}