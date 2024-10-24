// error.cpp
#include "error.h"

SyntaxError::SyntaxError(int line, string m) : lineno(line), msg(m) {}

string SyntaxError::What()
{
    return msg;   // Deve retornar msg
}

int SyntaxError::LineNo()
{
    return lineno;
}
