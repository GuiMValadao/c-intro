# **Capítulo 2 - Estrutura principal de um programa**

Esta seção trata sobre:

* Gramática C
* Declarando identificadores
* Instruindo o compilador com declarações

Comparados com os exemplos do capítulo 1, programas reais serão mais complicados e conterão mais instruções, mas suas estruturas permanecerão muito similares. O programa `getting-started` possui a maioria dos elementos estruturais de um programa C.

Existem duas categorias de aspectos a serem consideradas em um programa C: aspectos sintáticos (como especificamos o programa para que o compilador o entenda?) e aspectos semânticos(o que especificamos para que o programa faça o que queremos?). Nas seguintes seções, introduziremos os aspectos sintáticos (gramática) e três aspectos de semântica diferentes: partes declarativas (o que são as coisas), definições de objetos (onde as coisas estão) e declarações (o que as coisas devem fazer).

## 2.1 Gramática

Observando sua estrutura geral, podemos ver que um programa C é composto por diferentes tipos de elementos textuais que são juntados em um tipo de gramática. Estes elementos são:

**Palavras especiais**: no programa `getting-started` usamos as seguintes palavras especiais (diretivas, palavras-chave, atributos e reservadas):

>`#include int maybe_unused char void double for return`

Essas palavras especiais representam conceitos e recursos que a linguagem C impõe e que não podem ser alteradas.

**Pontuação**: C usa vários tipos de pontuação para estruturar o texto dos programas.

* Existem 6 tipos de 'brackets': {...}, (...), \[...\], \[\[...\]\], /*...*/ e <...>. Brackets agrupam certas partes do programa e deveriam sempre estar em pares. Os brackets <...> são raros e usados apenas como mostrado no exemplo, na mesma linha lógica de texto. Os outros 5 não são limitados a uma única linha; seus conteúdos podem cobrir várias linhas, como na declaração de printf mostrada no programa `getting-started`.

* Existem dois separadores ou terminadores diferentes: vírgula e ponto e vírgula. Quando usamos printf, as vírgulas separaram os 4 argumentos da função. Na linha 12, vimos que uma vírgula também pode seguir o último elemento de uma lista de elementos: `[3] = .00007,`. 

Uma das dificuldades para iniciantes em C é que os mesmos caracteres de pontuação são usados para expressar conceitos diferentes. Por exemplo, {} e [] são usados para três propósitos diferentes no programa `getting-started`. O construto /\*...*/ diz ao compilador que tudo dentro dele é um comentário. Os comentários são ignorados pelo compilador, sendo o lugar perfeito para explicar e documentar seu código. Outra forma de comentário é o chamado estilo-C++, na linha 15, marcado com //, que são estendem desde o // até o final da linha.

**Literais**: Nosso programa contém vários items que referenciam valores fixos que são parte do programa: `0`, `1`, `3`, `4`, `6`, `9.0`, `2.9`, `3.E+25`, `.00007` e `"element %zu is %g \tits square is %g\n"`. Eles são chamados *literais*.

**Identificadores**: Identificadores são "nomes" que nós (ou o padrão C) dá a certas entidades no programa. Aqui temos `A`, `i`, `main`, `printf`, `size_t`, e `EXIT_SUCCESS`. Identificadores podem ter diferentes funções em um programa. Entre outras coisas, podem se referir a:
    
* **Objetos de dados** (como `A` e `i`). Também chamados *variáveis*.
    
* **Tipos** aliases, como `size_t`, que especifica o "tipo" de um novo objeto(neste caso, `i`). Observe a barra _t no nome. Esta convenção de nomeação é usada pelo C padrão para lembrá-lo que o identificador se refere a um tipo.

* Funções, como `main` e `printf`.

* Constantes, como `EXIT_SUCCESS`.

**Funções**: Dois dos identificadores se referem a funções. Como já vimos, `printf` é usada pelo programa para produzir alguma saída. A função `main`, por sua vez, é *definida*, isto é, sua *declaração* `int main(void)` é seguida pelo *corpo de uma função* (indicado por {...} de uma declaração composta) que descreve o que a função deve fazer. Em nosso exemplo, esta definição da função vai da linha 6 até a 24. `main` tem um papel especial em programas C, como veremos: deve sempre estar presente pois é o ponto inicial da execução do programa.

