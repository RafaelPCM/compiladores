#include <iostream> // Para depuração com std::cout
#include <sstream>
#include "ast.h"
#include "error.h"
using std::stringstream;

extern Lexer *scanner;

// ----
// Node
// ----

Node::Node() : node_type(NodeType::UNKNOWN) {}
Node::Node(int t) : node_type(t) {}

// ---------
// Statement
// ---------

Statement::Statement() : Node(NodeType::STMT) {}
Statement::Statement(int type) : Node(type) {}

// ----------
// Expression
// ----------

Expression::Expression(Token *t) : Node(NodeType::EXPR), type(ExprType::VOID), token(t) {}
Expression::Expression(int ntype, int etype, Token *t) : Node(ntype), type(etype), token(t) {}

string Expression::Name()
{
    return token->lexeme;
}

string Expression::Type()
{
    switch (type)
    {
    case ExprType::INT:
        return "int";
        break;
    case ExprType::FLOAT:
        return "float";
        break;
    case ExprType::BOOL:
        return "bool";
        break;
    default:
        return "void";
    }
}

// --------
// Constant
// --------

Constant::Constant(int etype, Token *t) : Expression(NodeType::CONSTANT, etype, t)
{
    // Implementa a conversão automática de inteiro para booleano
    if (etype == ExprType::INT)
    {
        int value = std::stoi(token->lexeme);
        std::cout << "Constante Inteira: " << value << std::endl; // Depuração
        if (value == 0)
        {
            // Se for 0, converte para false (booleano)
            type = ExprType::BOOL;
            token->lexeme = "false";
            std::cout << "Convertido para False" << std::endl; // Depuração
        }
        else
        {
            // Qualquer outro valor converte para true (booleano)
            type = ExprType::BOOL;
            token->lexeme = "true";
            std::cout << "Convertido para True" << std::endl; // Depuração
        }
    }
}

// ----------
// Identifier
// ----------

Identifier::Identifier(int etype, Token *t) : Expression(NodeType::IDENTIFIER, etype, t) {}

// ------
// Access
// ------

Access::Access(int etype, Token *t, Expression *i, Expression *e) : Expression(NodeType::ACCESS, etype, t), id(i), expr(e) {}

// -------
// Logical
// -------

Logical::Logical(Token *t, Expression *e1, Expression *e2) : Expression(NodeType::LOG, ExprType::BOOL, t), expr1(e1), expr2(e2)
{
    // Verifica e realiza conversões automáticas de tipos
    if (expr1->type != ExprType::BOOL)
    {
        if (expr1->type == ExprType::INT)
        {
            // Converte inteiro para booleano
            if (expr1->node_type == NodeType::CONSTANT)
            {
                int value = std::stoi(expr1->token->lexeme);
                expr1->type = ExprType::BOOL;
                expr1->token->lexeme = (value == 0) ? "false" : "true";
            }
            else
            {
                // Para expressões não constantes, cria uma expressão relacional expr1 != 0
                Token *neqToken = new Token(Tag::NEQ, "!=");
                Constant *zeroConst = new Constant(ExprType::INT, new Token(Tag::INTEGER, "0"));
                expr1 = new Relational(neqToken, expr1, zeroConst);
            }
        }
        else
        {
            stringstream ss;
            ss << "\'" << token->lexeme << "\' usado com operando nao booleano ("
               << expr1->Name() << ":" << expr1->Type() << ")";
            throw SyntaxError{scanner->Lineno(), ss.str()};
        }
    }

    if (expr2->type != ExprType::BOOL)
    {
        if (expr2->type == ExprType::INT)
        {
            // Converte inteiro para booleano
            if (expr2->node_type == NodeType::CONSTANT)
            {
                int value = std::stoi(expr2->token->lexeme);
                expr2->type = ExprType::BOOL;
                expr2->token->lexeme = (value == 0) ? "false" : "true";
            }
            else
            {
                // Para expressões não constantes, cria uma expressão relacional expr2 != 0
                Token *neqToken = new Token(Tag::NEQ, "!=");
                Constant *zeroConst = new Constant(ExprType::INT, new Token(Tag::INTEGER, "0"));
                expr2 = new Relational(neqToken, expr2, zeroConst);
            }
        }
        else
        {
            stringstream ss;
            ss << "\'" << token->lexeme << "\' usado com operando nao booleano ("
               << expr2->Name() << ":" << expr2->Type() << ")";
            throw SyntaxError{scanner->Lineno(), ss.str()};
        }
    }

    std::cout << "Operacao Logica: " << expr1->Name() << " " << token->lexeme << " " << expr2->Name() << std::endl; // Depuração
}

