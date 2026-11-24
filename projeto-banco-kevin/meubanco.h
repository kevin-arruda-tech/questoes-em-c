#ifndef MEUBANCO_H
#define MEUBANCO_H

#define TIPO_CORRENTE          1
#define TIPO_SALARIO           2
#define TIPO_POUPANCA          3

#define MAX_NOME               100
#define MAX_HISTORICO          512
#define QTD_FINALISTAS_SORTEIO 5

typedef struct {
    char nome[MAX_NOME];
    int numero_base;               /* Inicia no número 1000 */
    int tipo_conta;                /* tipo 1: corrente, tipo 2: salario, tipo 3: poupança */
    double saldo;                  /* Saldo total consolidado */
    double saldo_corrente;         /* Saldo da conta corrente */
    double saldo_salario;          /* Saldo da conta salario */
    double saldo_poupanca;         /* Saldo da conta poupanca */
    int possui_corrente;           /* 1 se possui conta corrente */
    int possui_salario;            /* 1 se possui conta salario */
    int possui_poupanca;           /* 1 se possui conta poupanca */
    int possui_emprestimo;         /* Maximo 1 emprestimo por cliente */
    int comprou_titulo;            /* 1 se adquiriu titulo */
    char historico[MAX_HISTORICO];
} Carteira;

typedef struct {
    Carteira *clientes;
    int quantidade_clientes;
    int banco_aberto;              /* 0: fechado, 1: aberto */
    int proximo_numero;            /* Começa no número 1000 */
} Banco;

/* Seção das Funções principais do menu */
void inicializar_banco(Banco *banco);
void abrir_banco(Banco *banco);
void consultar_historico(const Banco *banco);
void efetuar_sorteio(Banco *banco);
void liberar_banco(Banco *banco);

/* Seção das Operações do cliente e regras do banco */
void acessar_conta_cliente(Banco *banco);
void registrar_evento_historico(Carteira *cliente, const char *descricao_evento);
void atualizar_saldo_total(Carteira *cliente);
int validar_combinacao_contas(int possui_corrente, int possui_salario);
double calcular_limite_emprestimo(const Carteira *cliente);
int apto_titulo_capitalizacao(const Carteira *cliente);
void verificar_alerta_saldo_negativo(const Carteira *cliente);

/* Seção das Funções auxiliares de Fibonacci para o sorteio */
long long soma_fibonacci(int quantidade_termos);
int eh_primo(long long numero);
int escolher_vencedor_fibonacci(const Banco *banco, const int indices_finalistas[QTD_FINALISTAS_SORTEIO]);

#endif