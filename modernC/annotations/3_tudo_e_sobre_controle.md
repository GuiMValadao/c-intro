# **Tudo é sobre controle**

Esta seção aborda:
* Execução condicional com `if`
* Iteração sobre domínios
* Fazer múltiplas seleções

No exemplo introdutório, o programa 'getting-started.c', vimos dois construtos diferenes que nos permitiram controlar o fluxo da execução de um programa: funções e a iteração `for`. As funções são uma maneira de controlar o fluxo incondicionalmente. A chamada transfere o controle para a função, e uma declaração `return` transfere novamente para o ponto em que foi chamada. Retornaremos às funções na seção 7.

A declaração `for` é diferente pois possui uma condição de controle que regula se e, se sim, quando o bloco secundário é executado. C tem 5 declarações de controle condicionais: `if`, `for`, `do`, `while` e `switch`. Vamos ver essas declarações nessa seção: `if` introduz uma execução condicionada que depende de uma expressão booleana; `for`, `do` e `while` são formas diferentes de iterações; e `switch` é uma seleção múltipla baseado em um valor inteiro.

C ainda possui alguns outros condicionais que discutiremos posteriormente: o operador ternário, denotado por uma expressão na forma `cond ? A : B`; condicionais do preprocessador do momento-de-compilação #if, #ifdef, #ifndef, #elif, #elifdef, #elifndef, #else, #endif; e expressões de tipo genérico denotadas com a palavra chave _Generic.

## 3.1 Execução condicional

O primeiro construto que veremos é especificado pela palavra chave `if`. Parece assim:

```
if (i > 25) {
    j = i - 25;
}
```

Aqui comparamos `i` com o valor 25. Se é maior que 25, `j` é definido como `i-25`. No exemplo, i > 25 é chamado de expressão de controle, e a parte em {...} é chamado bloco secundário. Uma forma mais geral do construto `if` é:

```
if (i > 25) {
    j = i - 25;
} else {
    j = i;
}
```

Ela possui outro bloco secundário que é executado se a condição de controle não é preenchida. Sintáticamente, isto é feito introduzindo outra palavra chave, `else`, que separa dois blocos secundários. O construto `if (...) ... else ...` é uma declaração de seleção. Ela seleciona um dos dois caminhos de código possível, de acordo com o counteúdo de (...). A forma geral é: 

```
if (condição) bloco-secundario0
else bloco-secundario1
```

As possibilidades para a condição (expressão de controle) são inúmeras. Pode, ser desde comparações simples, como no exemplo, até expressões aninhadas bastante complexas. A especificações mais simples dessas condições é uma declaração `if` que pode ser vista no exemplo seguinte, em uma variação do loop `for` do programa 'getting-started.c':

```
for (size_T i = 0; i < 5; ++i) {
    if (i) {
        printf("element %zu is %g, \tits square is %g\n",
        i,
        A[i],
        A[i] * A[i]);
    }
}
```

Aqui, a condição que determina se printf é executado é apenas `i`: um valor numérico por si só pode ser interpretado como uma condição. O texto será exibido apenas quando o valor de 'i' não é 0. Existem duas regras simples para a avaliação de uma condição numérica:

* O valor 0 representa um lógico falso.
* Qualquer valor diferente de 0 representa um lógico verdadeiro.

Os operadores == e != permitem-nos testar igualdades e diferenças, respectivamente. a == b é verdade se o valor de a é igual ao de b, e falso se não; a != b pe falso se a é igual a b e diferente se não. 

O tipo bool deve ser usado para armazenar valores de verdade. Seus valores são true e false. Tecnicamente, false é apenas um valor 0 do tipo bool e true o valor 1. É importante usar false e true (não os números) para enfatizar que é um valor a ser interpretado como uma condição. Aprenderemos mais sobre o tipo bool na seção 5.7.4. Note qie antes do C23, para usar bool e seus literais false e true, era necessário usar o cabeçalho <stdbool.h>. Com o C23, isto tornou-se obsoleto, sendo usado apenas se você suspeitar que seu código possa ser compilado em uma plataforma mais antiga.

