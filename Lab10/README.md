# Para rodar o Lab10:
cd Lab10


<!-- Para o teste 1 -->

g++ -o Lab10/Ast/Testes/teste1.exe `
Lab10/Ast/main.cpp `
Lab10/Ast/ast.cpp `
Lab10/Ast/lexer.cpp `
Lab10/Ast/parser.cpp `
Lab10/Ast/error.cpp `
Lab10/Ast/symtable.cpp `
Lab10/Ast/checker.cpp `
-std=c++17

.\Lab10\Ast\Testes\teste1.exe Lab10/Ast/Testes/teste1.cpp


<!-- Para o teste 2 -->
g++ -o Lab10/Ast/Testes/teste2.exe `
Lab10/Ast/main.cpp `
Lab10/Ast/ast.cpp `
Lab10/Ast/lexer.cpp `
Lab10/Ast/parser.cpp `
Lab10/Ast/error.cpp `
Lab10/Ast/symtable.cpp `
Lab10/Ast/checker.cpp `
-std=c++17

.\Lab10\Ast\Testes\teste2.exe Lab10/Ast/Testes/teste2.cpp
