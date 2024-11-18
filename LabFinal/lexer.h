#ifndef COMPILER_LEXER
#define COMPILER_LEXER

#include <unordered_map>
#include <string>
#include <sstream>
#include "token.h"  
using std::stringstream;
using std::unordered_map;
using std::string;


class Lexer
{
private:
	char peek;			// último caractere lido
	Token token;		// último token retornado
	int line = 1;		// número da linha atual

	// tabela para identificadores e palavras-chave
	unordered_map<string, Token> token_table;

public:
	Lexer();			// construtor
	int lineno();		// retorna linha atual
	Token * Scan();		// retorna próximo token da entrada
};

#endif
