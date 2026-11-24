Esta pasta são os códigos pedidos separados em três partes:

meubanco.c | é onde fica as declarações de constantes e estruturas;

banco.c | onde fica a lógica e regras do banco;

main.c | é o código que fica o fluxo principal e o menu interativo.

A atividade se baseia neste enunciado:

Visão do Banco
Construa um algoritmo que simule uma carteira digital. A carteira deverá conter
os seguintes campos obrigatórios, sem se limitar a eles:
1. Cliente;
2. Saldo;
3. Tipo de conta (01 – corrente, 02 – salário, 03 – poupança);
4. Histórico;
5. Número da conta. O número deverá ser composto por quatro dígitos,
iniciando a contagem em 1000, seguidos pelo código correspondente ao
tipo de conta. Exemplo: 1000-01.
O banco poderá ter n clientes. O cliente poderá solicitar um empréstimo caso
possua saldo na conta-poupança e também tenha uma conta corrente, sendo
permitido apenas um empréstimo por cliente. O limite do empréstimo
corresponderá a 25% de dez vezes o saldo total da conta.
O sistema deverá apresentar um menu principal com as seguintes opções:
abrir o banco, consultar histórico, efetuar sorteio e sair. As opções de consulta
ao histórico e efetuar sorteio só poderão ser utilizadas se o banco estiver
aberto.
O cliente não poderá possuir, simultaneamente, uma conta-salário e uma conta
corrente. Todas as demais opções e combinações de contas serão permitidas.
O banco permitirá que os clientes adquiram títulos de capitalização, desde que
possuam entre R$ 1.000,00 e R$ 1.500,00 de saldo na contasalário.
Os clientes que estiverem com saldo negativo na conta corrente deverão
receber uma mensagem de alerta sempre que acessarem o sistema, enquanto
permanecerem nessa condição.
O banco deverá oferecer a opção de realizar um sorteio entre os cinco clientes
com os maiores saldos, desde que todos os participantes tenham adquirido
títulos de capitalização. O sorteio deverá seguir o critério do algoritmo de
sorteio baseado em Fibonacci, desenvolvido em sala de aula.O cliente
vencedor do sorteio deverá receber, em sua conta, um prêmio equivalente a
dez vezes o saldo nela disponível no momento da realização do sorteio.
Inicialmente, o banco deverá cadastrar todos os clientes com os saldos de suas
respectivas contas zerados.
Exemplo de saída para o Histórico:
== Saldo Total do banco ==
<Qtde de clientes> | R$ <valor>
== Clientes Aptos a Empréstimos ==
<nome>|<número>|<valor que pode ser concedido>
== Clientes com Saldo Negativo na Conta Salário ==
<nome>|<número>|<saldo da conta>
== Clientes Aptos a Compra de Títulos ==
<nome>|<número>|<saldo da conta>
== Clientes Contemplado no Sorteio ==
<nome>|<número>|<valor do prêmio>
