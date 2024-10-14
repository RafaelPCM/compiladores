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
                        // Caso chegue ao final do arquivo sem fechar o comentário
                        cout << "Erro: Comentário de bloco não fechado" << endl;
                        return Token{Tag::END};
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
