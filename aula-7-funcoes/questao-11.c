/* Questão 11 – Análise de notas de uma turma: Uma turma possui 10 alunos, e o professor 
deseja analisar suas notas finais. Desenvolva um programa que armazene as notas em um 
vetor e implemente as seguintes funções:calcularMediaTurma, que retorne a média das notas; 
encontrarMaiorNota, que retorne a maior nota registrada; contarAprovados, que retorne a quantidade 
de alunos com nota maior ou igual a 7,0; e exibirResultados, que apresente os resultados calculados. 
As funções responsáveis pelos cálculos devem retornar os valores, sem
imprimir diretamente os resultados. */

#include <stdio.h>

#define ALUNOS 10

float calcularMediaTurma(float notas[], int quantidade) {
    float soma = 0;
    int i;

    for (i = 0; i < quantidade; i++) {
        soma += notas[i];
    }

    return soma / quantidade;
}

float encontrarMaiorNota(float notas[], int quantidade) {
    float maior = notas[0];
    int i;

    for (i = 1; i < quantidade; i++) {
        if (notas[i] > maior) {
            maior = notas[i];
        }
    }

    return maior;
}

int contarAprovados(float notas[], int quantidade) {
    int aprovados = 0;
    int i;

    for (i = 0; i < quantidade; i++) {
        if (notas[i] >= 7.0) {
            aprovados++;
        }
    }

    return aprovados;
}

void exibirResultados(float media, float maiorNota, int aprovados) {
    printf("\n--- Resultados da turma ---\n");
    printf("Média da turma: %.2f\n", media);
    printf("Maior nota: %.2f\n", maiorNota);
    printf("Alunos aprovados: %d\n", aprovados);
}

int main() {
    float notas[ALUNOS];
    float media, maiorNota;
    int aprovados;
    int i;

    for (i = 0; i < ALUNOS; i++) {
        printf("Digite a nota do aluno %d: ", i + 1);
        scanf("%f", &notas[i]);
    }

    media = calcularMediaTurma(notas, ALUNOS);
    maiorNota = encontrarMaiorNota(notas, ALUNOS);
    aprovados = contarAprovados(notas, ALUNOS);

    exibirResultados(media, maiorNota, aprovados);

    return 0;
}