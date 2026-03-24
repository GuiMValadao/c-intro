# **Capítulo 7 - Funções**

Esta seção trata sobre:

* Uma introdução para funções simples
* Trabalhar com `main`
* Entender recursão

Já vimos formas diferentes de execução condicional em C. A razão para um possível 'pulo' para outra parte do código do programa (por exemplo, um ramo else) é uma decisão da hora de execução(run-time) que depende de dados do momento da execução. Esta seção inicia falando sobre formas *incondicionais* de transferir controle para outras partes co código.

Já usamos nos exemplos anteriores funções da biblioteca C padrão que fornecem recursos que não queríamos/podíamos implementar por nós mesmos naquele momento, como printf e strlen. A ideia é que uma função implemente um certo recurso uma única vez, e que possamos reutilizar aquele recurso em qualquer momento no código.

As principais razões motivando o conceito de funções são modularidade e fatorização de código:
    
* Funções evitam a repetição de código. Em particular, evitam erros que podem ser introduzidos por copiar e colar e economizam o esforço de precisar alterar múltiplos locais se modificar uma parte da funcionalidade. Assim, aumentam a legibilidade e facilitam a manutenção.
* A utilização de funções diminui tempo de compilação. Pois o código que será reutilizado será compilado apenas uma vez, e não em todas as vezes que for utilizado .
* Funções simplificam futuras reutilizações de código. Após extrairmos código em uma função que fornece certas funcionalidades, pode-se aplicar facilmente em outros locais que nem tínhamos imaginado de implementá-la.
* Funções fornecem interfaces claras. Elas especificam claramente tipos de entrada e saída dos argumentos que passam por ela.
* Funções fornecem uma forma natural de formular algoritmos que usam uma "pilha" de valores intermediários.

Além de funções, C tem outras formas de transferência de controle incondicional, usadas principalmente para lidar com condições de erros ou outras formas de exceções do fluxo de controle comum:

* exit, _Exit, quick_exit e abort terminam a execução do programa
* goto transfere controle dentro do corpo de uma função
* setjmp e longjmp podem ser usados para retornar incondicionalmente ao contexto que chamou
* Certos eventos no ambiente de execução ou chamadas à função raise podem levantar sinais que passam controle a uma função especializada, um signal handler.

## 7.1 Funções simples

Já vimos diversas funções e algumas declarações nos capítulos anteriores. Em todas elas, os parênteses tem um papel sintático importante. Eles são usados para declarações e definições de funções para encapsular a lista de declarações de parâmetros. Para chamadas de funçoes, elas guardam a lista de argumentos para aquela chamada concreta. Este papel sintático é similar às chaves de matrizes [].

Todas as funções vistas até aqui tinham um protótipo: sua declaração e definição, incluindo uma espécie de lista de parâmetros e um tipo de retorno. Para ver isso, vejamos novamente a função leapyear do listing 6.3:

```
bool leapyear(unsigned year) {
    return !(year % 4) && ((year % 100) || !(year % 400));
}
```

Uma declaração daquela função (sem uma definição), poderia ter a seguinte forma:

```
bool leapyear(unsigned year);
```

Alternativamente, poderíamos até omitir o nome do parâmetro e/ou acrescentar o *especificador de armazenamento* `extern`:

```
extern bool leapyear(unsigned);
```

O importante desse tipo de declaração é que o compilador veja o tipo do(s) argumento e do retorno. Existem duas convenções especiais que usam a palavra chave `void`:

* Se a função deve ser chamada sem parâmetros, a lista é substituída pela palavra chave void
* Se a função não retorna um valor, o tipo de retorno dado é void.

Tais protótipos ajudam o compilador em locais onde a função deve ser chamada. Ele apenas precisa saber sobre os parâmetros que a função espera.

*Todas as funções devem ter protótipos.*

Uma exceção a essa regra são funções que podem receber um número de parâmetros variável, como printf. Elas usam um mecanismo para lidar com parâmetros chamado uma lista de argumentos variável, que vem do cabeçalho <stdargs.h>. Veremos na seção 17.4.2 como isto funciona, mas este recurso deve ser evitado de qualquer modo.

Na implementação de uma função, devemos estar atentos que fornecemos valores de retorno a todas as funções que retornam um tipo não-void. Uma função pode possuir diversas declarações return.

Todos os returns de uma função devem ser consistentes com a declaração da função. Para uma função que espera um valor de retorno, todas as declarações return devem conter uma expressão; em funçõeos que não esperam tais valores, declarações return contendo expressões são erradas.

