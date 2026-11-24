/* Questão 9 - Crie uma função chamada mostrarTabuada que receba um número inteiro 
e exiba sua tabuada de 1a 10. No programa principal, leia o número informado pelo 
usuário e chame a função para apresentar a
tabuada completa.*/

#include <stdio.h>

void mostrarTabuada(int numero) {
    int i;

    for (i = 1; i <= 10; i++) {
        printf("%d x %d = %d\n", numero, i, numero * i);
    }
}

int main() {
    int n;

    printf("Digite um número inteiro: ");
    scanf("%d", &n);

    mostrarTabuada(n);

    return 0;
}