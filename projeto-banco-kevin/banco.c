#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "meubanco.h"

static void limpar_buffer_entrada(void) {
    int caractere_lido = 0;
    while ((caractere_lido = getchar()) != '\n' && caractere_lido != EOF) {
    }
}

void inicializar_banco(Banco *banco) {
    banco->clientes = NULL;
    banco->quantidade_clientes = 0;
    banco->banco_aberto = 0;
    banco->proximo_numero = 1000;
}

void atualizar_saldo_total(Carteira *cliente) {
    double total = 0.0;
    if (cliente->possui_corrente) {
        total += cliente->saldo_corrente;
    }
    if (cliente->possui_salario) {
        total += cliente->saldo_salario;
    }
    if (cliente->possui_poupanca) {
        total += cliente->saldo_poupanca;
    }
    cliente->saldo = total;
}

void registrar_evento_historico(Carteira *cliente, const char *descricao_evento) {
    size_t tamanho_atual = strlen(cliente->historico);
    if (tamanho_atual + strlen(descricao_evento) + 4 < MAX_HISTORICO) {
        if (tamanho_atual > 0) {
            strncat(cliente->historico, " | ", MAX_HISTORICO - tamanho_atual - 1);
            tamanho_atual = strlen(cliente->historico);
        }
        strncat(cliente->historico, descricao_evento, MAX_HISTORICO - tamanho_atual - 1);
    }
}

int validar_combinacao_contas(int possui_corrente, int possui_salario) {
    /* Cliente nao pode possuir simultaneamente conta-salario e conta corrente */
    if (possui_corrente && possui_salario) {
        return 0;
    }
    return 1;
}

double calcular_limite_emprestimo(const Carteira *cliente) {
    /* Exige conta-poupanca com saldo, conta corrente e no maximo 1 emprestimo[cite: 1] */
    if (!cliente->possui_emprestimo &&
        cliente->possui_poupanca &&
        cliente->saldo_poupanca > 0.0 &&
        cliente->possui_corrente) {
        /* 25% de dez vezes o saldo total da conta[cite: 1] */
        return 0.25 * (10.0 * cliente->saldo);
    }
    return 0.0;
}

int apto_titulo_capitalizacao(const Carteira *cliente) {
    /* Entre R$ 1.000,00 e R$ 1.500,00 de saldo na conta-salario[cite: 1] */
    if (cliente->possui_salario &&
        cliente->saldo_salario >= 1000.0 &&
        cliente->saldo_salario <= 1500.0) {
        return 1;
    }
    return 0;
}

void verificar_alerta_saldo_negativo(const Carteira *cliente) {
    /* Alerta quando o saldo da conta corrente esta negativo[cite: 1] */
    if (cliente->possui_corrente && cliente->saldo_corrente < 0.0) {
        printf("[ALERTA] %s (%04d-%02d): Saldo negativo na conta corrente (R$ %.2f)!\n",
               cliente->nome,
               cliente->numero_base,
               cliente->tipo_conta,
               cliente->saldo_corrente);
    }
}

long long soma_fibonacci(int quantidade_termos) {
    if (quantidade_termos <= 0) {
        return 0;
    }

    long long termo_anterior = 0;
    long long termo_atual = 1;
    long long proximo_termo = 0;
    long long soma_total = 0;

    for (int indice_termo = 1; indice_termo <= quantidade_termos; indice_termo++) {
        soma_total += termo_anterior;
        proximo_termo = termo_anterior + termo_atual;
        termo_anterior = termo_atual;
        termo_atual = proximo_termo;
    }

    return soma_total;
}

