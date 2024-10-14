#include <iostream>
#include <sstream>
#include "lexer.h" // Certifique-se de que Token e Word estão definidos aqui

using namespace std;

Lexer::Lexer() {
    // Inicializa a tabela de identificadores, se necessário
}

Token Lexer::Scan()
{
    // Ignora espaços em branco e comentários
    while (isspace(peek) || peek == '/')
    {
        if (peek == '/')
        {
            peek = cin.get();
            if (peek == '/')
            {
                // Ignora até o fim da linha
                while (peek != '\n' && peek != EOF)
                {
                    peek = cin.get();
                }
            }
            else if (peek == '*')
            {
                // Ignora comentário de bloco
                while (true)
                {
                    peek = cin.get();
                    if (peek == '*' && cin.peek() == '/')
                    {
                        cin.get(); // Consome o '/'
                        break;
                    }
                    else if (peek == EOF)
                    {
                        cout << "Erro: Comentário de bloco não fechado" << endl;
                        return Token{0}; // Use um valor apropriado aqui
                    }
                }
            }
            else
            {
                // Se não for um comentário, volta o caractere
                cin.putback(peek);
                peek = ' ';
            }
        }
        else
        {
            // Incrementa a linha se encontrar uma nova linha
            if (peek == '\n')
                line += 1;
            peek = cin.get();
        }
    }

    // Lógica para números, palavras reservadas, etc.
    if (isdigit(peek))
    {
        int v = 0;
        do
        {
            int n = peek - '0';
            v = 10 * v + n;
            peek = cin.get();
        } while (isdigit(peek));

        cout << "<NUM," << v << "> ";
        return Num{v};
    }

    if (isalpha(peek))
    {
        stringstream ss;
        do
        {
            ss << peek;
            peek = cin.get();
        } while (isalpha(peek));

        string s = ss.str();
        cout << "<ID," << s << "> ";
        return Word{s};
    }

    // Trata caracteres desconhecidos e operadores
    Token tok{peek};
    peek = ' ';
    return tok;
}

void Lexer::Start() {
    Token tok = Scan();
    while (tok.tag != EOF) { // Assumimos que EOF é o indicador de fim do arquivo
        tok = Scan();
    }
}
