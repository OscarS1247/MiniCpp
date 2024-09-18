#pragma once

#include "Lexer.hpp"
#include <memory>
#include "Ast.hpp"
#include <iostream>
#include <cstdlib>
#include <vector>

class Parser {
public:
    Parser(Lexer& lexer) : lexer(lexer) {
        advance();
    }

    bool parse(double& result);

    std::shared_ptr<Program> prg();            // Devuelve el nodo Program
private:
    Lexer& lexer;
    Token currentToken;
    std::string currentText;
    int currentLine;

    void advance();
    bool match(Token token);
    void error(const std::string& expected);


    std::shared_ptr<FunctionDecl> func();      // Devuelve el nodo FunctionDecl
    bool param_list(std::shared_ptr<FunctionDecl> funcNode);  // Modificamos para recibir el nodo de función
    bool param(std::shared_ptr<FunctionDecl> funcNode);       // Modificamos para recibir el nodo de función
    std::shared_ptr<VarDecl> var_decl();       // Devuelve el nodo VarDecl
    bool ident_decl();                         // Esta función aún puede devolver bool si solo hace matching
    std::shared_ptr<Statement> stmt();         // Devuelve el nodo Statement
    std::shared_ptr<Expression> cout_arg();    // Devuelve el nodo Expression (para los argumentos de cout)
    std::shared_ptr<Expression> expr();        // Devuelve el nodo Expression
    std::shared_ptr<Expression> bool_term();   
    std::shared_ptr<Expression> rel_expr();    
    std::shared_ptr<Expression> arith_expr();  
    std::shared_ptr<Expression> arith_term();  
    std::shared_ptr<Expression> arith_factor();
    std::vector<std::shared_ptr<Expression>> expr_list();                           
};