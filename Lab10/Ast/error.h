// error.h
#ifndef COMPILER_ERROR
#define COMPILER_ERROR

#include <string>
using std::string;

class SyntaxError
{
private:
    int lineno;
    string msg;

public:
    SyntaxError(int, string);
    string What();   // Deve retornar string
    int LineNo();    // Método para acessar lineno
};

#endif
