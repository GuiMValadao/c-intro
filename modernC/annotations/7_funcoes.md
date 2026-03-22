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

## 7.1 Funções simples (pag 106)

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