**Operadores**: Dos vários operadores C, nosso programa usa apenas alguns:
* = para *inicialização* ou *atribuição*
* < para comparação
* ++ para incrementar uma variável (somar 1 a seu valor)
* \* para multiplicar dois valores

**Atributos**: Atributos como `[[maybe_unused]]` são colocados entre chaves duplas como mostrado e fornecem alguma informação extra para a estrutura principal do programa (este recurso é novo de C23, de modo que o compilador pode não tê-lo implementado ainda).

## 2.2 Declarações

Antes de podermos usar um identificador particular em um programa, temos que dar ao compilador uma *declaração* que especifica o que aquele identificador deve representar. Desta forma, identificadores são diferentes de palavras chave: as palavras chave são predefinidas pela linguagem de não devem ser declaradas ou redefinidas.

Muitos dos identificadores que usamos são declarados no programa: `main`, `argc`, `argv`, `A` e `i`. Posteriormente, veremos de onde os outros identificadores vem (`printf`, `size_t` e `EXIT_SUCCESS`). Já mencionamos a declaração da função `main`. Todas as cinco declarações, isoladas como 'apenas declarações', pareceriam com:

>```
>int main(int, char* []);
>int argc;
>[[maybe_unused]] char* argv[];
>double A[5];
>size_t i;
>```

Estas cinco declarações seguem um padrão. Cada uma tem um identificador (main, argc, argv, A ou i), e uma especificação de certas propriedades que são associadas àquele identificador:

* `i` é do tipo `size_t`
* `argc` é do tipo `int`
* `main` é seguida por parênteses, e assim declara uma função do tipo `int`
* `A` é seguida por chaves, e assim declara uma matriz. Uma matrizs é um agregado de vários items do mesmo tipo; aqui, consiste de 5 items do tipo `double`. Estes cinco items são ordenados e podem ser referenciados por números, chamado índices, de 0 a 4.
* `argv` também é seguido por chaves, então tem as propriedades de uma matriz. O atributo `[[maybe_unused]]` indica que é, possivelmente, não usado e, de fato, não vemos a palavra argv em nenhum outro lugar no código. Existem argc+1 elementos de um tipo denotado por char*.

Cada uma dessas declarações inicia com um tipo. Veremos mais tarde o que isso representa. Por hora, é suficiente saber que especifica que 4 dos identificadores (main, argc, A e i), quando usados no contexto de uma declração, fornecerão algum tipo de número.

Para o outro, argv, o asterisco no fim de char* indica que é um ponteiro(*pointer*); apesar de uma das principais características da linguagem C, os ponteiros aparecerão apenas muito à frente no livro. As declarações de argc, i e A declaram variáveis, que são items nomeados que nos permitem armazenar valores. Elas são melhor visualizadas como um tipo de caixa que pode conter alguma 'coisa' de um tipo particular.

Conceitualmente, é importante diferenciar a caixa em si (o objeto), a especificação (seu tipo), os conteúdos da caixa (seu valor), e o nome ou rótulo que está escrito na caixa (o identificador). Nestes tipos de diagrama, colocamos ?? se não soubermos o valor real de um item.

![diagrama de variáveis](imagens\diagrama_exemplo_variaveis.png)

Para os outros três identificadores, `printf`, `size_t` e `EXIT_SUCCESS`, não vemos nenhuma declaração. Eles são identificadores pré-declarados. Entretanto, como vimos quando tentamos compilar com o programa 'bad.c', a informação sobre estes identificadores não vem de lugar nenhum. Temos de dizer ao compilador onde ele pode obter informação sobre eles. Isto é feito bem no início do programa, com as declarações #include: `printf` é fornecida por <stdio.h> enquanto `size_t` e `EXIT_SUCCESS` vem de <stdlib.h>. As declarações reais desses identificadores são especificadas nos arquivos .h com estes nomes em algum lugar do computador. Poderiam ser algo do tipo:

```
int printf(char const format[static 1], ...);
typedef unsigned long size_t;
#define EXIT_SUCCESS 0
```

Porque as especificidades desses recursos pré-declarados são de menor importância, esta informação é, normalmente, escondida em *include files* ou *header files*. Se precisar saber sua semântica, normalmente é uma má ideia procurá-la nos arquivos correspondentes, pois costumam ser difícil de ler. Em vez disso, procure na documentação que vem com a plataforma. A fonte das informações é o C padrão, mas os seguintes comandos podem ajudar:

```
apropos printf
man printf
man 3 printf
```

