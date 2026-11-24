/* Questão 1 - Crie uma função chamada mostrarSaudacao () que exiba a mensagem “
Bem-vindo ao mundo das funções em C!”. No programa principal (main),
chame essa função três vezes */

#include <stdio.h>

void apresentarSaudacao() {
    printf("Bem-vindo ao mundo das funções em C!\n");
}

int main() {
    apresentarSaudacao();
    apresentarSaudacao();
    apresentarSaudacao();

    return 0;
}