*Alcançar o final do corpo de uma função é equivalente a uma declaração return sem expressão. Isso só é possível para funções que retornam void.*

## 7.2 `main` é especial

A função main é o ponto de entrada do programa, com seu protótipo sendo obrigatório pelo padrão C, mas sua implementação sendo feita pelo programador. Por isso, deve obedecer algumas regras: 

* Primeiro, para cumprir diferentes necessidades, tem vários protótipos, um dos quais deve ser impementado. Dois deveriam sempre ser possíveis:

´´´
int main(void);
int main(int argc, char* argv[argc+1]);
´´´

Então, qualquer plataforma C pode fornecer outras interfaces. Duas variações são bastante comuns:

* Em algumas plataformas embarcadas (embedded) onde não se espera que main retorne ao sistema que a executa, o tipo de retorno pode ser void.
* Em muitas plataformas, um terceiro parâmetro pode das acesso ao "ambiente".

Não se deve depender da existência de coisas assim em outras plataformas. Se quer escrever código portável, fique com as duas formas "oficiais". Para elas, o valor de retorno int dá uma indicação ao sistema de execução se o programa executou corretamente: EXIT_SUCCESS ou EXIT_FAILURE indicam sucesso ou falha na execução do ponto de vista do programador. Eles são os únicos valores que funcionam em qualquer plataforma.

Além disso, existe uma exceção especial para `main`, pois ela não precisa ter uma declaração de retorno explícita. *Chegar ao final de main é o equivalente a um return com EXIT_SUCCESS.*

A função exit encerra o programa, encerrando a execução do programa exatamente como um return faria.. Seu protótipo é:

```
[[noreturn]] void exit(int status);
```

Também vemos que o protótipo de exit é especial pois tem um tipo void. Assim como uma declaração return, exit nunca falha. O atributo [[noreturn]] indica que a função nunca retorna ao ponto que a chamou (recurso do C23). Versões de C anteriores à 23 tinham a palavra chave _Noreturn e a macro noreturn, uma versão pretty-printed dela, que vinha com o cabeçalho stdnoreturn.h.

O segundo protótipo de main tem outro recurso: argv, o vetor de argumentos de comando de linha. Cada um de argv[i] para i = 0, ..., argc é um pointer similar aos encontrados anteriormente. Como uma primeira aproximação, pode-se pensar neles como strings.

Dos argumentos argv, dois possuem importância particular: argv[0] aponta para o nome da invocação do programa (não há uma regra, mas costuma ser o nome do executável), e argv[argc] é um pointer null. 

## 7.3 Recursão

Um recurso importante das funções é a encapsulação. Variáveis locais são apenas visíveis e vivas até sairmos da função, seja por um return explícito ou por que a execução sai do último braquete do corpo da função. Seus identificadores (nomes) não conflitam com outros identificadores similares em outras funções, e assim que saímos da função, tudo que ficou para trás é limpo. 

Ainda por cima, sempre que chamamos uma função, mesmo que já tenhamos chamado-a antes, um novo conjunto de variáveis locais (incluindo parâmetros de funções) é criado e inicializado como novo. Isto se mantém se chamamos uma nova função que ainda possui uma chamada ativa. Uma função que chama a si própria, direta ou indiretamente, é chamada recursiva. 

Esse tipo de função é crucial para o entendimento de funções em C. Elas demonstram e usam recursos primários do modelo de chamada de funções e são apenas completamente funcionais com tais recursos. Como primeiro exemplo, vejamos uma implementação do algoritmo de Euclides para computar o maior divisor comum(gcd) de dois números:


euclid.h
```
inline size_t gcd2(size_t a, size_t b) [[__unsequenced__]] {
    assert(a <= b);
    if (!a) return b;
    size_t r = b % a;
    return gcd2(r, a);
}
```

Esta função é curta e, aparentemente, fácil; ela faz algumas presunções sobre seus argumentos e, portanto, não é a interface completa de gcd {O atributo [[unsequenced]] será discutido na seção 16.3}. Mas, para entender como ela funciona, temos de entender completamente como funções funcionam e como transformamos declarações matemáticas em algoritmos.

Dados dois números inteiros a,b>0, o gcd é definido como o maior inteiro c > 0 que divide ambos a e b. Essa é a fórmula:

    gcd(a,b) = max{c ∈  | c|a e c|b}

Se também assumimos que a < b, pode ser mostrado que duas fórmulas recursivas são corretas:
    
    gcd(a,b) = gcd(a, b-a)
    gcd(a,b) = gcd(a, b % a)