Uma declaração apenas descreve um recurso, não o cria, de modo que repetir uma declaração não traz muito problema além da redundância. Por isso, identificadores podem ter várias declarações consistentes.

Obviamente, seria bastante confuso (tanto para os programadores quanto para o compilador), se existissem várias declarações conflitantes para o mesmo identificador na mesma parte do programa, de forma que isto não é permitido. C é bem específico sobre o significado de 'mesma parte do programa': o escopo(*scope*) é uma parte do programa onde um identificador é visível.

Os escopos dos identificadores são descritos de maneira não-ambígua pela gramática. No programa 'getting-started', tinhamos declarações em escopos diferentes:
* `A` é visível dentro da definição da função `main`, iniciando sua declaração na linha 8 e terminando ao fechar } na linha 24 da declaração composta que contém aquela declaração.
* `i` tem visibilidade mais restrita. Está presa ao construto `for` no qual é declarada. Sua visibilidade alcance desde sua declaração na linha 16 até o final da declaração composta {} que é associada ao loop for na linha 21.
* `main` não é cercada por qualquer outra declaração composta, sendo visível desde sua declaração até o final do arquivo.
* `argc` e `argv` não estão cercados por {}, mas estão dentro de () que marca main como sendo uma função. Eles são parâmetros da função, e seu escopo inicia em suas respectivas declarações e então atingem o corpo inteiro {} de sua função (nesse caso, `main`).

Os primeiros dois e o último tipos de escopo são chamados de escopos de bloco, com um bloco sendo uma estrutura na gramática que encapsula tais declarações. Uma função como `main`, junto com sua lista de parâmetros e seu corpo inteiro, formam um único bloco por si só. O construto for forma um bloco primário, e o corpo do loop (normalmente dado entre colchetes {}), forma um bloco secundário. Você pode ver que blocos são aninhados: o bloco de `main` contém o bloco primário do loop `for`, que, por sua vez, contém seu bloco secundário.

O terceiro tipo de escopo, como usado para o nome `main`, que não está dentro de parênteses ou colchetes, é chamado escopo do arquivo. Identificadores no escopo do arquivo são, frequentemente chamados de globais. Então, nosso aparentemente simples programa tem 4 níveis de escopo aninhados: o escopo do arquivo e três aninhados.

## 2.3 Definições

Geralmente, declarações especificam apenas o tipo ao qual um objeto se refere, não o valor concreto do identificador nem onde ele pode ser encontrado. Este papel importante é cumprido por uma definição. ***Declarações* especificam identificadores, enquanto *definições* especificam objetos.**

Veremos mais tarde que as coisas são um pouco mais complicadas na vida real, mas por enquanto, podemos fazer a simplificação que sempre inicializaremos nossas variáveis. Uma inicialização é um construto gramatical que aumenta uma declaração e fornece um valor inicial para o objeto. Por exemplo, `size_t i = 0;` é uma declaração de `i` com valor inicial 0. Em C, este tipo de declaração com um inicializador também define o objeto com o nome correspondente: isto é, instrui o compilador a fornecer armazenamento no qual o valor da variável pode ser armazenado.

Nossa caixa para visualização pode ser completa com um valor 0, neste exemplo:

![alt text](imagens\init_variable.png)

`A` é um pouco mais complexo pois possui várias componentes:

```
double A[5] = {
    [0] = 9.0,
    [1] = 2.9,
    [4] = 3.E+25,
    [3] = .00007,
};
```

![alt text](imagens\init_A.png)

A forma do inicializador que vemos aqui é chamado *designado*(designated): um par de brackets com um inteiro designa qual item da matriz é inicializado com o valor correspondente. Por exemplo, [4] = e.E+25 define o último item da matriz A como o valor 3.E+25. Como uma regra especial, qualquer posição não listada no inicializador tem o valor 0. No exemplo, o item [2] é preenchido com 0.

Além disso, a indexação inicia em 0, com o primeiro elemento sendo [0] e o último elemento sendo [4], ou seja, para uma matriz de n elementos, o primeiro terá índice 0 e o último índice n-1.

Para uma função, temos uma definição (ao contrário de declaração), se sua declaração é seguida por chaves {} contendo o código da função:

```
int main(int argc, [[maybe_unused]] char* argv[argc+1]){
    ...
}
```

