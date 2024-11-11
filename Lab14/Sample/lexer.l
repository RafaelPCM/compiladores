%{
// Reconhecedor de uma linguagem simplificada
#include <iostream>
#include "tokens.h"
using std::cout;
%}

%option noyywrap
delim	[ \t\n]
brancos {delim}+
letra	[A-Za-z]
digito	[0-9]
id	    ({letra}|_)(_{letra}|{letra}|{digito})*
num	    {digito}+(\.{digito}+)?(E[+-]?{digito}+)?
\"([^\"\\\\]|\\\\.)*\" {
    yylval.str = strdup(yytext + 1); // Remove surrounding quotes
    yylval.str[strlen(yylval.str) - 1] = '\\0'; // Remove ending quote
    for (char *src = yylval.str, *dest = yylval.str; *src; ++src) {
        if (*src == '\\\\' && (*(src + 1) == '\"' || *(src + 1) == '\\\\')) {
            *dest++ = *(++src);
        } else {
            *dest++ = *src;
        }
    }
    *dest = '\\0';
    return STRING;
}


%%
{brancos}	; // nenhuma ação e nenhum retorno
if		    return IF; 
then		return THEN; 
else		return ELSE; 
while       return WHILE;
{id}		return ID;  
{num}	    return NUM; 
"=="        return RELOP;
"!="        return RELOP;
"<"         return RELOP;
"<="        return RELOP;
">"         return RELOP;
">="        return RELOP;
.           cout << YYText() << " é um token inválido!\n"; 
%%

// nenhuma função auxiliar é necessária