Isto é, o gcs não é alterado se subtraímos o menor inteiro ou se substituímos o maior dos dois com o módulo do outro. Estas fórmulas tem sido usadas para calcular o gcd desde a matemática da Grácia antiga, sendo atribuídas comumente a Euclides, mas sendo conhecidas mesmo antes dele. O termo recursão para tais fórmulas (e derivado delas para funções) refere-se ao fato que o valor de um termo (aqui gcd(a, b)), é explicado ao usar o mesmo termo mas com valores diferentes (por exemplo, gcd(a, b-a)).

Nossa função C gcd2 usa a terceira equação acima. Primeiro, checa se uma pré-condição para a execução é satisfeita: se o primeiro argumento é menor ou igual ao segundo, com a macro assert de <assert.h>. Isto abortaria o programa com uma mensagem informativa se a função fosse chamada com argumentos que causassem com a condição fosse falsa. Em seguida, checa se a é zero, e se for, retorna b. Este é um passo importante em algoritmos recursivos, chamado condição base ou condição de término. A ausência dessa informação levaria a recursão infinita, com a função chamando si própria repetidamente até exaurir os recursos do sistema e quebrar(crash) o programa. Em seguida, computamos o resto r de b modulo a. Então, chamamos a função recursivamente com r e a, e o valor de retorno disso é retornado diretamente.

Para cada chamada recursiva, a aritmética modular garante que a pré-condição é sempre cumprida automaticamente. Para a chamada inicial, temos que garantir isso nós mesmos. A melhor forma de fazer isso é através de uma função diferentes, um *wrapper*:

```
inline size_t gcd(size_t a, size_t b) [[__unsequenced__]] {
    assert(a);
    assert(b);
    if (a < b)
        return gcd2(a, b);
    else
        return gcd2(b, a);
}
```

Isto evita a necessidade de checar a pré-condição em cada chamada recursiva: a macro assert pode ser desativada no objeto do arquivo de produção final.

Outro exemplo famoso de um definição recursiva de uma sequência de inteiros são os números de Fibonnacci, que surgiu pelo menos em torno de 200 a.C. em textos indianos. Pode ser definida como:

    F_1 = 1
    F_2 = 1
    F_i = F_i-1 + F_i-2         Para todo i > 2

    Seus primeiros elementos são 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 377, 610 e 987.

Com a razão dourada 
    
    𝜑 = (1 + √5)/ 2 = 1.61803...

Pode ser mostrado que, assintóticamente, F_n ≈ 𝜑^n / √5.

Assim, o crescimento de F_n é exponencial. Essa definição matemática pode ser traduzida de uma forma direta em uma função C:

```
size_t fib(size_t n)    [[__unsequenced__]] {
    if (n < 3)
        return 1;
    else
        return fib(n-1) + fib(n-2);
}
```

Novamente, primeiro é checada a condição de término, que é quando n é menor que três. Se for, retorna 1, se não, retorna a soma da própria função com os argumentos anterior(n-1) e antes do anterior(n-2). Implementada dessa forma, a computação dos números de Fibonnacci é bem lenta, sendo exponencial com n.

*Múltiplas recursões pode levar a tempo de computação exponencial.*

Par diminuir o tempo consumido, pode-se aumentar o gasto em memória, como um programa como:

```
/* Computa o número de Fibonnacci n com a ajuda de um cache que pode
    armazenar valores computados anteriormente */
size_t fibCacheRec(size_t n, size_t cache[static n]) {
    if (!cache[n-1]) {
        cache[n-1] = fibCacheRec(n-1, cache) + fibCacheRec(n-2, cache);
    }
    return cache[n-1];
}

size_t fibCache(size_t n) {
    if (n+1 <= 3>) return 1;
    /* Prepara uma VLA para armazenar os valores em cache */
#if __STDC_VERSION__ > 202311L
    /* Desde C23, VLA pode ser inicializada com default */
    size_t cache[n] = { };
#else
    size_t cache[n]; memset(cache, 0, n*sizeof(*cache));
#endif
    /* Inicialização não-trivial é substituída por atribuição */
    cache[0] = 1; cache[1] = 1;
    /* Chama a função recursiva */
    return fibCacheRec(n, cache);
}
```

Ao trocar armazenamento por tempo de computação, as chamadas recursivas são afetadas apenas pelos valores que ainda não foram computados. Assim, fibCache(i) tem um tempo de execução linear em n.