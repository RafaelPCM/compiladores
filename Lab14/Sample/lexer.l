%{
#include <iostream>
#include "tokens.h"
using std::cout;
%}

%option noyywrap
delim    [ \t\n]
brancos  {delim}+
letra    [A-Za-z]
digito   [0-9]
id       ({letra}|_)(_{letra}|{letra}|{digito})*
num      {digito}+(\.{digito}+)?(E[+-]?{digito}+)? 
string   \"([^"\\]|\\.)*\"

%%

{string} {
    cout << "String capturada: " << YYText() << "\n";  // Verificação básica para strings
    return STRING;
}
{brancos}    ;
if           return IF; 
then         return THEN; 
else         return ELSE; 
while        return WHILE;
{id}         return ID;  
{num}        return NUM; 
"=="         return RELOP;
"!="         return RELOP;
"<"          return RELOP;
"<="         return RELOP;
">"          return RELOP;
">="         return RELOP;
.            cout << YYText() << " é um token inválido!\n";
