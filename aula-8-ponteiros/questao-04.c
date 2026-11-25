/* 4. Cinco apostadores desejam tentar a sorte em uma competição que premiará os três melhores resultados. Para participar, cada apostador
deverá informar seu nome e um valor inteiro positivo.
a) Desenvolva um algoritmo em linguagem C que receba os dados dos cinco apostadores e calcule a soma da sequência de Fibonacci
correspondente ao valor informado por cada participante.
b) Após calcular os resultados, o programa deverá determinar os três vencedores, obedecendo aos seguintes critérios:
c) 1º lugar – Maior número primo: será premiado o apostador que obtiver o maior resultado primo entre os cinco participantes.
d) 2º lugar – Maior número par: será premiado o apostador que obtiver o maior resultado par entre os participantes que ainda não
receberam premiação.
e) 3º lugar – Maior resultado acima da média: será premiado o apostador que apresentar o maior resultado acima da média dos cinco
participantes, desde que ainda não tenha recebido outra premiação.
f) Requisitos do algoritmo
a) Cadastre o nome dos cinco apostadores e solicite um número inteiro positivo para cada um.
b) Desenvolva uma função para calcular a soma dos termos da sequência de Fibonacci até a quantidade de termos indicada pelo
apostador.
c) Armazene os resultados calculados em um vetor.
d) Desenvolva uma função para verificar se determinado resultado é primo.
e) Identifique o maior resultado primo e atribua o primeiro lugar.
f) Identifique o maior resultado par entre os apostadores que ainda não foram premiados e atribua o segundo lugar.
g) Calcule a média dos cinco resultados e identifique o maior resultado acima dela, considerando apenas os participantes ainda
não premiados, para atribuir o terceiro lugar.
h) Garanta que nenhum apostador receba mais de uma premiação.
i) Caso não exista participante que atenda a algum critério, o respectivo prêmio deverá ficar sem vencedor.
j) Ao final, apresente somente os nomes dos apostadores vencedores e suas respectivas colocações, em ordem decrescente de
classificação.*/

#include <stdio.h>

#define QTD_APOSTADORES 5
#define TAM_NOME 100

long long soma_fibonacci(int n) {
    if (n <= 0) {
        return 0;
    }
    long long a = 0, b = 1, prox;
    long long soma = 0;
    for (int i = 1; i <= n; i++) {
        soma += a;
        prox = a + b;
        a = b;
        b = prox;
    }
    return soma;
}

int eh_primo(long long num) {
    if (num <= 1) {
        return 0;
    }
    if (num == 2) {
        return 1;
    }
    if (num % 2 == 0) {
        return 0;
    }
    for (long long i = 3; i * i <= num; i += 2) {
        if (num % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    char nomes[QTD_APOSTADORES][TAM_NOME];
    int valores[QTD_APOSTADORES];
    long long resultados[QTD_APOSTADORES];
    int premiado[QTD_APOSTADORES] = {0};

    for (int i = 0; i < QTD_APOSTADORES; i++) {
        printf("Digite o nome do apostador %d: ", i + 1);
        scanf(" %99[^\n]", nomes[i]);

        do {
            printf("Digite um valor inteiro positivo para %s: ", nomes[i]);
            scanf("%d", &valores[i]);
        } while (valores[i] <= 0);

        resultados[i] = soma_fibonacci(valores[i]);
    }

    int idx_primeiro = -1;
    long long maior_primo = 0;
    for (int i = 0; i < QTD_APOSTADORES; i++) {
        if (!premiado[i] && eh_primo(resultados[i])) {
            if (idx_primeiro == -1 || resultados[i] > maior_primo) {
                maior_primo = resultados[i];
                idx_primeiro = i;
            }
        }
    }
    if (idx_primeiro != -1) {
        premiado[idx_primeiro] = 1;
    }

    int idx_segundo = -1;
    long long maior_par = 0;
    for (int i = 0; i < QTD_APOSTADORES; i++) {
        if (!premiado[i] && resultados[i] % 2 == 0) {
            if (idx_segundo == -1 || resultados[i] > maior_par) {
                maior_par = resultados[i];
                idx_segundo = i;
            }
        }
    }
    if (idx_segundo != -1) {
        premiado[idx_segundo] = 1;
    }

    long long soma_total = 0;
    for (int i = 0; i < QTD_APOSTADORES; i++) {
        soma_total += resultados[i];
    }
    double media = (double)soma_total / QTD_APOSTADORES;

    int idx_terceiro = -1;
    long long maior_acima_media = 0;
    for (int i = 0; i < QTD_APOSTADORES; i++) {
        if (!premiado[i] && (double)resultados[i] > media) {
            if (idx_terceiro == -1 || resultados[i] > maior_acima_media) {
                maior_acima_media = resultados[i];
                idx_terceiro = i;
            }
        }
    }
    if (idx_terceiro != -1) {
        premiado[idx_terceiro] = 1;
    }

    if (idx_terceiro != -1) {
        printf("3o lugar: %s\n", nomes[idx_terceiro]);
    } else {
        printf("3o lugar: Sem vencedor\n");
    }

    if (idx_segundo != -1) {
        printf("2o lugar: %s\n", nomes[idx_segundo]);
    } else {
        printf("2o lugar: Sem vencedor\n");
    }

    if (idx_primeiro != -1) {
        printf("1o lugar: %s\n", nomes[idx_primeiro]);
    } else {
        printf("1o lugar: Sem vencedor\n");
    }

    return 0;
}
