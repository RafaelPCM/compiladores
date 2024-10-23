# Compiladores

FONTE: MATERIAL DE LABORATORIO DE COMPILADORES DO PROFESSOR JUDSON SANTOS SANTIAGO

O LINK DO GITHUB DO CODIGO FONTE DO ANALISADOR LEXICO PODE ACESSADO:

https://github.com/JudsonSS/Compiladores/tree/2e1b81ba859e18e938ea149d1cef2edea04dde36/Labs/Lab06



## Para rodar o projeto:

### [Como Instalar GCC/G++ MinGW no Windows:](https://terminalroot.com.br/2022/12/como-instalar-gcc-gpp-mingw-no-windows.html)

### Comandos uteis para rodar o projeto:

cd Lab06

g++ -o lexer lexer.cpp expressions.cpp

Get-Content input.txt | ./lexer.exe


Para rodar o Lab10:


g++ -o Lab10\Ast\Testes\teste1 Lab10\Ast\Testes\teste1.cpp Lab10\Ast\ast.cpp Lab10\Ast\lexer.cpp Lab10\Ast\parser.cpp Lab10\Ast\error.cpp Lab10\Ast\symtable.cpp -std=c++17
./Lab10/Ast/Testes/teste1

g++ -o Lab10\Ast\Testes\teste2 Lab10\Ast\Testes\teste2.cpp Lab10\Ast\ast.cpp Lab10\Ast\lexer.cpp Lab10\Ast\parser.cpp Lab10\Ast\error.cpp Lab10\Ast\symtable.cpp -std=c++17
./Lab10/Ast/Testes/teste2