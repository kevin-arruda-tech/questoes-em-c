/* 5. Uma organização está desenvolvendo um sistema para cadastrar quatro participantes de uma competição. Cada participante deverá possuir
um identificador (ID) calculado a partir de sua idade. O sistema também deverá registrar valores numéricos, calcular médias ponderadas e
classificar os participantes de acordo com uma comparação geométrica.
Desenvolva um algoritmo em linguagem C que execute as seguintes operações:
1.Cadastro dos participantes
- Solicite o nome e a idade de quatro participantes.
- Calcule o ID de cada participante utilizando o fatorial da idade dividido por 2.
- Os IDs deverão ser únicos.
- Caso dois ou mais participantes obtenham o mesmo ID, o cálculo deverá ser refeito utilizando o fatorial da metade da idade do
participante, elevado à quantidade de valores capturados.
- Caso ainda exista duplicidade, repita o procedimento até obter um ID exclusivo.
2. Captura dos valores
- Solicite ao usuário a quantidade de valores que serão registrados para cada participante.
- Armazene os valores em uma matriz, na qual cada linha representa um participante e cada coluna representa um valor informado.
- Os valores poderão ser positivos, negativos ou iguais a zero.
3. Organização dos participantes
Após realizar os cadastros, organize os quatro participantes em ordem alfabética pelo nome, mantendo corretamente associados seus
IDs e respectivos valores armazenados na matriz.
4. Cálculo da média ponderada
Desenvolva uma função para calcular a média ponderada dos valores capturados para cada participante.
Considere como pesos a sequência crescente de números naturais, começando em 1. Assim, o primeiro valor terá peso 1, o segundo
peso 2, o terceiro peso 3 e assim sucessivamente.
5. Cálculo da diagonal do retângulo
O programa deverá identificar os dois primeiros valores não negativos informados pelo usuário durante a entrada dos dados. Esses
valores representarão os lados de um retângulo.
Calcule o comprimento da diagonal desse retângulo utilizando o Teorema de Pitágoras.
Caso não sejam encontrados dois valores não negativos, o programa deverá informar que não foi possível calcular a diagonal.
6. Classificação dos participantes
Compare a média ponderada de cada participante com o comprimento da diagonal calculada.
Classifique os participantes em três categorias:
- Acima da diagonal: média ponderada maior que o comprimento da diagonal.
- Abaixo da diagonal: média ponderada menor que o comprimento da diagonal.
- Sobre a diagonal: média ponderada igual ao comprimento da diagonal.
7. Saída do programa
Ao final, apresente os nomes dos quatro participantes em ordem alfabética, acompanhados de sua classificação em relação à diagonal do
retângulo.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define NUM_PARTICIPANTES 4
#define MAX_NOME 100
#define MAX_VALORES 100
#define EPS 1e-9

double fatorial(double n) {
    if (n < 0) {
        return 0.0;
    }
    int inteiro = (int)n;
    double res = 1.0;
    for (int i = 2; i <= inteiro; i++) {
        res *= (double)i;
    }
    return res;
}

double media_ponderada(double valores[], int qtd) {
    if (qtd <= 0) {
        return 0.0;
    }
    double soma_ponderada = 0.0;
    double soma_pesos = 0.0;
    for (int j = 0; j < qtd; j++) {
        double peso = (double)(j + 1);
        soma_ponderada += valores[j] * peso;
        soma_pesos += peso;
    }
    return soma_ponderada / soma_pesos;
}

int ids_iguais(double a, double b) {
    return fabs(a - b) <= EPS;
}

int main() {
    char nomes[NUM_PARTICIPANTES][MAX_NOME];
    int idades[NUM_PARTICIPANTES];
    double ids[NUM_PARTICIPANTES];
    int qtd_valores = 0;
    double matriz[NUM_PARTICIPANTES][MAX_VALORES];

    double nao_negativos[2];
    int cont_nao_negativos = 0;

    for (int i = 0; i < NUM_PARTICIPANTES; i++) {
        printf("Digite o nome do participante %d: ", i + 1);
        scanf(" %99[^\n]", nomes[i]);

        printf("Digite a idade de %s: ", nomes[i]);
        scanf("%d", &idades[i]);
    }

    printf("Digite a quantidade de valores para cada participante: ");
    scanf("%d", &qtd_valores);
    if (qtd_valores < 0) {
        qtd_valores = 0;
    }
    if (qtd_valores > MAX_VALORES) {
        qtd_valores = MAX_VALORES;
    }

    for (int i = 0; i < NUM_PARTICIPANTES; i++) {
        for (int j = 0; j < qtd_valores; j++) {
            printf("Digite o valor %d de %s: ", j + 1, nomes[i]);
            scanf("%lf", &matriz[i][j]);

            if (matriz[i][j] >= 0.0 && cont_nao_negativos < 2) {
                nao_negativos[cont_nao_negativos] = matriz[i][j];
                cont_nao_negativos++;
            }
        }
    }

    for (int i = 0; i < NUM_PARTICIPANTES; i++) {
        ids[i] = fatorial((double)idades[i]) / 2.0;
    }

    int houve_duplicidade;
    do {
        houve_duplicidade = 0;
        for (int i = 0; i < NUM_PARTICIPANTES; i++) {
            int duplicado = 0;
            for (int k = 0; k < NUM_PARTICIPANTES; k++) {
                if (i != k && ids_iguais(ids[i], ids[k])) {
                    duplicado = 1;
                    break;
                }
            }
            if (duplicado) {
                houve_duplicidade = 1;
                double base = fatorial((double)idades[i] / 2.0);
                ids[i] = pow(base, (double)qtd_valores);
            }
        }
    } while (houve_duplicidade);

    for (int i = 0; i < NUM_PARTICIPANTES - 1; i++) {
        for (int j = i + 1; j < NUM_PARTICIPANTES; j++) {
            if (strcmp(nomes[i], nomes[j]) > 0) {
                char temp_nome[MAX_NOME];
                strcpy(temp_nome, nomes[i]);
                strcpy(nomes[i], nomes[j]);
                strcpy(nomes[j], temp_nome);

                int temp_idade = idades[i];
                idades[i] = idades[j];
                idades[j] = temp_idade;

                double temp_id = ids[i];
                ids[i] = ids[j];
                ids[j] = temp_id;

                for (int c = 0; c < qtd_valores; c++) {
                    double temp_val = matriz[i][c];
                    matriz[i][c] = matriz[j][c];
                    matriz[j][c] = temp_val;
                }
            }
        }
    }

    if (cont_nao_negativos < 2) {
        printf("\nNao foi possivel calcular a diagonal do retangulo (menos de dois valores nao negativos informados).\n");
        return 0;
    }

    double diagonal = sqrt(pow(nao_negativos[0], 2.0) + pow(nao_negativos[1], 2.0));

    printf("\n========== CLASSIFICACAO FINAL ==========\n\n");
    for (int i = 0; i < NUM_PARTICIPANTES; i++) {
        double mp = media_ponderada(matriz[i], qtd_valores);
        const char *classificacao;

        if (mp > diagonal + EPS) {
            classificacao = "ACIMA DA DIAGONAL";
        } else if (mp < diagonal - EPS) {
            classificacao = "ABAIXO DA DIAGONAL";
        } else {
            classificacao = "SOBRE A DIAGONAL";
        }

        printf("%-12s ............ %s\n", nomes[i], classificacao);
    }
    printf("\n=========================================\n");

    return 0;
}