# Carteira Digital em C

Este repositório contém os códigos do projeto de carteira digital divididos em três partes:

* **`meubanco.h`**: onde ficam as declarações de constantes, estruturas (`struct`) e protótipos de funções;
* **`banco.c`**: onde fica a implementação da lógica e das regras do banco;
* **`main.c`**: onde fica o fluxo principal do programa e o menu interativo.

A atividade se baseia no enunciado **Visão do Banco** (carteira digital com `n` clientes, contas iniciando em `1000`, empréstimos, títulos de capitalização, alertas de saldo negativo, sorteio baseado em Fibonacci e consulta de histórico)[cite: 1, 2].

## Visão do Banco

Construa um algoritmo que simule uma **carteira digital**. A carteira deverá conter os seguintes campos obrigatórios, sem se limitar a eles:

1. **Cliente**;
2. **Saldo**;
3. **Tipo de conta** (`01` – corrente, `02` – salário, `03` – poupança);
4. **Histórico**;
5. **Número da conta**: deverá ser composto por quatro dígitos, iniciando a contagem em `1000`, seguidos pelo código correspondente ao tipo de conta. Exemplo: `1000-01`.

---

### Regras de Funcionamento

* **Quantidade de clientes e cadastro inicial**: o banco poderá ter `n` clientes. Inicialmente, o banco deverá cadastrar todos os clientes com os saldos de suas respectivas contas zerados.
* **Combinação de contas**: o cliente não poderá possuir, simultaneamente, uma conta-salário e uma conta corrente. Todas as demais opções e combinações de contas serão permitidas.
* **Menu principal**: o sistema deverá apresentar um menu principal com as seguintes opções:
* **Abrir o banco**
* **Consultar histórico**
* **Efetuar sorteio**
* **Sair**


> As opções de **consultar histórico** e **efetuar sorteio** só poderão ser utilizadas se o banco estiver aberto.


* **Empréstimos**: o cliente poderá solicitar um empréstimo caso possua saldo na conta-poupança e também tenha uma conta corrente, sendo permitido apenas **um empréstimo por cliente**. O limite do empréstimo corresponderá a **25% de dez vezes o saldo total da conta**.
* **Títulos de capitalização**: o banco permitirá que os clientes adquiram títulos de capitalização, desde que possuam entre **R$ 1.000,00 e R$ 1.500,00** de saldo na conta-salário.
* **Alerta de saldo negativo**: os clientes que estiverem com saldo negativo na conta corrente deverão receber uma mensagem de alerta sempre que acessarem o sistema, enquanto permanecerem nessa condição.
* **Sorteio (Fibonacci)**: o banco deverá oferecer a opção de realizar um sorteio entre os **cinco clientes com os maiores saldos**, desde que todos os participantes tenham adquirido títulos de capitalização. O sorteio deverá seguir o critério do algoritmo de sorteio baseado em **Fibonacci**, desenvolvido em sala de aula. O cliente vencedor do sorteio deverá receber, em sua conta, um prêmio equivalente a **dez vezes o saldo** nela disponível no momento da realização do sorteio.

---

### Exemplo de Saída para o Histórico

```text
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

```
