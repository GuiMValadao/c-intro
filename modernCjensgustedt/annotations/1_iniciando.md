# **Capítulo 1 - Iniciando**

Esta seção trata sobre:
* Introdução à programação imperativa
* Compilando e executando códigos

Programar em C trata-se de fazer o computador executar tarefas específicas. Um programa em C faz isso dando ordens, o que leva ao termo programação imperativa. Para começar, vamos observar o primeiro programa, 'getting-started'.

## Programação imperativa

Você pode observar que o código contém palavras como `main`, `include`, `for` e outras que estão distribuídas e coloridas de maneira peculiar, misturadas com caracteres estranhos, números e texto que parece inglês comum. É projetado para fornecer uma ligação entre nós, programadores humanos, e uma máquina, o computador, de modo que possamos dizê-lo o que fazer dando 'ordens'.

No livro, além da linguagem de programação C também é usado algum vocabulário de um dialeto em inglês, 'jargão C', que ajuda a conversar sobre C. Não será possível, imediatamente,explicar cada termo na primeira vez que aparecem. Mas todos são explicados uma vez, estão indexados, de modo que pode-se pular para a explicação do jargão em qualquer momento.

O resultado exibido no terminal após aexecução do programa 'getting-started.exe' é:

element 0 is 9,         its square is 81
element 1 is 2.9,       its square is 8.41
element 2 is 0,         its square is 0
element 3 is 7e-05,     its square is 4.9e-09
element 4 is 3e+25,     its square is 9e+50

É fácil identificar as partes do texto no programa getting-started.c que o programa exibe(*prints* no jargão C): a parte da linha 17 entre aspas. A ação ocorre entre essa linha e a linha 20. C chama isso *declaração*(statement), o que é um nome um pouco equivocado (misnomer). Outras linguagens usam o termo *instrução*, que descreve melhor o propósito. Em particular, essa declaração é uma *chamada* a uma *função* nomeada `printf`. 

A função printf recebe 4 *argumentos* cercados por parênteses:

* O texto curioso (entre aspas) é um *string literal* que serve como um *formato* para a saída. Dentro do texto tem três marcadores (*especificadores de formato*) que indicam as posições na saída onde os números devem ser inseridos. Estes marcadores iniciam com o caractere %. Este formato também contém alguns *caracteres de escape* especiais que iniciam com contrabarra: \t e \n.

* Depois do caractere vírgula, tem a palavra de uma letra `i`. A coisa que `i` representa será exibida no lugar do primeiro especificador de formato, `%zu`.

* Outra vírgula separa o próximo argumento, `A[i]`. A coisa representada por ele será exibida no lugar do segundo especificador, `%g`.

* Por fim, novamente separado por vírgula, aparece `A[i] * A[i]`, o último `%g`.

O significado destes argumentos será explorado posteriormente. Por hora, identificamos o propósito principal do programa (exibir algumas linhas no terminal) e aprendemos que ele 'ordena' que a função `printf` cumpra esse propósito. O resto é apenas um pouco de *açúcar* para especificar quais e quantos números serão exibidos.

## Compilando e executando

Como mostrado na subseção anterior, o texto do programa expressa o que queremos que nosso computador faça. Dessa forma, é apenas outra peça do texto que escrevemos e armazenamos em algum lugar do disco (HD/SSD), mas o computador não entende esse texto. Existe um programa especial, chamado *compilador*, que traduz o texto C para algo que a máquina entende: **código binário** ou **executável**. Com o que aquele programa traduzido se parece e como esta tradução é feita é um assunto muito complicado para o escopo do livro. No momento, não é necessário entender a fundo como isto é feito pois já temos a ferramenta que realiza isso por nós, o **compilador** (C é uma linguagem de programação compilada).

O nome do compilador e seus argumentos de linha de comando dependem bastante da *plataforma* na qual o programa estará sendo executado. Isto ocorre por uma razão simples: o código binário resultante é *dependente da plataforma*, ou seja, sua forma e detalhes dependem do computador em que se quer executá-lo. Na verdade, esta é uma das razões da existência de C: ela fornece um nível de abstração para todas as linguagens específicas de máquina diferentes (geralmente chamada *linguagem assembly*). Um programa C correto é portável(transferível) entre diferentes plataformas.

No livro, é colocado esforço na escrita de programas C 'corretos' que garantem a portabilidade. Infelizmente, existem algumas plataformas que alegam ser C mas não conformam com os padrões mais recentes, e algumas plataformas em conformidade aceitam programas incorretos ou fornecem extensões para o C padrão que não são amplamente portáveis. Assim, executar e testar um programa em uma única plataforma não garante a portabilidade.