Comparações redundantes se tornam ilegíveis rapidamente e bagunçar o código. Se você tem um condicional que depende de um valor verdade, use aquele valor diretamente como a condição. Novamente, podemos evitar redundância reescrevendo algo como:
```
bool b = ...;
if ((b != false) == true) {
    ...
}
```

como:

```
bool b = ...;
...
if (b) {
    ...
}
```

*Não compare com 0, false ou true.* Usar ou o valor verdade diretamente (como o i acima) ou a negação (denotado como !i em C) torna o código mais limpo e ilustra um dos conceitos básicos da linguagem C.

*Todos os escalares tem um valor verdade*. Aqui, tipos escalares incluem todos os tipos numéricos como size_t, bool e int que já encontramos e tipos pointer. Veja a tabela abaixo para os tipos que são usados frequentemente neste livro:

![Tipos escalares](imagens\tipos.png)

## 3.2 Iterações

Anteriormente, encontramos a declaração `for`para iterar sobre um domínio. No exemplo introdutório, declaramos uma variável i que foi definida para os valores 0, 1, 2, 3 e 4. A forma geral desta declaração é:

```
for (cláusula1; condição2; expressão3) bloco-secundário
```

Esta declaração é, na verdade, bem genérica. Geralmente, cláusula1 é uma expressão de atribuição ou definição de variável. Serve para colocar um valor inicial para o domínio da iteração. condição2 testa se a iteração deveria continuar. Então, expressão3 atualiza a variável de iteração usada em cláusula1, sendo executada ao final de cada iteração. Alguns conselhos:

* Como queremos que as variáveis de iteração sejam definidas estreitamente no contexto do loop `for`, cláusula1 deveria, na maioria dos casos, ser a definição de uma variável.
* Como `for` é relativamente complexo com suas 4 partes diferentes e não é fácil de capturar visualmente, o bloco secundário deveria, geralmente, ser uma declaração composta indicada por {...}.

Alguns exemplos são:

```
for (size_t i = 10; i; --i) {
    something(i);
}
for (size_t i = 0; stop = upper_bound(); i < stop; ++i) {
    something_else(i);
}
for (size_t i = 9; i <= 9; --i) {
    something_else(i);
}
```

O primeiro `for` conta i decrescentemente, de 10 até 1, inclusive. A condição é. novamente, apenas a avaliação ad variável i, sendo desnecessário teste redundante comparando com o valor 0. Quando i torna-se 0, será avaliado como falso, e o loop terminará. O segundo `for` declara duas variáveis, i e stop. Assim como antes, i é a variável do loop, stop é com o que queremos comparar na condição, e quando i torna-se maior ou igual a stop, o loop termina. O terceiro `for` parece como se fosse continuar indefinidamente, mas na verdade ele conta de 9 até 0. Na próxima seção, veremos que "sizes" em C (números como o tipo size_t) nunca são negativos.

Observe que todos as três declarações `for` declaram variáveis chamadas `i`. Estas três variáveis com o mesmo nome podem coexistir lado a lado desde que seus escopos não se sobreponham. 

Existem ainda outras duas declarações iterativas em C, `while` e `do`:

```
while (condição) bloco-secundário
do bloco-secundário while (condição);
```

O seguinte exemplo mostra um uso típico de `while`. Ele implementa a *aproximação de Heron* para computar o inverso multiplicativo 1/x de um número x:

```
#include <tgmath.h>

consexpr double e = 1E-9;   // precisão desejada
...
double const a = 34.0;
double x = 0.5;
while (fabs(1.0 - a*x) >= e) {      // itera até próximo
    x *= (2.0 - a*x);               // da aproximação de Heron
}
```

Ele itera enquanto a condição dada permanecer verdadeira, ou seja, enquanto o valor absoluto da diferença entre 1.0 e o produto computado for menor que uma constante nomeada chamada `e`, que representa a precisão mínima desejada para a computação. O loop `do` é similar, exceto que checa a condição após o bloco secundário:

