#include <iostream>
#include "error.h"
#include "gen.h"
using std::cout;
using std::endl;

extern Lexer* scanner;

// AQUI ESTÁ O ERRO: Remova esta definição duplicada
// void EmitLabel(int label) {
//     cout << "L" << label << ":" << endl;
// }

Expression* Lvalue(Expression* n) {
    if (n->node_type == NodeType::IDENTIFIER) {
        return n;
    } else if (n->node_type == NodeType::ACCESS) {
        Access* a = (Access*)n;
        return new Access(a->type, a->token, a->id, Rvalue(a->expr));
    } else {
        stringstream ss;
        ss << "Expressão \'" << n->ToString() << "\' não possui valor-l";
        throw SyntaxError{scanner->Lineno(), ss.str()};
    }
}

Expression* Rvalue(Expression* n) {
    if (n->node_type == NodeType::IDENTIFIER || n->node_type == NodeType::CONSTANT) {
        return n;
    } else if (n->node_type == NodeType::ARI) {
        Arithmetic* ari = (Arithmetic*)n;
        Temp* t = new Temp(ari->type);
        Expression* e1 = Rvalue(ari->expr1);
        Expression* e2 = Rvalue(ari->expr2);
        cout << '\t' << t->ToString() << " = " 
             << e1->ToString() << " " 
             << ari->ToString() << " " 
             << e2->ToString() << endl;
        return t;
    } else if (n->node_type == NodeType::REL) {
        Relational* rel = (Relational*)n;
        Temp* t = new Temp(rel->type);
        Expression* e1 = Rvalue(rel->expr1);
        Expression* e2 = Rvalue(rel->expr2);
        cout << '\t' << t->ToString() << " = " 
             << e1->ToString() << " " 
             << rel->ToString() << " " 
             << e2->ToString() << endl;
        return t;
    } else if (n->node_type == NodeType::LOG) {
        Logical* log = (Logical*)n;
        Temp* t = new Temp(log->type);

        // Gerar código para a expressão lógica com parênteses explícitos
        Expression* e1 = Rvalue(log->expr1);
        Expression* e2 = Rvalue(log->expr2);

        Node tempNode;  // Cria uma instância de Node

        if (log->token->tag == AND) {
            // Geração de código para o operador &&
            cout << "\tif " << e1->ToString() << " goto L" << tempNode.NewLabel() << endl;
        } else if (log->token->tag == OR) {
            // Geração de código para o operador ||
            cout << "\tifFalse " << e1->ToString() << " goto L" << tempNode.NewLabel() << endl;
        }

        return t;
    } else if (n->node_type == NodeType::UNARY) {
        UnaryExpr* una = (UnaryExpr*)n;
        Temp* t = new Temp(una->type);
        Expression* e = Rvalue(una->expr);
        cout << '\t' << t->ToString() << " = " 
             << una->ToString() 
             << e->ToString() 
             << endl;
        return t;
    } else if (n->node_type == NodeType::ACCESS) {
        Access* access = (Access*)n;
        Temp* temp = new Temp(access->type);
        Expression* right = Lvalue(n);
        cout << '\t' << temp->ToString() << " = " 
             << right->ToString() 
             << endl;
        return temp;
    } else if (n->node_type == NodeType::ASSIGN) {
        Access* acc = (Access*)Lvalue(n);
        Expression* left = Lvalue(acc->id);
        Expression* right = Rvalue(acc->expr);
        cout << '\t' 
             << left->ToString()  
             << " = " 
             << right->ToString() 
             << endl;
        return right;
    } else {
        stringstream ss;
        ss << "Expressão \'" << n->ToString() << "\' não possui valor-r";
        throw SyntaxError{scanner->Lineno(), ss.str()};
    }
}

// Definição de EmitLabel em gen.cpp
void EmitLabel(int label) {
    cout << "L" << label << ":" << endl;
}

// Definição de While::Gen() em gen.cpp
void While::Gen() {
    int label1 = NewLabel();  // Cria rótulo para o início do loop
    int label2 = NewLabel();  // Cria rótulo para o final do loop

    EmitLabel(label1);  // Emite o rótulo do início
    Expression* cond = Rvalue(condition);  // Avalia a condição do while
    cout << "\tifFalse " << cond->ToString() << " goto L" << label2 << endl;  // Se a condição for falsa, vai para o final do loop
    body->Gen();  // Gera o código do corpo do while
    cout << "\tgoto L" << label1 << endl;  // Volta ao início do loop
    EmitLabel(label2);  // Emite o rótulo de saída do loop
}



