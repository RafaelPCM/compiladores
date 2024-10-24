// main.cpp
#include "parser.h"
#include "checker.h"
#include "error.h"
#include <iostream>
#include <fstream>

// Definição das variáveis globais
Lexer* scanner = nullptr;
std::ifstream fin;

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Uso: " << argv[0] << " <arquivo_de_entrada>" << std::endl;
        return 1;
    }

    fin.open(argv[1]);
    if (!fin)
    {
        std::cerr << "Nao foi possivel abrir o arquivo " << argv[1] << std::endl;
        return 1;
    }

    scanner = new Lexer();
    Parser parser;

    try
    {
        Node* root = parser.Start();
        std::cout << "Analise sintatica concluida com sucesso!" << std::endl;

        // Se você quiser testar o AST
        TestParser(root);
    }
    catch (SyntaxError& e)
    {
        std::cerr << "Erro na linha " << e.LineNo() << ": " << e.What() << std::endl;
    }

    fin.close();
    delete scanner;
    return 0;
}
