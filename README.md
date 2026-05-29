# Noos

> "The Omnissiah directs our footsteps along the path of knowledge." — Techpriest Yaffel, Soylens Viridians for the Machine-Spirit

## Sumário

- [Introdução](#introdução)
- [Objetivo da Linguagem](#objetivo-da-linguagem)
- [Arquitetura Geral do Compilador](#arquitetura-geral-do-compilador)
- [Pré-processamento](#pré-processamento)
- [Análise Léxica](#análise-léxica)
  - [Palavras reservadas](#palavras-reservadas)
  - [Tipos primitivos](#tipos-primitivos)
  - [Operadores](#operadores)
  - [Delimitadores](#delimitadores)
  - [Literais](#literais)
  - [Identificadores](#identificadores)
- [Análise Sintática](#análise-sintática)
- [Gramática da linguagem](#gramática-da-linguagem)
- [Tokens Reconhecidos](#tokens-reconhecidos)
- [Exemplos de programas](#exemplos-de-programas)
  - [Exemplos válidos](#exemplos-válidos)
  - [Exemplos inválidos](#exemplos-inválidos)
- [Estrutura do Projeto](#estrutura-do-projeto)
- [Como Compilar e Executar](#como-compilar-e-executar)
  - [Linux / WSL2](#linux--wsl2)
  - [Windows (PowerShell)](#windows-powershell)
- [Tratamento de Erros](#tratamento-de-erros)
  - [Estrutura das Mensagens de Erro](#estrutura-das-mensagens-de-erro)
  - [Erros Léxicos](#erros-léxicos)
  - [Erros Sintáticos](#erros-sintáticos)
  - [Erros Semânticos](#erros-semânticos)
  - [Erros de Geração de Código](#erros-de-geração-de-código)
  - [Estratégia de Recuperação](#estratégia-de-recuperação)

## Introdução
O Adeptus Mechanicus, também conhecido como Mechanicum em períodos anteriores da cronologia de Warhammer 40.000, é uma das principais organizações do Império da Humanidade dentro do universo fictício criado pela Games Workshop. Originário do planeta-forja Marte, o Mechanicus atua como a principal autoridade tecnológica da humanidade, sendo responsável pela preservação, manutenção e desenvolvimento de conhecimento técnico em uma era marcada pela decadência científica e pela constante guerra interestelar.

Diferentemente de uma instituição científica tradicional, o Adeptus Mechanicus combina engenharia, religião e dogma. Seus membros acreditam que todo conhecimento tecnológico possui caráter sagrado e que as máquinas contêm uma essência espiritual conhecida como Machine Spirit (Espírito da Máquina). Dessa forma, operações de manutenção, ativação e fabricação de equipamentos frequentemente assumem a forma de rituais litúrgicos, orações e cerimônias tecnorreligiosas.

Os principais integrantes da organização são os chamados Tech-Priests (Tecno-sacerdotes), indivíduos que dedicam suas vidas ao culto da máquina e à busca pelo conhecimento. Esses sacerdotes substituem progressivamente partes do próprio corpo por implantes cibernéticos, próteses mecânicas e augmentações neurais, acreditando que a carne humana é fraca e imperfeita quando comparada à precisão das máquinas.

Além de sua função religiosa, os Tech-Priests exercem papéis fundamentais na operação tecnológica do Império. São responsáveis pela manutenção de naves espaciais, armamentos, sistemas industriais e até inteligências artificiais limitadas. Também atuam na recuperação de tecnologias ancestrais perdidas, tratando fragmentos de conhecimento técnico como relíquias sagradas.

A linguagem Noos, desenvolvida para a disciplina de Compiladores da Pontifícia Universidade Católica de Goiás, foi inspirada na estética tecnorreligiosa do Adeptus Mechanicus. Sua sintaxe utiliza terminologia derivada do latim pseudo-eclesiástico presente no universo de Warhammer 40.000, incorporando palavras associadas a rituais, transmissão de conhecimento e lógica mecanizada. Elementos como ritus, codex, transmit e vox refletem diretamente a linguagem litúrgica utilizada pelos Tech-Priests, buscando criar uma identidade temática consistente entre o design da linguagem e o universo que a inspirou.

## Objetivo da Linguagem

A linguagem Noos foi desenvolvida com fins educacionais no contexto da disciplina de Compiladores, tendo como principal objetivo aplicar, de forma prática, os conceitos relacionados à análise léxica, análise sintática, gramáticas livres de contexto e processamento de linguagens formais.

A proposta do projeto consiste na criação de uma linguagem procedural própria, inspirada esteticamente no universo de Warhammer 40.000, mais especificamente na facção Adeptus Mechanicus. A linguagem utiliza palavras-chave e estruturas sintáticas derivadas da terminologia tecnorreligiosa presente nesse universo fictício, buscando criar uma identidade temática consistente sem comprometer a clareza sintática e a legibilidade do código.

Além do aspecto temático, a linguagem foi projetada para possuir uma estrutura simples e adequada ao desenvolvimento incremental de um compilador. O projeto contempla desde o pré-processamento do código-fonte até a análise sintática e semântica, permitindo a implementação das principais etapas clássicas de um compilador moderno.

A linguagem Noos possui tipagem estática e sintaxe inspirada em linguagens imperativas tradicionais, especificamente BASIC e C, oferecendo suporte para:

- declaração de variáveis;
- tipos primitivos inteiros, reais, booleanos e strings;
- arrays unidimensionais;
- estruturas condicionais;
- estruturas de repetição;
- funções com parâmetros e retorno;
- operadores aritméticos, relacionais e lógicos;
- impressão de valores em console.

O projeto foi concebido visando transpilação para C++, evitando a necessidade de lidar com linguagens de nível mais baixo.

Do ponto de vista técnico, a linguagem foi projetada para ser compatível com analisadores sintáticos do tipo LALR(1), possibilitando a utilização do GNU Bison na construção do parser. A gramática foi cuidadosamente estruturada para evitar ambiguidades e conflitos comuns em gramáticas de linguagens imperativas, especialmente relacionados à precedência de operadores, delimitação de blocos e diferenciação entre identificadores, chamadas de função e acesso a arrays.

Dessa forma, o projeto busca unir contextualização temática, aplicação prática de teoria de compiladores e implementação incremental de ferramentas de processamento de linguagens formais.

## Arquitetura Geral do Compilador

O compilador da linguagem Noos foi desenvolvido utilizando a linguagem C++ e segue a arquitetura clássica de compiladores dividida em múltiplas etapas de processamento.

O fluxo geral do compilador pode ser descrito da seguinte forma:

1. Leitura do código-fonte;
2. Pré-processamento;
3. Análise léxica;
4. Análise sintática;
5. Construção da Árvore Sintática Abstrata (AST);
6. Análise semântica;
7. Geração de código C++;
8. Compilação do código gerado.

Cada etapa é responsável por transformar progressivamente o código-fonte escrito em Noos em uma representação intermediária mais estruturada e validada.

O pré-processamento realiza a limpeza inicial do código, removendo comentários e tratando espaços em branco desnecessários, de forma explicita.

A análise léxica é responsável por identificar lexemas e convertê-los em tokens válidos da linguagem. Nesta etapa são reconhecidos identificadores, palavras reservadas, operadores, delimitadores e literais.

A análise sintática utiliza uma gramática livre de contexto compatível com parsers LALR(1), sendo implementada com auxílio do GNU Bison. O parser valida se a sequência de tokens produzida pelo analisador léxico respeita as regras sintáticas da linguagem.

Após a validação sintática, o compilador constrói uma Árvore Sintática Abstrata, utilizada pelas etapas posteriores de análise semântica e geração de código.

A análise semântica realiza verificações relacionadas ao significado do programa.

Por fim, o compilador realiza a transpilação do código Noos para código C++, permitindo utilizar o compilador g++ como etapa final de geração do executável.

## Pré-processamento
Tendo apresentado a idea por trás da linguagem e sua finalidade, vamos apresentar a fase de pré-processamento e os principais comandos da linguagem.

A primeira etapa do compilador consiste no pré-processamento do código-fonte da linguagem Noos.

O objetivo desta etapa é preparar o texto de entrada para as fases posteriores do compilador, simplificando o processo de análise léxica e reduzindo ambiguidades causadas por elementos irrelevantes para a sintaxe da linguagem.

As principais operações realizadas durante o pré-processamento incluem:

* remoção de comentários de linha;
* normalização de espaços em branco;
* separação lógica de linhas;
* tratamento inicial de caracteres inválidos.

A linguagem Noos suporta comentários de linha utilizando o símbolo `--`

Exemplo:

```noos
-- Comentário
```

Durante o pré-processamento, os comentários são removidos completamente antes da etapa de tokenização.

Os espaços em branco não possuem significado sintático na linguagem, sendo utilizados apenas para legibilidade do código. Dessa forma, múltiplos espaços consecutivos são ignorados pelo analisador léxico, tais qual espaços no início e fim de linhas.

Após o pré-processamento, o código-fonte é convertido em uma sequência limpa de caracteres, pronta para ser analisada pelo scanner léxico.

Os principais comandos da linguagem são:

* `verify` inicia uma estrutura de controle
* `fallback` equivalente ao `else`
* `cycle` inicia um loop `while`
* `codex` define o ponto de entrada do programa

## Análise Léxica

A análise léxica é responsável por converter o código-fonte da linguagem Noos em uma sequência estruturada de tokens.

O analisador léxico foi implementado manualmente em C++, utilizando autômatos finitos determinísticos para reconhecimento dos diferentes padrões léxicos da linguagem.

Cada token identificado possui:

* tipo;
* lexema;
* linha de ocorrência;
* coluna de ocorrência.

Essa informação é utilizada posteriormente pelo analisador sintático para geração de mensagens de erro mais precisas.

Os principais grupos de tokens reconhecidos pela linguagem incluem:

### Palavras reservadas

| Palavra   | Função                |
| --------- | --------------------- |
| `ritus`   | declaração de função  |
| `codex`   | início do programa    |
| `vox`     | impressão em console  |
| `verify`      | estrutura condicional |
| `fallback`  | bloco else            |
| `cycle`   | laço de repetição     |
| `transmit` | retorno de função     |
| `cojunction` | operador de conjunção     |
| `divergence` | operador de disjunção     |

### Tipos primitivos

| Tipo      | Descrição             |
| --------- | --------------------- |
| `numerus` | números inteiros      |
| `flux`    | números reais         |
| `veritas` | valores lógicos       |
| `scriptum`  | cadeias de caracteres |

### Operadores

#### Operadores aritméticos

```text
+  -  *  /
```

#### Operadores relacionais

```text
==  !=  <  >  <=  >=
```

#### Operadores lógicos

```text
conjunction divergence  !
```

### Delimitadores

```text
( ) { } [ ] ,
```

### Literais

A linguagem suporta:

* inteiros;
* números reais;
* strings delimitadas por aspas;
* valores booleanos (`verum` e `falsum`).

### Identificadores

Os identificadores devem:

* iniciar com letra;
* conter apenas letras, números e `_`;
* não utilizar palavras reservadas.

Exemplos válidos:

```text
valor
total_
machineSpirit42
```

Exemplos inválidos:

```text
_total
42valor
ritus
valor-total
```

## Análise Sintática

A análise sintática da linguagem Noos foi implementada utilizando GNU Bison, com uma gramática livre de contexto compatível com parsers LALR(1).

O objetivo desta etapa é verificar se a sequência de tokens produzida pelo analisador léxico respeita as regras sintáticas da linguagem.

A gramática da linguagem define:

* estrutura do programa;
* declaração de funções;
* comandos;
* expressões;
* chamadas de função;
* estruturas condicionais;
* estruturas de repetição.

Exemplo simplificado de produção gramatical:

O parser realiza análise bottom-up utilizando tabelas LALR(1), permitindo detectar erros sintáticos de maneira eficiente.

Exemplo de erro sintático tratado:

```text
[ERROR::PARSE] :: MACHINE_SPIRIT_CONFUSED

SIGNAL :: syntax error, unexpected identifier at line 4 and column 20

RECOVERY :: ENSURE CORRECT SYNTAX RITUALS
```

Além da validação sintática, o parser constrói uma Árvore Sintática Abstrata (AST), utilizada pelas etapas posteriores do compilador.

A AST representa a estrutura lógica do programa de maneira hierárquica, facilitando:

* análise semântica;
* verificação de tipos;
* geração de código;
* otimizações futuras.

Após a análise sintática e semântica, o compilador realiza a transpilação do código Noos para C++.


## Gramática da linguagem
A gramática também pode ser verificada no arquivo `parser.y`

### Estrutura Principal
program =
    CODEX ,
    INITIATE ,
    NEWLINE ,
    global_sequence ,
    END_CODEX ,
    END_OF_FILE ;
Sequências
global_sequence =
    {
        NEWLINE
        | statement , NEWLINE
        | function_declaration , NEWLINE
    } ;

statement_sequence =
    {
        NEWLINE
        | statement , NEWLINE
    } ;
Statements
statement =
      variable_declaration
    | assignment_statement
    | print_statement
    | function_call
    | return_statement
    | if_statement
    | while_statement ;
### Declaração de Variáveis
variable_declaration =
      value_type , IDENTIFIER
    | value_type , IDENTIFIER , ASSIGN , expression
    | value_type ,
      IDENTIFIER ,
      LBRACK ,
      INTEGER ,
      RBRACK
    | value_type ,
      IDENTIFIER ,
      LBRACK ,
      INTEGER ,
      RBRACK ,
      ASSIGN ,
      array_initializer ;

array_initializer =
    LBRACE ,
    [ expression_list ] ,
    RBRACE ;

expression_list =
    expression ,
    { COMMA , expression } ;
### Atribuição
assignment_statement =
      IDENTIFIER , ASSIGN , expression
    | IDENTIFIER ,
      LBRACK ,
      expression ,
      RBRACK ,
      ASSIGN ,
      expression ;
### Impressão
print_statement =
    PRINT ,
    LPAR ,
    expression ,
    RPAR ;
### Funções
function_declaration =
    RITUS ,
    return_type ,
    IDENTIFIER ,
    LPAR ,
    [ parameter_list ] ,
    RPAR ,
    INITIATE ,
    NEWLINE ,
    statement_sequence ,
    END_RITUS ;

parameter_list =
    parameter ,
    { COMMA , parameter } ;

parameter =
      value_type , IDENTIFIER
    | value_type , IDENTIFIER , LBRACK , RBRACK ;
### Estruturas de Controle
if_statement =
    IF ,
    expression ,
    NEWLINE ,
    statement_sequence ,
    [ else_clause ] ,
    END_IF ;

else_clause =
    ELSE ,
    NEWLINE ,
    statement_sequence ;

while_statement =
    CYCLE ,
    expression ,
    NEWLINE ,
    statement_sequence ,
    END_CYCLE ;
### Return
return_statement =
    RETURN ,
    [ expression ] ;
### Chamada de Função
function_call =
    IDENTIFIER ,
    LPAR ,
    [ argument_list ] ,
    RPAR ;

argument_list =
    expression ,
    { COMMA , expression } ;
### Expressões
expression =
    logical_or_expression ;

logical_or_expression =
    logical_and_expression ,
    { OR , logical_and_expression } ;

logical_and_expression =
    equality_expression ,
    { AND , equality_expression } ;

equality_expression =
    relational_expression ,
    { ( EQ | NEQ ) , relational_expression } ;

relational_expression =
    additive_expression ,
    { ( GT | LT | GTE | LTE ) , additive_expression } ;

additive_expression =
    multiplicative_expression ,
    { ( PLUS | MINUS ) , multiplicative_expression } ;

multiplicative_expression =
    unary_expression ,
    { ( MULT | DIV ) , unary_expression } ;

unary_expression =
      primary_expression
    | MINUS , unary_expression
    | NOT , unary_expression ;
### Expressões Primárias
primary_expression =
      INTEGER
    | FLOAT
    | STRING
    | TRUE
    | FALSE
    | IDENTIFIER
    | IDENTIFIER ,
      LPAR ,
      [ argument_list ] ,
      RPAR
    | IDENTIFIER ,
      LBRACK ,
      expression ,
      RBRACK
    | LPAR ,
      expression ,
      RPAR ;
### Tipos
return_type =
      value_type
    | value_type , LBRACK , RBRACK
    | VOID ;

value_type =
      TYPE_INT
    | TYPE_FLOAT
    | TYPE_BOOLEAN
    | TYPE_STRING ;

# Tokens Reconhecidos

A linguagem CODEX utiliza palavras-chave inspiradas em terminologia latina para representar estruturas fundamentais da linguagem, incluindo controle de fluxo, tipos primitivos, definição de funções e operadores lógicos.

A tabela abaixo apresenta os tokens atualmente reconhecidos pelo analisador léxico.

| Lexema            | Token          | Descrição                               |
| ----------------- | -------------- | --------------------------------------- |
| `codex`           | `CODEX`        | Marca o início do programa principal    |
| `ritus`           | `RITUS`        | Declaração de função                    |
| `cycle`           | `CYCLE`        | Estrutura de repetição                  |
| `verify`          | `IF`           | Estrutura condicional                   |
| `fallback`        | `ELSE`         | Bloco alternativo do condicional        |
| `initiate`        | `INITIATE`     | Início de bloco                         |
| `transmit`        | `RETURN`       | Retorno de função                       |
| `numerus`         | `TYPE_INT`     | Tipo inteiro                            |
| `flux`            | `TYPE_FLOAT`   | Tipo de ponto flutuante                 |
| `veritas`         | `TYPE_BOOLEAN` | Tipo booleano                           |
| `scriptum`        | `TYPE_STRING`  | Tipo textual                            |
| `verum`           | `TRUE`         | Valor booleano verdadeiro               |
| `falsum`          | `FALSE`        | Valor booleano falso                    |
| `vox`             | `PRINT`        | Comando de impressão                    |
| `codexterminate`  | `END_CODEX`    | Finalização do programa                 |
| `ritusterminate`  | `END_RITUS`    | Finalização de função                   |
| `verifyterminate` | `END_IF`       | Finalização de estrutura condicional    |
| `cycleterminate`  | `END_CYCLE`    | Finalização de estrutura de repetição   |
| `conjunction`     | `AND`          | Operador lógico AND                     |
| `divergence`      | `OR`           | Operador lógico OR                      |
| `nullrite`        | `VOID`         | Tipo sem retorno                        |
| `=`               | `ASSIGN`       | Operador de atribuição                  |
| `+`               | `PLUS`         | Operador de soma                        |
| `-`               | `MINUS`        | Operador de subtração                   |
| `*`               | `MULT`         | Operador de multiplicação               |
| `/`               | `DIV`          | Operador de divisão                     |
| `==`              | `EQ`           | Operador relacional de igualdade        |
| `!=`              | `NEQ`          | Operador relacional de diferença        |
| `>`               | `GT`           | Operador relacional maior que           |
| `<`               | `LT`           | Operador relacional menor que           |
| `>=`              | `GTE`          | Operador relacional maior ou igual      |
| `<=`              | `LTE`          | Operador relacional menor ou igual      |
| `!`               | `NOT`          | Operador lógico de negação              |
| `(`               | `LPAR`         | Delimitador de abertura de parênteses   |
| `)`               | `RPAR`         | Delimitador de fechamento de parênteses |
| `[`               | `LBRACK`       | Delimitador de abertura de colchetes    |
| `]`               | `RBRACK`       | Delimitador de fechamento de colchetes  |
| `{`               | `LBRACE`       | Delimitador de abertura de chaves       |
| `}`               | `RBRACE`       | Delimitador de fechamento de chaves     |
| `,`               | `COMMA`        | Separador de argumentos e elementos     |
| `\n`              | `NEWLINE`      | Quebra de linha                         |
| `[A-Za-z][A-Za-z0-9_]*`              | `IDENTIFIER`      | Identificador                         |


## Exemplos de programas

## Exemplos válidos
O programa mais simples que podemos escrever simplesmente imprime uma mensagem na tela:
```Noos
codex initiate
    vox("Hail the omnissaiah")
codexterminate
```
Cuja saída é 
```Text
Hail the omnissaiah
```

Podemos dar um exemplo mais interessante, como essa implementação do algoritmo Selection Sort:
```Noos
codex initiate
    numerus arr[5] = {64, 25, 12, 22, 11}

    numerus i = 0
    numerus j
    numerus min_idx
    numerus aux

    cycle i < 4
        j = i + 1
        min_idx = i
        cycle j < 5
            verify arr[j] < arr[min_idx]
                min_idx = j
            verifyterminate
            j = j + 1
        cycleterminate

        aux = arr[i]
        arr[i] = arr[min_idx]
        arr[min_idx] = aux
        i = i + 1
    cycleterminate

    -- PT: Imprimimos resultados formatados
    -- EN: Print formatted results
    vox("{")
    vox(arr[0])
    i = 1
    cycle i < 5
        vox(", ")
        vox(arr[i])
        i = i + 1
    cycleterminate
    vox("}")
    vox("\n")
codexterminate
```
Cuja saída é:
```Text
{11, 12, 22, 25, 64}
```

### Exemplos inválidos

A linguagem detecta erros semânticos e os reporta com mensagens temáticas antes de gerar qualquer executável.

**Erro de tipo — atribuição de `flux` a `numerus`:**

```Noos
codex initiate
    numerus contador = 3.14
    vox(contador)
    vox("\n")
codexterminate
```

Erro gerado:

```text
[ERROR::SEMA] :: MACHINE_SPIRIT_HERETICAL

SIGNAL :: type mismatch in initializer of 'contador' at line 2 and column 19

RECOVERY :: REVIEW YOUR RITES OF DECLARATION
```

**Erro de variável não declarada:**

```Noos
codex initiate
    numerus resultado = base * altura
    vox(resultado)
    vox("\n")
codexterminate
```

Erros gerados:

```text
[ERROR::SEMA] :: MACHINE_SPIRIT_HERETICAL

SIGNAL :: undeclared variable 'base' at line 2 and column 27

RECOVERY :: REVIEW YOUR RITES OF DECLARATION

[ERROR::SEMA] :: MACHINE_SPIRIT_HERETICAL

SIGNAL :: undeclared variable 'altura' at line 2 and column 36

RECOVERY :: REVIEW YOUR RITES OF DECLARATION
```

O compilador continua a análise após o primeiro erro e reporta todos os problemas encontrados em uma única execução.

# Tratamento de Erros

A linguagem Noos possui mecanismos de detecção e sinalização de erros nas diferentes etapas do processo de compilação, incluindo análise léxica, análise sintática e análise semântica.

As mensagens de erro foram projetadas para fornecer informações detalhadas ao usuário, incluindo:

* categoria do erro;
* descrição do problema;
* linha e coluna de ocorrência;
* possível ação corretiva.

O sistema de mensagens segue uma estética inspirada no universo Adeptus Mechanicus, mantendo consistência temática com a linguagem.

## Estrutura das Mensagens de Erro

Todas as mensagens seguem o formato geral:

```text
[ERROR::<FASE>] :: <CLASSIFICAÇÃO>

SIGNAL :: <descrição detalhada> at line <linha> and column <coluna>

RECOVERY :: <possível solução>
```

Onde:

* `<FASE>` identifica a etapa do compilador;
* `<CLASSIFICAÇÃO>` representa o tipo específico do erro;
* `SIGNAL` descreve o problema encontrado, incluindo a linha e coluna de ocorrência;
* `RECOVERY` sugere uma possível correção.



## Erros Léxicos

Os erros léxicos ocorrem durante a etapa de tokenização do código-fonte, quando o analisador léxico encontra símbolos ou padrões inválidos.

Os principais erros léxicos tratados incluem:

* caracteres desconhecidos;
* strings não finalizadas;
* números malformados;
* identificadores inválidos;
* símbolos ilegais.

### Exemplo

Código:

```Noos
numerus valor = 10 @ 2
```

Erro gerado:

```text
[ERROR::LEX] :: MACHINE_SPIRIT_AGITATED

SIGNAL :: UNRECOGNIZED TOKEN @ at line 1 and column 22

RECOVERY :: ENSURE CORRECT RITES OF AWAKENING
```



## Erros Sintáticos

Os erros sintáticos ocorrem quando a sequência de tokens não respeita as regras definidas pela gramática da linguagem.

Esses erros são detectados pelo parser LALR(1) implementado com GNU Bison.

Os principais erros sintáticos incluem:

* ausência de delimitadores;
* comandos incompletos;
* blocos não finalizados;
* uso incorreto de expressões;
* estruturas condicionais inválidas.

### Exemplo

Código:

```Noos
verify x >
    vox("invalid")
verifyterminate
```

Erro gerado:

```text
[ERROR::PARSE] :: MACHINE_SPIRIT_CONFUSED

SIGNAL :: syntax error, unexpected newline, expecting expression at line 1 and column 10

RECOVERY :: ENSURE CORRECT SYNTAX RITUALS
```



## Erros Semânticos

Os erros semânticos ocorrem após a construção da AST, durante a validação lógica do programa.

Nessa etapa, o compilador verifica:

* declaração prévia de variáveis;
* compatibilidade de tipos;
* validade de chamadas de função;
* quantidade de argumentos;
* retornos compatíveis com o tipo declarado;
* escopo de identificadores.

### Exemplo

Código:

```Noos
x = 10
```

Erro gerado:

```text
[ERROR::SEMA] :: MACHINE_SPIRIT_HERETICAL

SIGNAL :: undeclared variable 'x' at line 1 and column 1

RECOVERY :: REVIEW YOUR RITES OF DECLARATION
```


## Erros de Geração de Código

Os erros de geração de código ocorrem após a análise semântica, quando o compilador transpila o código Noos para C++ e invoca o `g++` para produzir o executável final. Se a compilação do código gerado falhar, o compilador reporta o erro e sugere a inspeção do C++ gerado.

### Exemplo

Erro gerado:

```text
[ERROR::CODEGEN] :: MACHINE_SPIRIT_BROKEN

SIGNAL :: C++ compilation failed

RECOVERY :: USE --emit-cpp TO INSPECT THE GENERATED CODE
```
---

## Estratégia de Recuperação

O compilador utiliza estratégias simples de recuperação de erro visando permitir a continuação parcial da análise sempre que possível.

Durante a análise sintática, o parser tenta sincronizar a leitura após encontrar tokens delimitadores importantes, como:

* quebras de linha;
* encerramentos de bloco;
* delimitadores de estruturas.

Essa abordagem permite reportar múltiplos erros em uma única execução do compilador, facilitando o processo de depuração do código-fonte.

# Estrutura do Projeto

```
Noos/
├── lexer.cpp / lexer.h          ← Analisador léxico (DFA com tabelas)
├── token.h                      ← Enum de tipos de token
├── parser.y                     ← Gramática formal (fonte Bison)
├── parser.cpp / parser.hh       ← Parser gerado pelo Bison
├── lexer_bridge.cpp / .h        ← Adaptador entre lexer e parser
├── ast.h / ast.cpp              ← Nós da Árvore Sintática Abstrata
├── type.h                       ← Sistema de tipos da linguagem
├── sema/
│   ├── symbol.h                 ← Definição de símbolo (variável, função)
│   ├── scope.h / scope.cpp      ← Tabela de símbolos com escopos
│   └── analyzer.h / analyzer.cpp← Análise semântica
├── codegen.h / codegen.cpp      ← Transpilação para C++
├── main.cpp                     ← Ponto de entrada do compilador
├── Makefile                     ← Build do projeto
└── examples/                    ← Programas de exemplo em Noos (.noos)
```

# Como Compilar e Executar

## Pré-requisitos

* `g++` com suporte a C++17
* `make`

## Linux / WSL2

Na raiz do repositório, execute:

```bash
make && make install
```

Isso gera o executável `noos` em `/usr/local/bin`.

## Windows (PowerShell)

### 1. Instalar o MSYS2

Baixe e instale o [MSYS2](https://www.msys2.org/) ou use o winget:

```powershell
winget install MSYS2.MSYS2
```

### 2. Instalar g++ e make

Abra o terminal **MSYS2 UCRT64** e execute:

```bash
pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-make
```

### 3. Adicionar ao PATH do Windows

No PowerShell, execute uma vez:

```powershell
[Environment]::SetEnvironmentVariable("PATH", $env:PATH + ";C:\msys64\ucrt64\bin", "User")
```

Feche e reabra o PowerShell para o PATH ser atualizado.

### 4. Compilar e instalar

Na raiz do repositório, execute:

```powershell
make && make install
```

> **Nota:** `&&` requer PowerShell 7+. Para versões anteriores use `make; if ($?) { make install }`.

Isso gera `noos.exe` e instala em `%LOCALAPPDATA%\bin`.

### 5. Adicionar o diretório de instalação ao PATH

Execute uma vez no PowerShell:

```powershell
[Environment]::SetEnvironmentVariable("PATH", $env:PATH + ";$env:LOCALAPPDATA\bin", "User")
```

Feche e reabra o PowerShell. Agora o comando `noos` estará disponível globalmente.

## Compilando um programa Noos

```bash
noos <arquivo.noos>
```

Então gera um executável com o mesmo nome do arquivo, que pode ser executado diretamente:

```bash
./<arquivo>          # Linux / WSL2
.\<arquivo>.exe      # Windows
```

## Flags opcionais

| Flag | Efeito |
|---|---|
| `--dump-tokens` | Imprime os tokens reconhecidos pelo analisador léxico |
| `--dump-ast` | Imprime a Árvore Sintática Abstrata construída pelo parser |
| `--no-sema` | Pula a análise semântica |
| `--emit-cpp` | Imprime o código C++ gerado em vez de compilá-lo |

Exemplo — inspecionar a árvore sintática abstrata durante a compilação:

```bash
noos examples/countdown.noos --dump-ast
```