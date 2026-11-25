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

#define QUANTIDADE_APOSTADORES 5
#define TAMANHO_NOME 100

long long calcular_soma_fibonacci(int quantidade_termos) {
    if (quantidade_termos <= 0) {
        return 0;
    }

    long long termo_atual = 0;
    long long proximo_termo = 1;
    long long guarda_soma = 0;
    long long soma_fibonacci = 0;

    for (int indice = 1; indice <= quantidade_termos; indice++) {
        soma_fibonacci += termo_atual;
        guarda_soma = termo_atual + proximo_termo;
        termo_atual = proximo_termo;
        proximo_termo = guarda_soma;
    }

    return soma_fibonacci;
}

int verificar_numero_primo(long long numero) {
    if (numero <= 1) {
        return 0;
    }
    if (numero == 2) {
        return 1;
    }
    if (numero % 2 == 0) {
        return 0;
    }

    for (long long divisor = 3; divisor * divisor <= numero; divisor += 2) {
        if (numero % divisor == 0) {
            return 0;
        }
    }

    return 1;
}

int main(void) {
    char nomes_apostadores[QUANTIDADE_APOSTADORES][TAMANHO_NOME];
    int valores_informados[QUANTIDADE_APOSTADORES];
    long long resultados_fibonacci[QUANTIDADE_APOSTADORES];
    int apostador_premiado[QUANTIDADE_APOSTADORES] = {0};

    for (int indice = 0; indice < QUANTIDADE_APOSTADORES; indice++) {
        printf("Digite o nome do apostador %d: ", indice + 1);
        scanf(" %99[^\n]", nomes_apostadores[indice]);

        do {
            printf("Digite um valor inteiro positivo para %s: ", nomes_apostadores[indice]);
            scanf("%d", &valores_informados[indice]);
        } while (valores_informados[indice] <= 0);

        resultados_fibonacci[indice] = calcular_soma_fibonacci(valores_informados[indice]);
    }

    int indice_primeiro_lugar = -1;
    long long maior_resultado_primo = 0;

    for (int indice = 0; indice < QUANTIDADE_APOSTADORES; indice++) {
        if (!apostador_premiado[indice] && verificar_numero_primo(resultados_fibonacci[indice])) {
            if (indice_primeiro_lugar == -1 || resultados_fibonacci[indice] > maior_resultado_primo) {
                maior_resultado_primo = resultados_fibonacci[indice];
                indice_primeiro_lugar = indice;
            }
        }
    }

    if (indice_primeiro_lugar != -1) {
        apostador_premiado[indice_primeiro_lugar] = 1;
    }

    int indice_segundo_lugar = -1;
    long long maior_resultado_par = 0;

    for (int indice = 0; indice < QUANTIDADE_APOSTADORES; indice++) {
        if (!apostador_premiado[indice] && resultados_fibonacci[indice] % 2 == 0) {
            if (indice_segundo_lugar == -1 || resultados_fibonacci[indice] > maior_resultado_par) {
                maior_resultado_par = resultados_fibonacci[indice];
                indice_segundo_lugar = indice;
            }
        }
    }

    if (indice_segundo_lugar != -1) {
        apostador_premiado[indice_segundo_lugar] = 1;
    }

    long long soma_total_resultados = 0;
    for (int indice = 0; indice < QUANTIDADE_APOSTADORES; indice++) {
        soma_total_resultados += resultados_fibonacci[indice];
    }

    double media_resultados = (double)soma_total_resultados / QUANTIDADE_APOSTADORES;

    int indice_terceiro_lugar = -1;
    long long maior_resultado_acima_media = 0;

    for (int indice = 0; indice < QUANTIDADE_APOSTADORES; indice++) {
        if (!apostador_premiado[indice] && (double)resultados_fibonacci[indice] > media_resultados) {
            if (indice_terceiro_lugar == -1 || resultados_fibonacci[indice] > maior_resultado_acima_media) {
                maior_resultado_acima_media = resultados_fibonacci[indice];
                indice_terceiro_lugar = indice;
            }
        }
    }

    if (indice_terceiro_lugar != -1) {
        apostador_premiado[indice_terceiro_lugar] = 1;
    }

    if (indice_terceiro_lugar != -1) {
        printf("3o lugar: %s\n", nomes_apostadores[indice_terceiro_lugar]);
    } else {
        printf("3o lugar: Sem vencedor\n");
    }

    if (indice_segundo_lugar != -1) {
        printf("2o lugar: %s\n", nomes_apostadores[indice_segundo_lugar]);
    } else {
        printf("2o lugar: Sem vencedor\n");
    }

    if (indice_primeiro_lugar != -1) {
        printf("1o lugar: %s\n", nomes_apostadores[indice_primeiro_lugar]);
    } else {
        printf("1o lugar: Sem vencedor\n");
    }

    return 0;
}
