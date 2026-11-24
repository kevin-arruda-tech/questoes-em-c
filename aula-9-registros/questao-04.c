/* Atividade 4: Para otimizar o desempenho do disco, você precisa salvar uma lista inteira
de professores de uma só vez. A struct Professor possui registro (int) e horas_aula (int).
O que o algoritmo deve fazer:
Perguntar ao usuário quantos professores ele deseja cadastrar (N).
Alocar dinamicamente um array para N professores.
Criar um segundo bloco de memória (um buffer bruto de bytes com tamanho N *
sizeof(Professor)).
Utilizar memcpy() para copiar o array inteiro de structs para dentro desse buffer.
Gravar o buffer completo no arquivo folha.dat com uma única chamada da função
fwrite().
Criar uma função de leitura que use fread() para carregar tudo de volta em um novo
array dinâmico.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int registro;
    int horas_aula;
} Professor;

Professor* ler_professores_arquivo(const char *nome_arquivo, int quantidade) {
    if (quantidade <= 0) {
        return NULL;
    }

    FILE *arquivo = fopen(nome_arquivo, "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s para leitura.\n", nome_arquivo);
        return NULL;
    }

    Professor *lidos = (Professor *)malloc((size_t)quantidade * sizeof(Professor));
    if (lidos == NULL) {
        printf("Erro ao alocar memoria para leitura dos professores.\n");
        fclose(arquivo);
        return NULL;
    }

    size_t itens_lidos = fread(lidos, sizeof(Professor), (size_t)quantidade, arquivo);
    if (itens_lidos != (size_t)quantidade) {
        printf("Erro ao ler os dados completos do arquivo.\n");
        free(lidos);
        fclose(arquivo);
        return NULL;
    }

    fclose(arquivo);
    return lidos;
}

int main() {
    int n = 0;

    printf("Quantos professores deseja cadastrar? ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Quantidade invalida.\n");
        return 1;
    }

    Professor *professores = (Professor *)malloc((size_t)n * sizeof(Professor));
    if (professores == NULL) {
        printf("Erro ao alocar memoria para os professores.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Professor %d:\n", i + 1);
        printf("Registro: ");
        scanf("%d", &professores[i].registro);
        printf("Horas aula: ");
        scanf("%d", &professores[i].horas_aula);
    }

    size_t tamanho_bytes = (size_t)n * sizeof(Professor);
    unsigned char *buffer = (unsigned char *)malloc(tamanho_bytes);
    if (buffer == NULL) {
        printf("Erro ao alocar buffer bruto de bytes.\n");
        free(professores);
        return 1;
    }

    memcpy(buffer, professores, tamanho_bytes);

    FILE *arquivo = fopen("folha.dat", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo folha.dat para escrita.\n");
        free(buffer);
        free(professores);
        return 1;
    }

    fwrite(buffer, tamanho_bytes, 1, arquivo);
    fclose(arquivo);

    Professor *professores_carregados = ler_professores_arquivo("folha.dat", n);
    if (professores_carregados != NULL) {
        printf("\n=== PROFESSORES CARREGADOS DE FOLHA.DAT ===\n");
        for (int i = 0; i < n; i++) {
            printf("Registro: %d | Horas aula: %d\n",
                   professores_carregados[i].registro,
                   professores_carregados[i].horas_aula);
        }
        free(professores_carregados);
    }

    free(buffer);
    free(professores);

    return 0;
}