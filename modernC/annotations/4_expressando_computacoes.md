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

Várias operações fornecem (yield) um valor 0 ou 1, dependendo da verificação de alguma condição. Eles podem ser agrupados em duas categorias: avaliações comparativas e lógicas.

*4.4.1 Comparação:* Em nossos exemplos, já vimos os operadores de comparação ==, !=, < e >. Enquando os últimos dois realizam comparações estritas entre seus operandos, os operadores <= e >= realizam as comparações "menos que ou igual" e "maior que ou igual" , respectivamente. Todos esses operadores podem ser usados em declarações de controle, como já vimos, mas são, na verdade, mais poderosos que isso.

Operadores de comparação retornam o valor `false` ou `true`. Esses dois valores nada mais são que 0 e 1, respectivamente. Então podem ser usados em aritmética ou para indexação de matrizes. No código seguinte, c sempre será 1, e d será 1 se a e b são iguais, se não será 0.

```
size_t c = (a < b) + (a == b) + (a > b);
size_t d = (a <= b) + (a >= b) - 1;
```

No próximo exemplo, N é um número grande, e o elemento da matriz sign[false] armazenará o número de valores em largeA que são maiores ou iguais a 1. 0 e sign[true] aqueles que são estritamente menores:

```
double largeA[N] = { };
...
/* Preenche largeA de alguma maneira */

size_t sign[2] = { 0, 0 }
for (size_t i = 0; i < N; ++i) {
    sign[ (largeA[i] < 1.0)] += 1;
}
```

Por fim, também existe um identificadot not_eq que pode ser usado como substituto para !=. Este recurso é raramente usado, e para usá-lo deve-se incluir o arquivo <iso646.h>.

*4.4.2 Lógica:* Operadores lógicos operam em valores que já deveriam representar valores false ou true. Se não, as regras descritas para a execução condicional se aplicam primeiro. O operador `!` (not) nega o operando logicamente, e os operadores `&&` (and) é o 'e' lógico e `||`(or) é o 'ou' lógico. Os resultados desses operadores são sumarizados na tabela 4.4.

![Tabela 4.4](imagens/ope_logico.png)

De forma similar às operações de comparação, operações lógicas retornam valores de verdade, false ou true. Esses valores ainda assim são 0 e 1 e podem ser usados como índices:

```
double largeA[N] = { };
...
/* Preenche largeA de alguma maneira */

size_t sign[2] = { 0, 0 }
for (size_t i = 0; i < N; ++i) {
    sign[!!(largeA[i] < 1.0)] += 1;
}
```

Aqui, a expressão !!largeA[i] aplica o operador ! duas vezes e apenas garante que largeA[i] é avaliado como um valor verdade. Como resultado, a matriz de elementos isset[0] e isset[1] armazenarão o número de valores que são iguais a 0.0 e ineguais, respectivamente.

Os operadores && e || tem uma propriedade particular chamada avaliação de curto-circuito. Este termo denota o fato que a avaliação do segundo operando é omitida se não for necessária para o resultado da operação:

```
// Isto nunca divide por 0
if (b != 0 && ((a/b) > 1)) {
    ++x;
}
```

Aqui, a avaliação de a/b é omitida condicionalmente durante a execução, e, portanto, uma divisão por 0 nunca ocorrerá. O seguinte código é equivalente:

```
if (b) {
    if (a/b > 1) {
        ++x;
    }
}
```

## 4.5 Operador ternário ou condicional

O operador ternário é similar a uma declaração if, mas é uma expressão que retorna o valor do galho(branch) escolhido:

```
size_t size_min(size_t a, size_t b) {
    return (a < b) ? a : b;
}
```

Similar aos operadores && e ||, o segundo e terceiro operandos são avaliados apenas se forem necessários de fato. O macro sqrt de <tgmath.h> computa a raiz quadrada de um valor não-negativo. Chamá-la com um valor negativa levanta um erro de domínio:

```
#include <tgmath.h>

#ifdef __STDC_NO_COMPLEX__
# error "we need complex arithmetic"
#endif

double complex sqrt_real(double x) {
    return (x < 0) ? CMPLX(0, sqrt(-x)) : CMPLX(sqrt(x), 0);
}
```

Nesta função, sqrt é chamada apenas uma vez, e o argumento para chamá-la nunca será negativo. Assim, sqrt_real sempre se comportará corretamente; nenhum valor ruim será passado a ela.

Aritmética de números complexos e as ferramentas usadas para isso precisam do cabeçalho <complex.h>, que é indiretamente incluída por <tgmath.h>. Ambos serão introduzidos mais tarde, na seção 5.7.8.

No exemplo anterior, também vemos uma compilação condicional que é conseguida com diretivas pré-processador. O construto #ifdef garante que acessamos a condição #error apenas se o macro __STDC_NO_COMPLEX__ é definido.


## 4.6 Ordem de avaliação

Dos operadores até aqui, vimos que &&, || e ?: condicionam a avaliação de alguns de seus operandos: o primeiro operando, como é uma condição para as restantes, sempre será avaliada primeiro.

A vírgula é o único operador que ainda não foi introduzido. Ele avalia seus operandos em ordem, e o resultado é o valor do operando à direita. Por exemplo, (f(a), f(b)) primeiro avalia f(a) e então f(b); o resultado é o valor de f(b).

Saiba que o caractere vírgula tem outros papeis sintáticos em C que *não* usam a mesma convenção sobre avaliação. Por exemplo, as vírgulas que separam inicializações não tem as mesmas propriedades que aquelas que separam argumentos de funções. 

O operador vírgula é raramenta útil em código limpo, e é uma armadilha para iniciantes: A[i, j] não é um índice bidimensional para uma matriz A, mas resulta em A[j].

Outros operadores não tem restrições de avaliação. Por exemplo, em uma expressão como f(a) + g(b), não existe uma ordem pré-estabelecida especificando se f(a) ou g(b) deve ser computada primeiro. Se qualquer das funções f ou g possuem efeitos colaterais (por exemplo, se f modifica b por trás da cortina), o resultado da expressão dependerá da ordem escolhida.

Esta ordem podem depender do compilador, da versão do compilador, opções da hora da compilação, ou apenas do código do entorno da expressão. Não dependa de qualquer dessas formas de sequênciação, elas vão atrapalhar.

O mesmo é verdade para argumentos de funções. Em algo como:

```
printf("%g and %g\n", f(a), f(b));
```

não saberíamos qual dos dois últimos argumentos é avaliado primeiro.

A única forma confiável de não depender da ordem de avaliação de expressões aritméticas é remover efeitos colaterais.