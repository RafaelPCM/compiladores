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
    std::string str = YYText();
    str = str.substr(1, str.length() - 2);
    size_t pos = 0;
    while ((pos = str.find("\\", pos)) != std::string::npos) {
        if (pos + 1 < str.length()) {
            if (str[pos + 1] == '"' || str[pos + 1] == '\\') {
                str.erase(pos, 1);
                pos += 1;
            } else {
                str.erase(pos, 1);
            }
        } else {
            str.erase(pos, 1);
        }
    }

    cout << "String capturada: " << str << "\n";
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
