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

Para trabalhar com eles, você pode precisar ter de pular de uma tabela para outra. Por exemplo, se quer resolver uma expressão como a + 5, onde a é algua variável de tipo unsigned, primeiro precisará ir à terceira linha da tabela 4.2 para avaliar a. Então, pode usar a terceira linha na tabela 4.1 para deduzir que o valor de a e 5 são combinados em uma operação aritmética: a +. Não se frustre se não entender tudo nessas tabelas. Vários conceitos que são mencionados ainda não foram introduzidos; elas estão listadas aqui para criar uma referência para o livro inteiro.

![Tabela 4.1](imagens\tabela_4_1.png)

![Tabela 4.2](imagens\tabela_4_2.png)

![Tabela 4.3](imagens\tabela_4_3.png)

## 4.2 Aritmética

Os operadores aritméticos formam o primeiro grupo da tabela 4.1 de operadores que atuam em operandos.

*4.2.1. +, - e * :* Funcionam, em geral, como esperaríamos computando a soma, subtração e multiplicação, respectivamente:

```
size_t a = 45;
size_t b = 7;
size_t c = (a - b) * 2;
size_t d = a - b * 2;
```

Aqui, `c ` deve ser igual a 76, e `d` a 31. Como pode ver deste pequeno exemplo, sub-expressões podem ser agrupadas com parênteses para forçar uma ordem de operações preferencial.

Além disso, os operadores + e - tem variantes unárias (unary). -b dá o negativo de b: um valor a de modo que b + a seja 0. +a fornece simplesmente o valor de a.

Mesmo tendo usado um tipo sem sinal(unsigned) para nossa computação, a negação e diferença por meio do operador `-` são *bem definidas*. Isto é, independente dos valores que fornecemos para esta abstração, nossa computação sempre terá um resultado válido. De fato, uma das propriedades milagrosas de size_t é que a aritmética +-* sempre funciona onde pode. Enquanto o resultado matemético final estiver dentro do domínio(range) [0, SIZE_MAX], então o resultado será o valor da expressão.

Quando o resultado não está dentro do domínio e, assim, não é representável como um valor size_t, chamamos de transbordamento (*overflow*) aritmético. O transbordamento pode ocorrer, por exemplo, se multiplicarmos dois valores que são tão grandes que seu produto matemático é maior que SIZE_MAX. Vamos olhar em como C lida com o transbordamento na próxima seção.

*4.2.2 Divisão e resto:* Os operadores / e % são um pouco mais complexos pois correspondem à divisão de inteiros e a operação de resto. a/b é avaliado como o número de vezes que b cabe dentro de a, e a%b é o valor restante após o número máximo de b's serem removidos de a. Os operadores / e % vem em pares: se temos z = a/b, o restande a%b pode ser computado como a - z*b. Para valores sem sinal, `a == (a/b)*b + (a%b)`.

Um exemplo familiar do operador % são as horas no relógio. Imagine que temos um relógio de 12 horas: 6 horas após 8:00 são 2:00. A maioria das pessoas conseguem computar diferenças temporais em relógios de 12 e 24 horas. Esta computação corresponde a a % 12: em nosso exemplo, (8 + 6) % 12 == 2 -- o programa clock_24 exemplifica esta situação. Outro uso similar para % é a computação usando minutos em uma hora, na forma a % 60.

Existe apenas um valor não permitido para essas operações: 0. A divisão por zero é proibida.

O operador % também pode ser usado para explicar aritmética multiplicativa e aditiva em tipos sem sinal um pouco melhor. Como já mencionado, quando um tipo sem sinal recebe um valor fora de seu domínio, é dito que transborda. Neste caso, o resultado é reduzido como se o operador % tivesse sido usado. O valor resultado "enrola" (wraps around) em torno do domínio do tipo. No caso de size_t, o domínio é de 0 até SIZE_MAX. Aritmética em size_t implicitamente computa modulo SIZE_MAX + 1.

Isto significa que para valores size_t, SIZE_MAX + 1 é igual a 0, e 0 - 1 é igual a SIZE_MAX. Este 'enrolamento' é a mágica que faz os operadores `-` funcionarem para tipos sem sinal. Por exemplo, o valor -1 interpretado como um size_t é igual a SIZE_MAX; então acrescentar -1 a um valor `a` apenas calcula `a + SIZE_MAX`, que enrola acabando em:

a + SIZE_MAX - (SIZE_MAX + 1) = a - 1

Os operadores / e % tem a boa propriedade que seus resultados são sempre menores ou iguais a seus operandos. Assimm, aritmética sem sinal com operadores / e % nunca transbordará.

## 4.3 Operadores que modificam objetos

Outra operação importante que já vimos é a atribuição: `a = 42`. Como pode ver deste exemplo, este operador não é simétrico; tem um valor à direita e um objeto à esquerda. Em um abuso esquisito da linguagem, jargão C costuma se referir ao lado direito como *rvalue* (right value/valor à direita) e ao objeto na esquerda como *lvalue* (left value/valor à esquerda). Vamos tentar evitar este vocabulário sempre que possível; falar de valor e objeto é suficiente. C possui outros operadores de atribuição. Para qualquer operador binário @, todos os 5 que já vimos tinham a sintaxe: `an_object @= some_expression;`. Eles são apenas abreviações convenientes para combinar o operador aritmético @ e a atribuição; Um forma equivalente é: `an_object = (an_object @ (some_expression));`. Em outras palavras, existem os operadores +=, -=, *=, /= e %=. Por exemplo, em um loop for, o operador += pode ser usado:
```
for (size_t i = 0; i < 25; i += 7){
    ...
}
```

A sintaxe desses operadores é um pouco enjoada(picky). Você não pode ter espaço vazio entre os caracteres de operação diferentes, por exemplo, i + = 7 em vez de i += 7 é um erro de sintaxe.

Já vimos duas outras operações que modificam objetos: o operador acréscimo ++ e decréscimo --. O primeiro é equivalente a i += 1 e o segundo a i -= 1.

Todos esses operadores de atribuição são operadores reais. Eles retornam o valor do objeto após a modificação, mas não o próprio objeto. Você poderia escrever algo como:

```
a = b = c += ++d;
a = (b = (c += (++d))); //Same
```

Mas esse tipo de combinação para vários objetos de uma vez costuma ser desincentivada (frowned upon). Não faça isso a menos que queira ofuscar seu código. Tais alterações para objetos que estão envolvidos em uma expressão são chamadas de efeitos colaterais.

Para os operadores de acréscimo e decréscimo, existem outras duas formas: *postfix increment* (acréscimo pós-fixo) e *postfix decrement* (decréscimo pós-fixo). Eles diferem do que já vimos no resultado que fornecem à expressão que o cerca. As versões prefixadas desses operadores(++a e --a) fazem a operação primeiro e então retornam o resultado; as operações pós-fixas retornam o valor antes da operação e realizam a modificação depois. Para qualquer um deles, o efeito na variável é o mesmo: o valor aumentado ou diminuído. Tudo isso mostra que a avaliação de expressões com efeitos colaterais pode ser difícil de seguir. Não faça isso.

## 4.4 Contexto booleano