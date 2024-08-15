#pragma once

#include "Lexer.hpp"

class Parser {
public:
    Parser(Lexer& lexer) : lexer(lexer) {
        advance();
    }

    bool parse(double& result);

private:
    Lexer& lexer;
    Token currentToken;
    std::string currentText;

    void advance();
    bool match(Token token);

     // Declaraciones de las funciones correspondientes a las producciones
    bool prg();         // input -> prg
    bool func();        // func -> type IDENT OPEN_PAR param_list CLOSE_PAR OPEN_CURLY (var_decl SEMICOLON)* (stmt SEMICOLON)* CLOSE_CURLY
    bool type();        // type -> KW_INT | KW_INT OPEN_BRACKET NUMBER CLOSE_BRACKET
    bool param_list();  // param_list -> param (COMMA param)* | %empty
    bool param();       // param -> TYPE IDENT | TYPE AMPERSAND IDENT
    bool var_decl();    // var_decl -> type IDENT (COMMA IDENT)*
    bool stmt();        // stmt -> varias opciones (asignación, if, while, cout, cin)
    bool cout_arg();    // cout_arg -> expr | STRING_LITERAL | KW_ENDL
    bool expr();        // expr -> bool_term (BOOL_OR bool_term)*
    bool bool_term();   // bool_term -> rel_expr (BOOL_AND rel_expr)*
    bool rel_expr();    // rel_expr -> arith_expr op arith_expr | arith_expr
    bool arith_expr();  // arith_expr -> arith_term ((OP_ADD | OP_SUB) arith_term)*
    bool arith_term();  // arith_term -> arith_factor ((OP_MULT | OP_DIV | OP_MOD) arith_factor)*
    bool arith_factor();// arith_factor -> NUMBER | IDENT opcional con expr o expr_list | OPEN_PAR expr CLOSE_PAR
    bool expr_list();   // expr_list -> expr (COMMA expr)* | %empty
};