```
do {                            // Itera
    x *= (2.0 - a*x);           // Aproximação de Heron
} while (fabs(1.0 - a*x) >= e); // Itera até próximo
```

Isto significa que se a condição for falsa imediatamente, um loop while não executará o bloco secundário nenhuma vez, mas o loop do executará pelo menos uma vez incondicionalmente antes mesmo de olhar a condição. Assim como para a declaração `for`, com `do` e `while` é aconselhável usar as variantes {...}. Também existe uma diferença sintática sutil entre os dois: `do` sempre precisa de um ponto e vírgula após `while(condição)` para finalizar a declaração. Mais tarde, veremos que este é um recurso sintático que acaba sendo bem útil no contexto de várias declarações aninhadas.

Todas as três declarações de iteração se tornam ainda mais flexíveis com as declarações `break` e `continue`. A primeira para o loop sem reavaliar a condição de término ou executar a parte do bloco secundário depois da declaração `break`:
```
while (true) {
    double prod = a*x;
    if (fabs(1.0 - prod) < e) {     //termina se próximo o suficiente 
        break;
    }
    x *= (2.0 - prod);              // Aprox. de Heron
}
```

Deste jeito, podemos separar a computação do produto a*x, a avaliação da condição de término e a atualização de x. A condição de `while`, então, se torna trivial. A mesma coisa pode ser feita usando `for`, e existe uma tradição entre programadores de C para escrever como segue:

```
for (;;) {
    double prod = a*x;
    if (fabs(1.0 - prod) < e) {     //termina se próximo o suficiente 
        break;
    }
    x *= (2.0 - prod);              // Aprox. de Heron
}
```

`for(;;)` aqui é equivalente a `while(true)`. O fato da expressão de controle de for (a parte do meio entre ;;) poder ser omitida, sendo interpretada como 'sempre verdadeira', é apenas um artefato historico nas regras de C e não tem nenhum outro propósito especial.

A declaração `continue` é usado com menos frequência. Assim como break, ela pula a execução do resto do bloco secundário para a iteração atual. Entretanto, então ela reavalia a condição e continua do início do bloco secundário se a condição for verdadeira:

```
for (size_t i = 0; i < max_iterations; ++i) {
    if (x > 1.0) {
        x = 1.0 /x;
        continue;
    }
    double prod = a * x;
    if (fabs(a.0 - prod) < e) {
        break;
    }
    x *= (2.0 - prod);
} 
```

Nestes exemplos, usando uma macro padrão `fabs`, que vem com o cabeçalho <tgmath.h>. Ela calcula o valor absoluto de um double. O programa heron_aprox.c é o programa completo que implementa o mesmo algoritmo, onde `fabs` foi substituída por várias comparações explícitas com certos números fixos: por exemplo, eps1m24 definido como sendo 1-1x2^-24 ou eps1p24 como 1+ 1x2^-24. Veremos mais tarde (seção 5.3) como os literais 0x1p-24 (2^-24) e parecidos usados nestas definições funcionam e como interagem com o construto constexpr.

Na primeira parte, o produto entre o número atual sob investigação `a` com a estimativa atual `x` é comparado com 1.5 e 0.5, e então `x` é multiplicado por 0.5 ou 2 até o produto tornar-se próximo de 1. Então, a aproximação de Heron, como mostrado no código, é usada em uma segunda iteração para fechar e computar a inversa multiplicativa com um alto grau de acurácia.

A tarefa geral do programa é computar o inverso de todos os números que são fornecidos a ele na linha de comando. Um exemplo de execução pode ser:

```
> ./heron 0.07 5 6E+23
heron: a=7.00000e-02, x=1.42857e+01, a*x=0.999999999996
heron: a=5.00000e+00, x=2.00000e-01, a*x=0.999999999767
heron: a=6.00000e+23, x=1.66667e-24, a*x=0.999999997028
```