// ----------
// Relational
// ----------

Relational::Relational(Token *t, Expression *e1, Expression *e2) : Expression(NodeType::REL, ExprType::BOOL, t), expr1(e1), expr2(e2)
{
    // Verifica e realiza conversões automáticas de tipos
    if (expr1->type != expr2->type)
    {
        if ((expr1->type == ExprType::INT && expr2->type == ExprType::BOOL) ||
            (expr1->type == ExprType::BOOL && expr2->type == ExprType::INT))
        {
            // Converte booleanos para inteiros
            if (expr1->type == ExprType::BOOL)
            {
                if (expr1->node_type == NodeType::CONSTANT)
                {
                    expr1->type = ExprType::INT;
                    expr1->token->lexeme = (expr1->token->lexeme == "true") ? "1" : "0";
                }
                else
                {
                    // Para expressões não constantes, adicionar lógica adicional se necessário
                }
            }
            if (expr2->type == ExprType::BOOL)
            {
                if (expr2->node_type == NodeType::CONSTANT)
                {
                    expr2->type = ExprType::INT;
                    expr2->token->lexeme = (expr2->token->lexeme == "true") ? "1" : "0";
                }
                else
                {
                    // Para expressões não constantes, adicionar lógica adicional se necessário
                }
            }
        }
        else
        {
            stringstream ss;
            ss << "\'" << token->lexeme << "\' usado com operandos de tipos incompativeis ("
               << expr1->Name() << ":" << expr1->Type() << ") e ("
               << expr2->Name() << ":" << expr2->Type() << ")";
            throw SyntaxError{scanner->Lineno(), ss.str()};
        }
    }

    std::cout << "Operacao Relacional: " << expr1->Name() << " " << token->lexeme << " " << expr2->Name() << std::endl; // Depuração
}

// ----------
// Arithmetic
// ----------

Arithmetic::Arithmetic(int etype, Token *t, Expression *e1, Expression *e2) : Expression(NodeType::ARI, etype, t), expr1(e1), expr2(e2)
{
    // Verifica e realiza conversões automáticas de tipos
    if (expr1->type != expr2->type)
    {
        if ((expr1->type == ExprType::INT && expr2->type == ExprType::BOOL) ||
            (expr1->type == ExprType::BOOL && expr2->type == ExprType::INT))
        {
            // Converte booleanos para inteiros
            if (expr1->type == ExprType::BOOL)
            {
                if (expr1->node_type == NodeType::CONSTANT)
                {
                    expr1->type = ExprType::INT;
                    expr1->token->lexeme = (expr1->token->lexeme == "true") ? "1" : "0";
                }
                else
                {
                    // Para expressões não constantes, adicionar lógica adicional se necessário
                }
            }
            if (expr2->type == ExprType::BOOL)
            {
                if (expr2->node_type == NodeType::CONSTANT)
                {
                    expr2->type = ExprType::INT;
                    expr2->token->lexeme = (expr2->token->lexeme == "true") ? "1" : "0";
                }
                else
                {
                    // Para expressões não constantes, adicionar lógica adicional se necessário
                }
            }
        }
        else
        {
            stringstream ss;
            ss << "\'" << token->lexeme << "\' usado com operandos de tipos incompativeis ("
               << expr1->Name() << ":" << expr1->Type() << ") e ("
               << expr2->Name() << ":" << expr2->Type() << ")";
            throw SyntaxError{scanner->Lineno(), ss.str()};
        }
    }

    std::cout << "Operacao Aritmetica: " << expr1->Name() << " " << token->lexeme << " " << expr2->Name() << std::endl; // Depuração
}