Nos exemplos até aqui, vimos nomes para dois recursos diferentes: objetos (`i` e `A`), e funções (`main`e `printf`). Ao contrário de declarações de funções, onde são permitidas várias para o mesmo identificador, a definição de objetos ou funções deve ser única. Isto é, para que um programa em C seja operacional, qualquer objeto ou função usada deve ter uma definição, e não pode ter mais que uma definição (para manter a consistência do programa).

## 2.4 Declarações

A segunda parte da função `main` consiste primariamente de declarações, que são instruções dizendo ao compilador o que fazer com os identificadores que foram declarados até aquele ponto. Temos:
```
for (size_t i=0; i < 5; ++i) {
    printf("element %zu is %g \tits square is %g\n",
    i,
    A[i],
    A[i]*A[i]);
}
return EXIT_SUCCESS;
```

As linhas da chamada de printf já foram discutidas. Também estão presentes outros tipos de declarações: `for`, `return` e uma operação de incrementação indicada pelo operador ++. Na seguinte subseção, vamos entrar um pouco em detalhes das três categorias de declarações: iterações, chamadas de funções e retorno de funções.

### 2.4.1 Iteração

A declaração `for` diz ao compilador que o programa deve executar a linha printf algum número de vezes. Esta é a forma mais simples de uma iteração de domínio que C oferece. Ela possui 4 partes diferentes. O bloco secundário (aqui, uma declaração composta marcada por {...}) que segue `for` é o código que deve ser repetido, também chamado corpo do loop. As outras três partes são aquelas dentro dos parênteses, divididas por ponto e vírgula:

1. A declaração, definição e inicialização da variável do loop `i`, que já foi discutida. A inicialização é executada uma vez antes de qualquer uma das repetições do resto da declaração `for`.

2. Uma condição de loop, `i < 5`, especifica até quando a iteração do loop `for` deve continuar. A condição do exemplo diz que deve continuar enquanto `i` for estritamente menor que 5. A condição de loop é checada antes de cada execução do corpo do loop.

3. Outra declaração, `++i`, é executada após cada iteração. Neste caso, aumenta o valor de `i` em 1 cada vez.

O fato que podemos identificar cada iteração com um valor específico de `i` faz desta uma iteração sobre o domínio 0, ..., 4. Existem mais de uma forma de fazer isso em C, mas `for` é a mais fácil, sucinta e melhor ferramenta para isso.

Uma declaração `for` pode ser escrita de várias outras formas. Frequentemente, a variável de loop é definida em algum lugar antes do `for`, ou mesmo reutilizada para vários loops. Não faça isso: para ajudar um leitor ocasional e o compilador a entender seu codigo, é importante saber que esta variável tem o significado especial de um contador de iteração para aquele loop específico.

### 2.4.2 Chamadas de funções

As chamadas de funções são declarações especiais que suspendem a execução da função atual (inicialmente, essa seria normalmente a `main`) e então entregam o controle à função nomeada. Em nosso exemplo, a função chamada é a `printf`. Uma chamada de função normalmente fornece mais que apenas o nome da função; também fornece argumentos. Aqui, eles são a frase inicial, i, A[i] e A[i]\*A[i]. Os valores desses argumentos são passados para a função. Neste caso, estes valores são a informação que é exibida por printf. A ênfase aqui é no *valor*: apesar de i ser um argumento, printf nunca poderá alterá-lo sozinha. Este mecanismo é chamado chamada por valor. Outras linguagens de programação também tem chamadas por referência, um mecanismo onde a função chamada pode alterar o valor de uma variável. C não implementa a passagem por referência; em vez disso, tem outro mecanismo para passar o controle de uma variável para outra função: pegando o endereço e transmitindo ponteiros. Varemos esse mecanismo muito mais à frente.

### 2.4.3 Retorno da função

A última declaração em `main` é um `return`. Ela diz à função main para retornar à declaração de onde foi chamada após terminada. Aqui, como `main` tem `int` em sua declaração, o `return` *deve* retornar um valor do tipo inteiro para a declaração que chamou a função. Neste caso, o valor é `EXIT_SUCCESS`.

Mesmo não podendo ver sua definição, a função `printf` deve conter uma declaração `return` similar. No ponto onde chamamos a função na linha 17, a execução das declarações em `main` é suspensa temporariamente. A execução continua dentro da função printf até que um `return` seja encontrado. Após o retorno de printf, a execução das declarações em `main` é resumida de onde parou.