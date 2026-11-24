/* Questão 7 - Crie uma função chamada calcularMedia que receba 
três notas e retorne a média aritmética.Em seguida, crie uma 
função chamada verificarSituacao que receba a média e exiba 
a situação do aluno,considerando aprovado quem obtiver média 
maior ou igual a 7,0 e reprovado quem obtiver média inferior 
a 7,0. No programa principal, leia as três notas, calcule a 
média e apresente a situação do aluno.*/

#include <stdio.h>

float calcularMedia(float n1, float n2, float n3) {
    return (n1 + n2 + n3) / 3;
}

void verificarSituacao(float media) {
    if (media >= 7.0) {
        printf("Situação: Aprovado\n");
    } else {
        printf("Situação: Reprovado\n");
    }
}

int main() {
    float nota1, nota2, nota3, media;

    printf("Digite a primeira nota: ");
    scanf("%f", &nota1);

    printf("Digite a segunda nota: ");
    scanf("%f", &nota2);

    printf("Digite a terceira nota: ");
    scanf("%f", &nota3);

    media = calcularMedia(nota1, nota2, nota3);

    printf("Média: %.2f\n", media);
    verificarSituacao(media);

    return 0;
}