// ---------
// UnaryExpr
// ---------

UnaryExpr::UnaryExpr(int etype, Token *t, Expression *e) : Expression(NodeType::UNARY, etype, t), expr(e)
{
    // Verifica e realiza conversões automáticas de tipos
    if (expr->type != ExprType::BOOL)
    {
        if (expr->type == ExprType::INT)
        {
            // Converte inteiro para booleano
            if (expr->node_type == NodeType::CONSTANT)
            {
                int value = std::stoi(expr->token->lexeme);
                expr->type = ExprType::BOOL;
                expr->token->lexeme = (value == 0) ? "false" : "true";
            }
            else
            {
                // Para expressões não constantes, cria uma expressão relacional expr != 0
                Token *neqToken = new Token(Tag::NEQ, "!=");
                Constant *zeroConst = new Constant(ExprType::INT, new Token(Tag::INTEGER, "0"));
                expr = new Relational(neqToken, expr, zeroConst);
            }
        }
        else
        {
            stringstream ss;
            ss << "\'" << token->lexeme << "\' usado com operando nao booleano ("
               << expr->Name() << ":" << expr->Type() << ")";
            throw SyntaxError{scanner->Lineno(), ss.str()};
        }
    }

    std::cout << "Expressao Unaria: " << token->lexeme << " " << expr->Name() << std::endl; // Depuração
}

// ----
// Seq
// ----

Seq::Seq(Statement *s, Statement *ss) : Statement(NodeType::SEQ), stmt(s), stmts(ss) {}

// ------
// Assign
// ------

Assign::Assign(Expression *i, Expression *e) : Statement(NodeType::ASSIGN), id(i), expr(e)
{
    // Verifica e realiza conversões automáticas de tipos
    if (id->type != expr->type)
    {
        if (id->type == ExprType::BOOL && expr->type == ExprType::INT)
        {
            // Converte inteiro para booleano
            if (expr->node_type == NodeType::CONSTANT)
            {
                int value = std::stoi(expr->token->lexeme);
                expr->type = ExprType::BOOL;
                expr->token->lexeme = (value == 0) ? "false" : "true";
            }
            else
            {
                // Para expressões não constantes, cria uma expressão relacional expr != 0
                Token *neqToken = new Token(Tag::NEQ, "!=");
                Constant *zeroConst = new Constant(ExprType::INT, new Token(Tag::INTEGER, "0"));
                expr = new Relational(neqToken, expr, zeroConst);
            }
        }
        else if (id->type == ExprType::INT && expr->type == ExprType::BOOL)
        {
            // Converte booleano para inteiro
            if (expr->node_type == NodeType::CONSTANT)
            {
                expr->type = ExprType::INT;
                expr->token->lexeme = (expr->token->lexeme == "true") ? "1" : "0";
            }
            else
            {
                // Para expressões não constantes, adicionar lógica adicional se necessário
            }
        }
        else
        {
            // Tipos incompatíveis
            stringstream ss;
            ss << "\'=\' usado com operandos de tipos incompativeis ("
               << id->Name() << ":" << id->Type() << ") e ("
               << expr->Name() << ":" << expr->Type() << ")";
            throw SyntaxError{scanner->Lineno(), ss.str()};
        }
    }

    std::cout << "Atribuicao: " << id->Name() << " = " << expr->Name() << std::endl; // Depuração
}

// ----
// If
// ----

If::If(Expression *e, Statement *s) : Statement(NodeType::IF_STMT), expr(e), stmt(s) {}

// -----
// While
// -----

While::While(Expression *e, Statement *s) : Statement(NodeType::WHILE_STMT), expr(e), stmt(s) {}

// --------
// Do-While
// --------

DoWhile::DoWhile(Statement *s, Expression *e) : Statement(NodeType::DOWHILE_STMT), stmt(s), expr(e) {}
