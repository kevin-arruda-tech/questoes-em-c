/* Atividade 3: Um arquivo binário chamado clientes.bin armazena vários registros da
struct Cliente (contendo conta_corrente (int), nome (char[50]) e saldo (float)).
O que o algoritmo deve fazer:
a) Solicitar ao usuário o número de uma conta corrente e um valor de
depósito/saque.
b) Abrir o arquivo binário em modo de leitura/escrita ("rb+").
c) Ler o arquivo de registro em registro. Ao encontrar a conta correspondente,
atualizar o campo saldo.
d) Utilizar a função fseek() para voltar o ponteiro do arquivo para a posição exata
daquele cliente e sobrescrever o registro antigo com o atualizado.*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_NOME 50

typedef struct {
    int conta_corrente;
    char nome[MAX_NOME];
    float saldo;
} Cliente;

int main() {
    int conta_alvo;
    float valor_operacao;
    int encontrado = 0;

    printf("Digite o numero da conta corrente: ");
    scanf("%d", &conta_alvo);

    printf("Digite o valor (positivo para deposito, negativo para saque): ");
    scanf("%f", &valor_operacao);

    FILE *arquivo = fopen("clientes.bin", "rb+");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo clientes.bin.\n");
        return 1;
    }

    Cliente cli;
    while (fread(&cli, sizeof(Cliente), 1, arquivo) == 1) {
        if (cli.conta_corrente == conta_alvo) {
            cli.saldo += valor_operacao;
            fseek(arquivo, -(long)sizeof(Cliente), SEEK_CUR);
            fwrite(&cli, sizeof(Cliente), 1, arquivo);
            fflush(arquivo);
            encontrado = 1;
            printf("Saldo atualizado com sucesso! Novo saldo de %s: R$ %.2f\n", cli.nome, cli.saldo);
            break;
        }
    }

    if (!encontrado) {
        printf("Conta corrente %d nao encontrada.\n", conta_alvo);
    }

    fclose(arquivo);

    return 0;
}