Para processar os números na linha de comando, o programa usa outra função `strtod` da biblioteca <stdlib.h>.

## 3.3 Múltiplas seleções

A última declaração de controle que C oferece é a declaração `switch`, que é outra declaração de seleção. É principalmente usada quando uma sequência grande de construtos if-else tornaria-se tediosa:

```
if (arg == 'm') {
    puts("this is a magpie");
} else if (arg == 'r') {
    puts("this is a raven");
} else if (arg == 'j') {
    puts("this is a jay");
} else if (arg == 'c') {
    puts("this is a chough");
} else {
    puts("this is an unknown corvid");
}
```

Neste caso, temos uma escolha que é mais complexa que uma decisão verdadeiro-falso e que pode ter vários resultados. Podemos simplificar como segue:

```
switch (arg) {
    case 'm' : puts("this is a magpie");
               break;
    case 'r' : puts("this is a raven");
               break;
    case 'j' : puts("this is a jay");
               break;
    case 'c' : puts("this is a chough");
               break;
    default: puts("this is an unknown corvid");
}
```

Aqui, selecionamos uma das chamadas a `puts` de acordo com o valor da variável `arg`. Como printf, a função puts é fornecida por <stdio.h>. Ela exibe uma linha com a string que recebe como argumento. Demos casos específicos para caracteres 'm', 'r', 'j' e 'c' e um caso especial rotulado 'default'. O caso default é ativado se arg não equivale a nenhum dos valores de case.

Sintáticamente, uma switch é tão simples quanto `switch (expression) secondary-block` e sua semântica é bastante direta: os rótulos `case` e `default` servem como *alvos de pulo*. De acordo com o valor da expressão, o controle continua na declaração que é rotulada de acordo. Se encontramos uma declaração `break`, a switch em que ela apareceu é finalizada, e o controle do programa é transferido para a próxima declaração após a switch. Por essa especificação, declarações switch podem ser usadas mais amplamente que construtos if-else iterados:

```
switch (count) {
    default: puts("++++ .... +++");
    case 4: puts("++++");
    case 3: puts("+++");
    case 2: puts("++");
    case 1: puts("+");
    case 0:         // antes do C23 esta linha também deveria terminar com ;
}
```

Assim que pulamos para o bloco secundário, a execução continua até encontrar break ou o fim do bloco. Neste caso, como não existem declarações break, acabamos executando todas as declarações puts subsequentes. Por exemplo, a saída quando o valor de count é 3 é um triângulo com 3 linhas:

```
+++
++
+
```

A estrutura de uma switch pode ser mais flexível que if-else, mas é restrita de outras maneiras.

** expressões de `case` precisam ser expressões constantes inteiras.
** valores de `case` devem ser únicos para cada declaração `switch`.

Na seção 5.6.2 veremos o que são essas expressões em detalhes. Por hora, é suficiente saber que elas precisam ter valores fixos que fornecemos diretamente na fonte, como 4, 3, 2, 1, 0 no exemplo acima. Em particular, variáveis como count apenas são permitidas na parte switch, não nos casos individuais.

A maior flexibilidade da declaração switch vem com um preço: é mais suscetível a erros. Em particular, poderíamos acidentalmente pular a definição das variáveis:

```
switch (x) {
    unsigned tmp = 45;
    ...
    case 0: printf("the temp is %u\n", tmp); // tmp pode não ter sido inicializada.
}
```

Variáveis dessa tipo são válidas, mas seu inicializador pode não ter sido visto, por exemplo, quando x é zero. Assim, nesse caso, a execução de um programa onde x coincide com 0 seria errada. A inicialização (ou sua falta) será discutida em maior detalhe na seção 5.5

Antes de C23, o local dos rótulos de case era ainda mais restrito. Eles tinha necessariamente que marcar uma declaração: rótulos na frente de declarações ou logo após a chave de encerramento } de uma declaração composta não eram válidos.

