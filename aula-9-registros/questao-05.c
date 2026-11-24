/* Atividade 5: Um sistema eleitoral precisa registrar votos. Crie uma struct Eleitor
com titulo (char[12]) e zona (int). Crie uma struct Cedula que contenha um Eleitor
(struct aninhada) e o numero_voto (int).
O que o algoritmo deve fazer:
a) Implementar uma função que adicione votos dinamicamente (realoque
memória usando realloc à medida que novos votos entram).
b) Salvar a lista completa em um arquivo binário urnas.bin.
c) Desenvolver uma função de recuperação rápida que abra o arquivo, descubra
o tamanho total dele (usando fseek e ftell), aloque exatamente o espaço
necessário na memória de uma só vez, e leia todos os registros do arquivo
diretamente para o bloco alocado.*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_TITULO 12

typedef struct {
    char titulo[MAX_TITULO];
    int zona;
} Eleitor;

typedef struct {
    Eleitor eleitor;
    int numero_voto;
} Cedula;

Cedula* adicionar_voto(Cedula *cedulas, int *qtd_votos, Cedula novo_voto) {
    int nova_qtd = *qtd_votos + 1;
    Cedula *temp = (Cedula *)realloc(cedulas, (size_t)nova_qtd * sizeof(Cedula));
    if (temp == NULL) {
        printf("Erro ao realocar memoria para novo voto.\n");
        return cedulas;
    }
    cedulas = temp;
    cedulas[*qtd_votos] = novo_voto;
    *qtd_votos = nova_qtd;
    return cedulas;
}

int salvar_urnas(const char *nome_arquivo, const Cedula *cedulas, int qtd_votos) {
    FILE *arquivo = fopen(nome_arquivo, "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s para escrita.\n", nome_arquivo);
        return 0;
    }

    if (qtd_votos > 0) {
        size_t escritos = fwrite(cedulas, sizeof(Cedula), (size_t)qtd_votos, arquivo);
        if (escritos != (size_t)qtd_votos) {
            printf("Erro ao gravar todos os registros em %s.\n", nome_arquivo);
            fclose(arquivo);
            return 0;
        }
    }

    fclose(arquivo);
    return 1;
}

Cedula* recuperacao_rapida(const char *nome_arquivo, int *qtd_recuperados) {
    *qtd_recuperados = 0;

    FILE *arquivo = fopen(nome_arquivo, "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s para recuperacao.\n", nome_arquivo);
        return NULL;
    }

    if (fseek(arquivo, 0L, SEEK_END) != 0) {
        printf("Erro ao posicionar no final do arquivo.\n");
        fclose(arquivo);
        return NULL;
    }

    long tamanho_bytes = ftell(arquivo);
    if (tamanho_bytes < 0) {
        printf("Erro ao obter o tamanho do arquivo.\n");
        fclose(arquivo);
        return NULL;
    }

    rewind(arquivo);

    if (tamanho_bytes == 0) {
        fclose(arquivo);
        return NULL;
    }

    Cedula *bloco = (Cedula *)malloc((size_t)tamanho_bytes);
    if (bloco == NULL) {
        printf("Erro ao alocar memoria para recuperacao rapida.\n");
        fclose(arquivo);
        return NULL;
    }

    size_t total_itens = (size_t)tamanho_bytes / sizeof(Cedula);
    size_t lidos = fread(bloco, sizeof(Cedula), total_itens, arquivo);
    if (lidos != total_itens) {
        printf("Erro ao ler os registros do arquivo.\n");
        free(bloco);
        fclose(arquivo);
        return NULL;
    }

    *qtd_recuperados = (int)total_itens;
    fclose(arquivo);
    return bloco;
}

int main() {
    Cedula *cedulas = NULL;
    int qtd_votos = 0;
    int continuar = 1;

    while (continuar) {
        Cedula nova;
        printf("Digite o titulo do eleitor: ");
        scanf(" %11s", nova.eleitor.titulo);

        printf("Digite a zona eleitoral: ");
        scanf("%d", &nova.eleitor.zona);

        printf("Digite o numero do voto: ");
        scanf("%d", &nova.numero_voto);

        cedulas = adicionar_voto(cedulas, &qtd_votos, nova);

        printf("Deseja registrar outro voto? (1 - Sim / 0 - Nao): ");
        scanf("%d", &continuar);
    }

    if (salvar_urnas("urnas.bin", cedulas, qtd_votos)) {
        printf("\nVotos salvos em urnas.bin com sucesso.\n");
    }

    free(cedulas);

    int qtd_recuperados = 0;
    Cedula *recuperados = recuperacao_rapida("urnas.bin", &qtd_recuperados);

    if (recuperados != NULL) {
        printf("\n=== VOTOS RECUPERADOS DE URNAS.BIN ===\n");
        for (int i = 0; i < qtd_recuperados; i++) {
            printf("Voto %d -> Titulo: %s | Zona: %d | Numero: %d\n",
                   i + 1,
                   recuperados[i].eleitor.titulo,
                   recuperados[i].eleitor.zona,
                   recuperados[i].numero_voto);
        }
        free(recuperados);
    }

    return 0;
}