int eh_primo(long long numero) {
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

int escolher_vencedor_fibonacci(const Banco *banco, const int indices_finalistas[QTD_FINALISTAS_SORTEIO]) {
    long long resultados_fibonacci[QTD_FINALISTAS_SORTEIO];
    int premiado_finalista[QTD_FINALISTAS_SORTEIO] = {0};

    for (int indice_finalista = 0; indice_finalista < QTD_FINALISTAS_SORTEIO; indice_finalista++) {
        const Carteira *cliente_finalista = &banco->clientes[indices_finalistas[indice_finalista]];
        int quantidade_termos = (cliente_finalista->numero_base % 10) + indice_finalista + 1;
        resultados_fibonacci[indice_finalista] = soma_fibonacci(quantidade_termos);
    }

    /* 1o criterio: maior resultado primo entre os finalistas */
    int indice_vencedor_primo = -1;
    long long maior_primo = 0;
    for (int indice_finalista = 0; indice_finalista < QTD_FINALISTAS_SORTEIO; indice_finalista++) {
        if (!premiado_finalista[indice_finalista] && eh_primo(resultados_fibonacci[indice_finalista])) {
            if (indice_vencedor_primo == -1 || resultados_fibonacci[indice_finalista] > maior_primo) {
                maior_primo = resultados_fibonacci[indice_finalista];
                indice_vencedor_primo = indice_finalista;
            }
        }
    }
    if (indice_vencedor_primo != -1) {
        premiado_finalista[indice_vencedor_primo] = 1;
        return indices_finalistas[indice_vencedor_primo];
    }

    /* 2o criterio: maior resultado par entre os finalistas nao premiados */
    int indice_vencedor_par = -1;
    long long maior_par = 0;
    for (int indice_finalista = 0; indice_finalista < QTD_FINALISTAS_SORTEIO; indice_finalista++) {
        if (!premiado_finalista[indice_finalista] && resultados_fibonacci[indice_finalista] % 2 == 0) {
            if (indice_vencedor_par == -1 || resultados_fibonacci[indice_finalista] > maior_par) {
                maior_par = resultados_fibonacci[indice_finalista];
                indice_vencedor_par = indice_finalista;
            }
        }
    }
    if (indice_vencedor_par != -1) {
        premiado_finalista[indice_vencedor_par] = 1;
        return indices_finalistas[indice_vencedor_par];
    }

    /* 3o criterio: maior resultado acima da media entre os finalistas nao premiados */
    long long soma_resultados = 0;
    for (int indice_finalista = 0; indice_finalista < QTD_FINALISTAS_SORTEIO; indice_finalista++) {
        soma_resultados += resultados_fibonacci[indice_finalista];
    }
    double media_resultados = (double)soma_resultados / QTD_FINALISTAS_SORTEIO;

    int indice_vencedor_media = -1;
    long long maior_acima_media = 0;
    for (int indice_finalista = 0; indice_finalista < QTD_FINALISTAS_SORTEIO; indice_finalista++) {
        if (!premiado_finalista[indice_finalista] && (double)resultados_fibonacci[indice_finalista] > media_resultados) {
            if (indice_vencedor_media == -1 || resultados_fibonacci[indice_finalista] > maior_acima_media) {
                maior_acima_media = resultados_fibonacci[indice_finalista];
                indice_vencedor_media = indice_finalista;
            }
        }
    }
    if (indice_vencedor_media != -1) {
        premiado_finalista[indice_vencedor_media] = 1;
        return indices_finalistas[indice_vencedor_media];
    }

    return indices_finalistas[0];
}

void abrir_banco(Banco *banco) {
    int total_clientes = 0;
    printf("\nQuantos clientes deseja cadastrar? ");
    if (scanf("%d", &total_clientes) != 1 || total_clientes <= 0) {
        printf("Quantidade invalida.\n");
        limpar_buffer_entrada();
        return;
    }
    limpar_buffer_entrada();

    liberar_banco(banco);
    banco->clientes = (Carteira *)calloc((size_t)total_clientes, sizeof(Carteira));
    if (banco->clientes == NULL) {
        printf("Erro ao alocar memoria para os clientes.\n");
        return;
    }

    banco->quantidade_clientes = total_clientes;
    banco->proximo_numero = 1000;

    for (int indice_cliente = 0; indice_cliente < total_clientes; indice_cliente++) {
        Carteira *cliente_atual = &banco->clientes[indice_cliente];
        int deseja_corrente = 0;
        int deseja_salario = 0;
        int deseja_poupanca = 0;

        printf("\n--- Cadastro do cliente %d ---\n", indice_cliente + 1);
        printf("Nome: ");
        fgets(cliente_atual->nome, MAX_NOME, stdin);
        cliente_atual->nome[strcspn(cliente_atual->nome, "\n")] = '\0';

        do {
            printf("Possui conta corrente (01)? (1 - Sim / 0 - Nao): ");
            scanf("%d", &deseja_corrente);
            printf("Possui conta salario (02)? (1 - Sim / 0 - Nao): ");
            scanf("%d", &deseja_salario);
            printf("Possui conta poupanca (03)? (1 - Sim / 0 - Nao): ");
            scanf("%d", &deseja_poupanca);
            limpar_buffer_entrada();

            deseja_corrente = (deseja_corrente != 0);
            deseja_salario = (deseja_salario != 0);
            deseja_poupanca = (deseja_poupanca != 0);

            if (!validar_combinacao_contas(deseja_corrente, deseja_salario)) {
                printf("Combinacao invalida: nao e permitido ter conta-salario e conta corrente simultaneamente[cite: 1].\n");
            } else if (!deseja_corrente && !deseja_salario && !deseja_poupanca) {
                printf("Selecione pelo menos um tipo de conta.\n");
            }
        } while (!validar_combinacao_contas(deseja_corrente, deseja_salario) ||
                 (!deseja_corrente && !deseja_salario && !deseja_poupanca));

        cliente_atual->possui_corrente = deseja_corrente;
        cliente_atual->possui_salario = deseja_salario;
        cliente_atual->possui_poupanca = deseja_poupanca;

        if (cliente_atual->possui_corrente) {
            cliente_atual->tipo_conta = TIPO_CORRENTE;
        } else if (cliente_atual->possui_salario) {
            cliente_atual->tipo_conta = TIPO_SALARIO;
        } else {
            cliente_atual->tipo_conta = TIPO_POUPANCA;
        }

        cliente_atual->numero_base = banco->proximo_numero++;
        cliente_atual->saldo_corrente = 0.0;
        cliente_atual->saldo_salario = 0.0;
        cliente_atual->saldo_poupanca = 0.0;
        cliente_atual->saldo = 0.0;
        cliente_atual->possui_emprestimo = 0;
        cliente_atual->comprou_titulo = 0;
        cliente_atual->historico[0] = '\0';

        registrar_evento_historico(cliente_atual, "Cadastro inicial com saldos zerados[cite: 1].");
    }

    banco->banco_aberto = 1;
    printf("\nBanco aberto com %d cliente(s) cadastrado(s).\n", banco->quantidade_clientes);
}

void acessar_conta_cliente(Banco *banco) {
    int numero_informado = 0;
    int indice_encontrado = -1;

    if (!banco->banco_aberto) {
        printf("\nO banco esta fechado! Abra o banco primeiro[cite: 1].\n");
        return;
    }

    printf("\nInforme o numero base da conta (ex.: 1000): ");
    if (scanf("%d", &numero_informado) != 1) {
        printf("Numero invalido.\n");
        limpar_buffer_entrada();
        return;
    }
    limpar_buffer_entrada();

    for (int indice_cliente = 0; indice_cliente < banco->quantidade_clientes; indice_cliente++) {
        if (banco->clientes[indice_cliente].numero_base == numero_informado) {
            indice_encontrado = indice_cliente;
            break;
        }
    }

    if (indice_encontrado == -1) {
        printf("Cliente nao encontrado.\n");
        return;
    }

    Carteira *cliente = &banco->clientes[indice_encontrado];
    int opcao_cliente = 0;

    /* Alerta sempre que o cliente acessar enquanto tiver saldo negativo na conta corrente[cite: 1] */
    verificar_alerta_saldo_negativo(cliente);

    do {
        printf("\n--- Cliente: %s (%04d-%02d) | Saldo Total: R$ %.2f ---\n",
               cliente->nome, cliente->numero_base, cliente->tipo_conta, cliente->saldo);
        if (cliente->possui_corrente) {
            printf("  Corrente (01): R$ %.2f\n", cliente->saldo_corrente);
        }
        if (cliente->possui_salario) {
            printf("  Salario  (02): R$ %.2f\n", cliente->saldo_salario);
        }
        if (cliente->possui_poupanca) {
            printf("  Poupanca (03): R$ %.2f\n", cliente->saldo_poupanca);
        }
        printf("1 - Depositar\n");
        printf("2 - Sacar\n");
        printf("3 - Solicitar emprestimo\n");
        printf("4 - Adquirir titulo de capitalizacao\n");
        printf("5 - Ver historico do cliente\n");
        printf("0 - Voltar ao menu principal\n");
        printf("Escolha: ");

        if (scanf("%d", &opcao_cliente) != 1) {
            printf("Entrada invalida.\n");
            limpar_buffer_entrada();
            continue;
        }
        limpar_buffer_entrada();

        if (opcao_cliente == 1 || opcao_cliente == 2) {
            int conta_escolhida = 0;
            double valor_operacao = 0.0;
            char mensagem_evento[MAX_HISTORICO];

            printf("Tipo de conta (1 - corrente, 2 - salario, 3 - poupanca): ");
            scanf("%d", &conta_escolhida);
            printf("Valor (R$): ");
            scanf("%lf", &valor_operacao);
            limpar_buffer_entrada();

            if (valor_operacao <= 0.0) {
                printf("Valor deve ser positivo.\n");
                continue;
            }

            if (conta_escolhida == TIPO_CORRENTE && cliente->possui_corrente) {
                if (opcao_cliente == 1) {
                    cliente->saldo_corrente += valor_operacao;
                    snprintf(mensagem_evento, MAX_HISTORICO, "Deposito de R$ %.2f na conta corrente.", valor_operacao);
                } else {
                    cliente->saldo_corrente -= valor_operacao;
                    snprintf(mensagem_evento, MAX_HISTORICO, "Saque de R$ %.2f na conta corrente.", valor_operacao);
                }
                registrar_evento_historico(cliente, mensagem_evento);
            } else if (conta_escolhida == TIPO_SALARIO && cliente->possui_salario) {
                if (opcao_cliente == 1) {
                    cliente->saldo_salario += valor_operacao;
                    snprintf(mensagem_evento, MAX_HISTORICO, "Deposito de R$ %.2f na conta salario.", valor_operacao);
                } else {
                    cliente->saldo_salario -= valor_operacao;
                    snprintf(mensagem_evento, MAX_HISTORICO, "Saque de R$ %.2f na conta salario.", valor_operacao);
                }
                registrar_evento_historico(cliente, mensagem_evento);
            } else if (conta_escolhida == TIPO_POUPANCA && cliente->possui_poupanca) {
                if (opcao_cliente == 1) {
                    cliente->saldo_poupanca += valor_operacao;
                    snprintf(mensagem_evento, MAX_HISTORICO, "Deposito de R$ %.2f na conta poupanca.", valor_operacao);
                } else {
                    cliente->saldo_poupanca -= valor_operacao;
                    snprintf(mensagem_evento, MAX_HISTORICO, "Saque de R$ %.2f na conta poupanca.", valor_operacao);
                }
                registrar_evento_historico(cliente, mensagem_evento);
            } else {
                printf("Cliente nao possui essa conta.\n");
                continue;
            }

            atualizar_saldo_total(cliente);
            verificar_alerta_saldo_negativo(cliente);
        } else if (opcao_cliente == 3) {
            double limite_disponivel = calcular_limite_emprestimo(cliente);
            if (limite_disponivel <= 0.0) {
                printf("Cliente nao atende aos criterios para solicitar emprestimo[cite: 1].\n");
            } else {
                double valor_solicitado = 0.0;
                char mensagem_emprestimo[MAX_HISTORICO];
                printf("Limite maximo disponivel: R$ %.2f. Digite o valor desejado: ", limite_disponivel);
                scanf("%lf", &valor_solicitado);
                limpar_buffer_entrada();

                if (valor_solicitado > 0.0 && valor_solicitado <= limite_disponivel) {
                    cliente->possui_emprestimo = 1;
                    if (cliente->possui_corrente) {
                        cliente->saldo_corrente += valor_solicitado;
                    }
                    atualizar_saldo_total(cliente);
                    snprintf(mensagem_emprestimo, MAX_HISTORICO,
                             "Emprestimo concedido de R$ %.2f.", valor_solicitado);
                    registrar_evento_historico(cliente, mensagem_emprestimo);
                    printf("Emprestimo de R$ %.2f aprovado!\n", valor_solicitado);
                } else {
                    printf("Valor invalido ou acima do limite.\n");
                }
            }
        } else if (opcao_cliente == 4) {
            if (cliente->comprou_titulo) {
                printf("Cliente ja possui titulo de capitalizacao.\n");
            } else if (!apto_titulo_capitalizacao(cliente)) {
                printf("Para adquirir titulo, e preciso ter entre R$ 1.000,00 e R$ 1.500,00 na conta-salario[cite: 1].\n");
            } else {
                cliente->comprou_titulo = 1;
                registrar_evento_historico(cliente, "Titulo de capitalizacao adquirido.");
                printf("Titulo de capitalizacao adquirido com sucesso!\n");
            }
        } else if (opcao_cliente == 5) {
            printf("Historico: %s\n", cliente->historico);
        } else if (opcao_cliente != 0) {
            printf("Opcao invalida.\n");
        }
    } while (opcao_cliente != 0);
}

void consultar_historico(const Banco *banco) {
    if (!banco->banco_aberto) {
        printf("\nO banco esta fechado! Abra o banco primeiro[cite: 1].\n");
        return;
    }

    double saldo_total_banco = 0.0;
    for (int indice_cliente = 0; indice_cliente < banco->quantidade_clientes; indice_cliente++) {
        saldo_total_banco += banco->clientes[indice_cliente].saldo;
    }

    printf("\n== Saldo Total do banco ==\n");
    printf("%d | R$ %.2f\n", banco->quantidade_clientes, saldo_total_banco);

    printf("Clientes Aptos a Empréstimos =\n");
    for (int indice_cliente = 0; indice_cliente < banco->quantidade_clientes; indice_cliente++) {
        const Carteira *cliente_atual = &banco->clientes[indice_cliente];
        double limite_emprestimo = calcular_limite_emprestimo(cliente_atual);
        if (limite_emprestimo > 0.0) {
            printf("%s %04d-%02d|%.2f\n",
                   cliente_atual->nome,
                   cliente_atual->numero_base,
                   cliente_atual->tipo_conta,
                   limite_emprestimo);
        }
    }

    printf("= Clientes com Saldo Negativo na Conta Salário ==\n");
    for (int indice_cliente = 0; indice_cliente < banco->quantidade_clientes; indice_cliente++) {
        const Carteira *cliente_atual = &banco->clientes[indice_cliente];
        if (cliente_atual->possui_salario && cliente_atual->saldo_salario < 0.0) {
            printf("%s %04d-%02d/%.2f\n",
                   cliente_atual->nome,
                   cliente_atual->numero_base,
                   cliente_atual->tipo_conta,
                   cliente_atual->saldo_salario);
        }
    }

    printf("== Clientes Aptos a Compra de Títulos ==\n");
    for (int indice_cliente = 0; indice_cliente < banco->quantidade_clientes; indice_cliente++) {
        const Carteira *cliente_atual = &banco->clientes[indice_cliente];
        if (apto_titulo_capitalizacao(cliente_atual)) {
            printf("%s|%04d-%02d/%.2f\n",
                   cliente_atual->nome,
                   cliente_atual->numero_base,
                   cliente_atual->tipo_conta,
                   cliente_atual->saldo_salario);
        }
    }
}

void efetuar_sorteio(Banco *banco) {
    if (!banco->banco_aberto) {
        printf("\nO banco esta fechado! Abra o banco primeiro[cite: 1].\n");
        return;
    }

    if (banco->quantidade_clientes < QTD_FINALISTAS_SORTEIO) {
        printf("\nE necessario ter pelo menos %d clientes para o sorteio[cite: 1].\n", QTD_FINALISTAS_SORTEIO);
        return;
    }

    int *indices_ordenados = (int *)malloc((size_t)banco->quantidade_clientes * sizeof(int));
    if (indices_ordenados == NULL) {
        printf("Erro ao alocar memoria para ordenar clientes no sorteio.\n");
        return;
    }

    for (int indice_cliente = 0; indice_cliente < banco->quantidade_clientes; indice_cliente++) {
        indices_ordenados[indice_cliente] = indice_cliente;
    }

    for (int indice_externo = 0; indice_externo < banco->quantidade_clientes - 1; indice_externo++) {
        for (int indice_interno = indice_externo + 1; indice_interno < banco->quantidade_clientes; indice_interno++) {
            double saldo_externo = banco->clientes[indices_ordenados[indice_externo]].saldo;
            double saldo_interno = banco->clientes[indices_ordenados[indice_interno]].saldo;
            if (saldo_interno > saldo_externo) {
                int indice_temporario = indices_ordenados[indice_externo];
                indices_ordenados[indice_externo] = indices_ordenados[indice_interno];
                indices_ordenados[indice_interno] = indice_temporario;
            }
        }
    }

    for (int indice_finalista = 0; indice_finalista < QTD_FINALISTAS_SORTEIO; indice_finalista++) {
        const Carteira *finalista = &banco->clientes[indices_ordenados[indice_finalista]];
        if (!finalista->comprou_titulo) {
            printf("\nSorteio cancelado: nem todos os 5 maiores saldos possuem titulo de capitalizacao[cite: 1].\n");
            free(indices_ordenados);
            return;
        }
    }

    int indice_vencedor_banco = escolher_vencedor_fibonacci(banco, indices_ordenados);
    Carteira *vencedor = &banco->clientes[indice_vencedor_banco];

    double valor_premio = 10.0 * vencedor->saldo;
    vencedor->saldo += valor_premio;
    if (vencedor->possui_corrente) {
        vencedor->saldo_corrente += valor_premio;
    } else if (vencedor->possui_poupanca) {
        vencedor->saldo_poupanca += valor_premio;
    } else if (vencedor->possui_salario) {
        vencedor->saldo_salario += valor_premio;
    }

    char mensagem_premio[MAX_HISTORICO];
    snprintf(mensagem_premio, MAX_HISTORICO, "Premio de sorteio Fibonacci: R$ %.2f.", valor_premio);
    registrar_evento_historico(vencedor, mensagem_premio);

    printf("\n= Clientes Contemplado no Sorteio =\n");
    printf("%s %04d-%02d|%.2f\n",
           vencedor->nome,
           vencedor->numero_base,
           vencedor->tipo_conta,
           valor_premio);

    free(indices_ordenados);
}

void liberar_banco(Banco *banco) {
    free(banco->clientes);
    banco->clientes = NULL;
    banco->quantidade_clientes = 0;
    banco->banco_aberto = 0;
}