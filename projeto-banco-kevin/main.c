#include <stdio.h>
#include "meubanco.h"

static void exibir_menu(void) {
    printf("\n=== MENU PRINCIPAL ===\n");
    printf("1 - Abrir o banco\n");
    printf("2 - Consultar historico\n");
    printf("3 - Efetuar sorteio\n");
    printf("4 - Sair\n");
    printf("5 - Acessar conta de cliente\n");
    printf("Escolha uma opcao: ");
}

int main(void) {
    Banco banco_digital;
    int opcao_menu = 0;

    inicializar_banco(&banco_digital);

    do {
        exibir_menu();
        if (scanf("%d", &opcao_menu) != 1) {
            printf("Entrada invalida.\n");
            while (getchar() != '\n') {
            }
            continue;
        }
        while (getchar() != '\n') {
        }

        switch (opcao_menu) {
            case 1:
                abrir_banco(&banco_digital);
                break;
            case 2:
                consultar_historico(&banco_digital);
                break;
            case 3:
                efetuar_sorteio(&banco_digital);
                break;
            case 4:
                printf("Saindo do sistema...\n");
                break;
            case 5:
                acessar_conta_cliente(&banco_digital);
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao_menu != 4);

    liberar_banco(&banco_digital);
    return 0;
}
