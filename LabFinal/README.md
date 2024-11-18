```c++
%{
// Reconhecedor de uma linguagem simplificada
#include <iostream>
#include "tokens.h"
#include "token.h"
using std::cout;

typedef union { 
    Token* token; 
} YYSTYPE; 

YYSTYPE yylval;

%}

%option noyywrap

delim    [ \t\n]
brancos {delim}+
letra    [A-Za-z]
digito   [0-9]
id       ({letra}|_){letra}*({letra}|{digito}|_)*
num      {digito}+(\.{digito}+)?(E[+-]?{digito}+)?

%%

{brancos}    ; // nenhuma ação e nenhum retorno
main        { yylval.token = new Token(MAIN, yytext); return MAIN; }

int         { yylval.token = new Token(INTEGER, yytext); return INTEGER; }
float       { yylval.token = new Token(FLOATING, yytext); return FLOATING; }
bool        { yylval.token = new Token(BOOLEAN, yytext); return BOOLEAN; }
true        { yylval.token = new Token(TRUE, yytext); return TRUE; }
false       { yylval.token = new Token(FALSE, yytext); return FALSE; }

while       { yylval.token = new Token(WHILE, yytext); return WHILE; }
if          { yylval.token = new Token(IF, yytext); return IF; }
else        { yylval.token = new Token(ELSE, yytext); return ELSE; }
do          { yylval.token = new Token(DO, yytext); return DO; }

{id}        { yylval.token = new Token(ID, yytext); return ID; }
{num}       { if (strchr(yytext, '.') || strchr(yytext, 'E') || strchr(yytext, 'e')) { yylval.token = new Token(FLOATING, yytext); return FLOATING; } else { yylval.token = new Token(INTEGER, yytext); return INTEGER; } }


";"         { yylval.token = new Token(';', yytext); return ';'; } 
"="         { yylval.token = new Token('=', yytext); return '='; }
"+"         { yylval.token = new Token('+', yytext); return '+'; } 
"-"         { yylval.token = new Token('-', yytext); return '-'; } 
"*"         { yylval.token = new Token('*', yytext); return '*'; } 
"/"         { yylval.token = new Token('/', yytext); return '/'; }

"!"         { yylval.token = new Token('!', yytext); return '!'; }
"=="        { yylval.token = new Token(EQ, yytext); return EQ; }
"!="        { yylval.token = new Token(NEQ, yytext); return NEQ; }
"<"         { yylval.token = new Token(LT, yytext); return LT; }
"<="        { yylval.token = new Token(LTE, yytext); return LTE; }
">"         { yylval.token = new Token(GT, yytext); return GT; }
">="        { yylval.token = new Token(GTE, yytext); return GTE; }
"&&"        { yylval.token = new Token(AND, yytext); return AND; }
"||"        { yylval.token = new Token(OR, yytext); return OR; }
"("         {yylval.token = new Token('(', yytext); return '(';}
")"         {yylval.token = new Token(')', yytext); return ')';}
"["         {yylval.token = new Token('[', yytext); return '[';}
"]"         {yylval.token = new Token(']', yytext); return ']';}
"{"         {yylval.token = new Token('{', yytext); return '{';}
"}"         {yylval.token = new Token('}', yytext); return '}';}

.           { cout << yytext << " token invalido!\n"; return *yytext; }
%%

int yywrap() {
    return 1;
}

```

### O ```Flex``` armazena esses objetos ```Token``` no campo ```yylval.token``` , o que permite que a semântica dos tokens seja preservada e manipulada pelo analisador sintático.

```c++
{ yylval.token = new Token(EQ, yytext); return EQ; }
```

### Mais tipos de palavras-chave, operadores e tipos de dados foram adicionados a ```tokens.h``` para que o analisador léxico possa identificar os tokens.

```c++
enum Tag { ID = 256, INTEGER, FLOATING, BOOLEAN, TRUE, FALSE, MAIN, IF, ELSE, WHILE, DO, OR, AND, EQ, NEQ, LT, LTE, GT, GTE};
```

### O arquivo ```tokens.h``` define a estrutura de um token.

```c++
#ifndef TOKEN_H
#define TOKEN_H

#include <string>
using std::string;

struct Token {
    int tag;
    string lexeme;

    Token() : tag(0) {}
    Token(char ch) : tag(int(ch)), lexeme({ch}) {}
    Token(int t, const char* s) : tag(t), lexeme(s) {}
};

#endif // TOKEN_H

```

## Para fazer o código usar o analisador léxico gerado pelo Flex em vez do analisador léxico manual, você precisa alterar a declaração do scanner para usar o tipo yyFlexLexer gerado pelo Flex. No código, substitua:

```c++
extern Lexer * scanner;
```

por:

```c++
extern yyFlexLexer * scanner;
```

## Isso indica que o scanner será um objeto da classe yyFlexLexer, e você pode usar funções automaticamente geradas pelo Flex para realizar a análise léxica.

## Como testar

```c++
int main()
{
    int i; int j; float v; float x; float a[100]; bool flag;

    flag = true;
    while (flag)
    {
        do
        {
            i = i+1;
        } 
        while (a[i] < v);
        
        do
        {
            j = j-1;
        } 
        while (a[j] > v);
        
        if (i >= j)
            flag = false;
    
        x = a[i]; a[i] = a[j]; a[j] = x;
    }
}
```

### Rode o comando no terminal

```bash
tradutor.exe ../Testes/teste4.cpp
```

### Saida

```txt
C:\Users\rafae\vscodeworkbench\compiladores\LabFinal - ../Testes/teste4.cpp
        flag = true
L4:
        ifFalse flag goto L5
L1:
        t1 = i + 1
        i = t1
        t3 = a[i]
        t2 = t3 < v
        ifTrue t2 goto L1   
L2:
        t4 = j - 1
        j = t4
        t6 = a[j]
        t5 = t6 > v
        ifTrue t5 goto L2   
        t7 = i >= j
        ifFalse t7 goto L3  
        flag = false        
L3:
        t8 = a[i]
        x = t8
        t9 = a[j]
        a[i] = t9
        a[j] = x
        goto L4
L5:
```



## Video
[link](https://youtu.be/hA8Nkq4JW1g)

