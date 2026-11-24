/* Atividade 2: Você está desenvolvendo um sistema de RH. A struct
Funcionario possui id (int), cargo (char[30]) e salario (float).
O que o algoritmo deve fazer:
a) Alocar dinamicamente na memória (usando malloc) o
registro de um funcionário e preencher seus dados.
b) Alocar dinamicamente um segundo registro ("Buffer de
Backup").
c) Usar a função memcpy() para espelhar instantaneamente os
dados do funcionário original no buffer de backup.
d) Salvar o conteúdo do buffer de backup em um arquivo
binário chamado backup_rh.bin.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARGO 30

typedef struct {
    int id;
    char cargo[MAX_CARGO];
    float salario;
} Funcionario;

int main() {
    Funcionario *funcionario = (Funcionario *)malloc(sizeof(Funcionario));
    if (funcionario == NULL) {
        printf("Erro ao alocar memoria para o funcionario.\n");
        return 1;
    }

    printf("ID: ");
    scanf("%d", &funcionario->id);

    printf("Cargo: ");
    scanf(" %29[^\n]", funcionario->cargo);

    printf("Salario: ");
    scanf("%f", &funcionario->salario);

    Funcionario *buffer_backup = (Funcionario *)malloc(sizeof(Funcionario));
    if (buffer_backup == NULL) {
        printf("Erro ao alocar memoria para o buffer de backup.\n");
        free(funcionario);
        return 1;
    }

    memcpy(buffer_backup, funcionario, sizeof(Funcionario));

    FILE *arquivo = fopen("backup_rh.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo backup_rh.bin para escrita.\n");
        free(funcionario);
        free(buffer_backup);
        return 1;
    }

    fwrite(buffer_backup, sizeof(Funcionario), 1, arquivo);

    fclose(arquivo);
    free(funcionario);
    free(buffer_backup);

    return 0;
}