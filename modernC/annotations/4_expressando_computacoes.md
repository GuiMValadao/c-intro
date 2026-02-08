# **Capítulo 4 - Expressando Computações**

Esta seção cobre:
* Realizando aritmética;
* Modificando objetos;
* Trabalhando com booleanos;
* O operador ternário;
* Definindo a ordem de avaliação.

Já usamos alguns exemplos simples de expressões. Elas são seções(snippets) de código que computam um valor com base em outros valores. As mais simples expressões são expressões aritméticas, que são parecidas com as que aprende-se na escola. Mas existem outras, em particular, operadores de comparação como == e !=, que vimos no capítulo anterior.

## 4.1 Operandos e operadores

Aqui, os valores e objetos nos quais realizaremos as computações serão, em maior parte, do tipo size_t, que já vimos. Tais valores correspondem a 'tamanhos', de modo que são números que não podem ser negativos. Sua faixa de alcance de valores possíveis inicia em 0. O que gostaríamos de representar são todos os números inteiros não-negativos, denotados comumente como N, N0 ou números 'naturais' em matemática. Infelizmente, os computadores são finitos, então não se pode representar todos os números naturais, mas pode-se fazer uma aproximação razoável. Existe um limite superior SIZE_MAX que é o limiar superior do que pode-se representar com size_t. -> size_t - [0, SIZE_MAX].

O valor de SIZE_MAX é bem grande, e depende do tamanho de palavra da plataforma. Pode ser:

* 2^16 - 1 = 65 535
* 2^32 - 1 = 4 294 967 295
* 2^64 - 1 = 18 446 744 073 709 551 615

O primeiro valor é uma exigência mínima. Hoje em dia, valores tão pequenos apenas ocorrem em plataformas embutidas (embedded). Os outros dois valores são mais comumente usados: o segundo ainda é encontrado em alguns PCs e notebooks, e a grande maioria das plataformas mais recentes tem o terceiro. A escolha desse valor é grande o suficiente para cálculos que não são sofisticados demais. O cabeçalho padrão <stdint.h> fornece SIZE_MAX, de modo que não precisamos descobrir qual seu valor por nós mesmos ou especializar o programa de acordo.

O conceito de 'números que não podem ser negativos' que nos referimos para size_t corresponde aos chamados *unsigned integer types* em C. Símbolos e combinações como + e != são chamados operadores, e as coisas às quais eles são aplicados são chamados operandos. Assim, em algo como a + b, + é o operador e a e b são operandos. Para uma visualização geral de todos os operadores em C, veja as seguintes tabelas:

* Tabela 4.1 lista os operadores que atuam em valores.
* Tabela 4.2 lista os que atuam em objetos.
* Tabela 4.3 lista as que atuam em tipos.

Para trabalhar com eles, você pode precisar ter de pular de uma tabela para outra.