É responsabilidade do compilador garantir que o programa em C seja executado corretamente no computador, telefone, até mesmo na geladeira. Dito isso, em um sistema POSIX (como Linux ou macOS), há boa chance que programas como c99 ou c17 estejam presente pois eles são, na verdade, compiladores C. Poderia tentar compilar o programa usando o seguinte comando:

>`> c17 -Wall -o getting-started getting-started.c -lm`

> **No meu computador executei com o seguinte comando:**
>> **`> cl -Wall -o getting-started getting-started.c`**
> **Recebi um aviso que -o seria depreciado e -lm não é um comando reconhecido (no Windows); -o serve para definir o nome do executáve, no Windows usa -Fe<nome_saida>, por exemplo -Ferenomear**

O compilar deveria fazer o trabalho dele sem reclamar e retornar um arquivo executável chamado getting-started na pasta atual. Na linha de exemplo:
* `c17`(`cl`) é o programa compilador
* `-Wall` pede para nos avisar de qualquer coisa que julgue incomum
* `-o getting-started` diz para salvar a saída do compilador em um arquivo nomeado `getting-started`.
* `getting-started.c` é o nome do *arquivo fonte*, que contém o código C que escrevemos. Note que a extensão .c no fim do nome do arquivo refere-se à linguagem de programação C.
* `-lm` diz a acrescentar algumas funções numéricas padrões se necessário; precisaremos delas posteriormente.

Agora podemos executar o novo executável:
> `>./getting-started`
e devemos ver a mesma saída apresentada anteriormente. Isto é o que portável significa: onde quer que rode o programa, seu *comportamento* deveria permanecer o mesmo.

Se não tiver tido sorte e a compilação não funcionaou, terá de procurar o nome do compilador do sistema que estiver usando na documentação. Poderia até precisar instalar um compilador se não houver um disponível. Alguns nomes alternativos de compiladores incluem clang, gcc e icc.

Com o programa getting-started, fomos apresentados com um mundo ideal: um programa que funciona e produz o mesmo resultado em todas as plataformas. Infelizmente, quando estiver programando sozinho, frequentemente terá um programa que funciona apenas parcialmente e pode produzir resultados errados ou não confiáveis. Portanto, vamos olhar o programa `bad.c`, que é parecido com o anterior.

Ao rodar o compilador nesse programa, ele dará as seguintes informações de diagnóstico:

```
Microsoft (R) C/C++ Optimizing Compiler Versão 19.29.30159 para x64
Copyright (C) Microsoft Corporation. Todos os direitos reservados.

cl : Linha de comando warning D9035 : opção 'o' foi preterida e será removida em uma versão futura
bad.c
bad.c(1): warning C4255: 'main': nenhum protótipo de função fornecido: convertendo '()' para '(void)'
bad.c(12): warning C4013: 'printf' indefinido; assumindo extern retornando int
bad.c(17): warning C4098: 'main': função 'void' retornando um valor
D:\programacao\c-intro\modernCjensgustedt\programs\cap1\bad\bad.c(12) : warning C5045: O compilador inserirá a mitigação de espectro para carga de memória se a opção /Qspectre for especificada
D:\programacao\c-intro\modernCjensgustedt\programs\cap1\bad\bad.c(11) : observação: o intervalo 'i' do índice verificado por comparação nessa linha
D:\programacao\c-intro\modernCjensgustedt\programs\cap1\bad\bad.c(12) : observação: chamada a feeds nessa linha
Microsoft (R) Incremental Linker Version 14.29.30159.0
Copyright (C) Microsoft Corporation.  All rights reserved.

/out:bad.exe
/out:bad.exe
bad.obj
```

Alguns compiladores (GCC e o cl, usado por mim) ainda assim produzem um executável, outros (Clang) nem chegam a criar o executável após os erros encontrados. Foram retornados 3 diagnósticos: eles esperam um tipo de retorno diferente da função `main`; esperam a especificação de onde a função `printf` deve vir (como `#include <stdlib.h>` ou `#include <stdio.h>`); e detectam que o tipo de retorno da função main é incorreto para o especificado. Dependendo da plataforma, pode-se forçar o compilador e rejeitar programas que produzem tais diagnósticos. Para GCC, essa opção de linha-de-comando é -Werror, fazendo com que o GCC comporte-se igual ao Clang. 
> Para o compilador cl no Windows, em vez de -Werror, usa-se `-we<numero_erro>`, por exemplo `-we4255`.