#include "Parser.hpp"
#include <iostream>
#include <cstdlib>

void Parser::advance() {
    currentToken = lexer.nextToken();
    currentText = lexer.tokenText();
}

bool Parser::match(Token token) {
    if (currentToken == token) {
        advance();
        return true;
    }
    return false;
}

bool Parser::parse(double& result) {
    return prg() && currentToken == Token::Eof;
}

bool Parser::prg() {
    while (currentToken == Token::KW_INT) { 
        if (!func()) return false;
    }
    return true;                                                      
}

bool Parser::func() {
    std::cout << "Entering func()\n";

    if (!type()) {
        std::cerr << "Error: Expected type at " << currentText << "\n";
        return false;
    }
    std::cout << "Matched type\n";

    if (!match(Token::IDENT)) {
        std::cerr << "Error: Expected identifier after type at " << currentText << "\n";
        return false;
    }
    std::cout << "Matched identifier: " << currentText << "\n";

    if (!match(Token::OPEN_PAR)) {
        std::cerr << "Error: Expected '(' after identifier at " << currentText << "\n";
        return false;
    }
    std::cout << "Matched '('\n";

    if (!param_list()) {
        std::cerr << "Error: Expected parameter list at " << currentText << "\n";
        return false;
    }
    std::cout << "Matched parameter list\n";

    if (!match(Token::CLOSE_PAR)) {
        std::cerr << "Error: Expected ')' after parameter list at " << currentText << "\n";
        return false;
    }
    std::cout << "Matched ')'\n";

    if (!match(Token::OPEN_CURLY)) {
        std::cerr << "Error: Expected '{' to start function body at " << currentText << "\n";
        return false;
    }
    std::cout << "Matched '{'\n";

    while (currentToken == Token::KW_INT) { 
        std::cout << "Processing variable declaration\n";
        if (!var_decl()) {
            std::cerr << "Error: Invalid variable declaration at " << currentText << "\n";
            return false;
        }
        // if (!match(Token::SEMICOLON)) {
        //     std::cerr << "Error: Expected ';' after variable declaration at " << currentText << "\n";
        //     return false;
        // }
        // std::cout << "Matched ';'\n";
    }

    while (currentToken != Token::CLOSE_CURLY) {
        std::cout << "Processing statement\n";
        if (!stmt()) {
            std::cerr << "Error: Invalid statement at " << currentText << "\n";
            return false;
        }
        // if (!match(Token::SEMICOLON)) {
        //     std::cerr << "Error: Expected ';' after statement at " << currentText << "\n";
        //     return false;
        // }
        // std::cout << "Matched ';' after statement\n";
    }

    while (currentToken != Token::CLOSE_CURLY) {
    if (!stmt()) {
            std::cout << "Processing statement\n";
            std::cerr << "Error: Invalid statement at " << currentText << "\n";
            return false;
        }
    }

    if (match(Token::CLOSE_CURLY)) {
        std::cout << "Matched '}'\n";
        return true;
    } else {
        std::cerr << "Error: Expected '}' at the end of function body at " << currentText << "\n";
        return false;
    }
}

bool Parser::type() {
    if (match(Token::KW_INT)) {
        if (match(Token::OPEN_BRACKET)) {
            if (!match(Token::NUMBER)) return false;
            if (!match(Token::CLOSE_BRACKET)) return false;
        }
        return true;
    }
    return false;
}

bool Parser::param_list() {
    if (currentToken == Token::KW_INT) {
        if (!param()) return false;
        while (match(Token::COMMA)) {
            if (!param()) return false;
        }
    }
    return true; // Lista vacía es válida
}

bool Parser::param() {
    if (!type()) return false;
    if (match(Token::AMPERSAND)) {
        if (!match(Token::IDENT)) return false;
    } else {
        if (!match(Token::IDENT)) return false;
    }
    return true;
}

bool Parser::var_decl() {
    std::cout << "Entering var_decl()\n";

    if (!type()) {
        std::cerr << "Error: Expected type in variable declaration at " << currentText << "\n";
        return false;
    }
    std::cout << "Matched type\n";

    if (!match(Token::IDENT)) {
        std::cerr << "Error: Expected identifier after type in variable declaration at " << currentText << "\n";
        return false;
    }
    std::cout << "Matched identifier: " << currentText << "\n";

    while (match(Token::COMMA)) {
        std::cout << "Matched ',' in variable declaration, expecting another identifier\n";
        if (!match(Token::IDENT)) {
            std::cerr << "Error: Expected identifier after ',' in variable declaration at " << currentText << "\n";
            return false;
        }
        std::cout << "Matched identifier: " << currentText << "\n";
    }

    if (!match(Token::SEMICOLON)){
        std::cout << "Error: Expected semicolon after identifier in variable declaration at " << currentText << "\n";
        return false;
    }
    std::cout << "Matched semicolon: " << currentText << "\n";

    std::cout << "Completed var_decl()\n";

    return true;
}

bool Parser::stmt() {
    std::cout << "Entering stmt()\n";

    if (match(Token::IDENT)) {
        std::cout << "Matched IDENT: " << currentText << "\n";

        if (match(Token::OPEN_BRACKET)) {
            std::cout << "Matched '[', parsing expr\n";
            if (!expr()) {
                std::cerr << "Error: Expected expression after '[' at " << currentText << "\n";
                return false;
            }
            if (!match(Token::CLOSE_BRACKET)) {
                std::cerr << "Error: Expected ']' after expression at " << currentText << "\n";
                return false;
            }
            std::cout << "Matched ']'\n";
        }

        if (!match(Token::OP_ASSIGN)) {
            std::cerr << "Error: Expected '=' after IDENT or array access at " << currentText << "\n";
            return false;
        }
        std::cout << "Matched '='\n";

        if (!expr()) {
            std::cerr << "Error: Expected expression after '=' at " << currentText << "\n";
            return false;
        }
        std::cout << "Parsed expression after '='\n";

        if (!match(Token::SEMICOLON)) {
            std::cerr << "Error: Expected ';' after expr at variable inicialization " << currentText << "\n";
            return false;
        }
        std::cout << "Matched ';' after expr\n";

        return true;

    } else if (match(Token::KW_IF)) {
        std::cout << "Matched KW_IF\n";

        if (!match(Token::OPEN_PAR)) {
            std::cerr << "Error: Expected '(' after 'if' at " << currentText << "\n";
            return false;
        }

        if (!expr()) {
            std::cerr << "Error: Expected expression in 'if' condition at " << currentText << "\n";
            return false;
        }
        std::cout << "Parsed expression\n";

        if (!match(Token::CLOSE_PAR)) {
            std::cerr << "Error: Expected ')' after 'if' condition at " << currentText << "\n";
            return false;
        }

        if (!match(Token::OPEN_CURLY)) {
            std::cerr << "Error: Expected '{' to start 'if' body at " << currentText << "\n";
            return false;
        }

        while (currentToken != Token::CLOSE_CURLY) {
            std::cout << "Parsing statement in 'if' body\n";
            if (!stmt()) return false;
            // if (!match(Token::SEMICOLON)) {
            //     std::cerr << "Error: Expected ';' after statement in 'if' body at " << currentText << "\n";
            //     return false;
            // }
        }

        if (!match(Token::CLOSE_CURLY)) {
            std::cerr << "Error: Expected '}' to close 'if' body at " << currentText << "\n";
            return false;
        }

        if (match(Token::KW_ELSE)) {
            std::cout << "Matched KW_ELSE\n";
            if (!match(Token::OPEN_CURLY)) {
                std::cerr << "Error: Expected '{' to start 'else' body at " << currentText << "\n";
                return false;
            }
            while (currentToken != Token::CLOSE_CURLY) {
                std::cout << "Parsing statement in 'else' body\n";
                if (!stmt()) return false;
                // if (!match(Token::SEMICOLON)) {
                //     std::cerr << "Error: Expected ';' after statement in 'else' body at " << currentText << "\n";
                //     return false;
                // }
            }
            if (!match(Token::CLOSE_CURLY)) {
                std::cerr << "Error: Expected '}' to close 'else' body at " << currentText << "\n";
                return false;
            }
        }
        return true;

    } else if (match(Token::KW_WHILE)) {
        std::cout << "Matched KW_WHILE\n";

        if (!match(Token::OPEN_PAR)) {
            std::cerr << "Error: Expected '(' after 'while' at " << currentText << "\n";
            return false;
        }

        if (!expr()) {
            std::cerr << "Error: Expected expression in 'while' condition at " << currentText << "\n";
            return false;
        }

        if (!match(Token::CLOSE_PAR)) {
            std::cerr << "Error: Expected ')' after 'while' condition at " << currentText << "\n";
            return false;
        }

        if (!match(Token::OPEN_CURLY)) {
            std::cerr << "Error: Expected '{' to start 'while' body at " << currentText << "\n";
            return false;
        }

        while (currentToken != Token::CLOSE_CURLY) {
            std::cout << "Parsing statement in 'while' body\n";
            if (!stmt()) return false;
            // if (!match(Token::SEMICOLON)) {
            //     std::cerr << "Error: Expected ';' after statement in 'while' body at " << currentText << "\n";
            //     return false;
            // }
        }

        return match(Token::CLOSE_CURLY);

    } else if (match(Token::KW_COUT)) {
        std::cout << "Matched KW_COUT\n";
        while (match(Token::LT_LT)) {
            if (!cout_arg()) {
                std::cerr << "Error: Expected argument after '<<' in 'cout' at " << currentText << "\n";
                return false;
            }
        }

        if (!match(Token::SEMICOLON)) {
            std::cerr << "Error: Expected ';' after 'cout' statement at " << currentText << "\n";
            return false;
        }
        return true;

    } else if (match(Token::KW_CIN)) {
        std::cout << "Matched KW_CIN\n";
        if (!match(Token::GT_GT)) {
            std::cerr << "Error: Expected '>>' after 'cin' at " << currentText << "\n";
            return false;
        }
        std::cout << "Matched GT_GT\n";
        if (!match(Token::IDENT)) {
            std::cerr << "Error: Expected identifier after '>>' in 'cin' at " << currentText << "\n";
            return false;
        }

        if (match(Token::OPEN_CURLY)) {
            std::cout << "Matched '{' after 'cin >> IDENT'\n";
            if (!expr()) {
                std::cerr << "Error: Expected expression inside '{}' after 'cin >> IDENT' at " << currentText << "\n";
                return false;
            }
            if (!match(Token::CLOSE_CURLY)) {
                std::cerr << "Error: Expected '}' after expression in 'cin' statement at " << currentText << "\n";
                return false;
            }
            std::cout << "Matched '}' after expression in 'cin' statement\n";
        }

        if (!match(Token::SEMICOLON)) {
            std::cerr << "Error: Expected ';' after 'cin' statement at " << currentText << "\n";
            return false;
        }

        return true;
    }

    std::cerr << "Error: Unexpected token at " << currentText << "\n";
    return false;
}

bool Parser::cout_arg() {
    std::cout << "Entering cout_arg()\n";

    if (match(Token::STRING_LITERAL)) {
        std::cout << "Matched STRING_LITERAL: " << currentText << "\n";
        return true;
    } else if (match(Token::KW_ENDL)) {
        std::cout << "Matched KW_ENDL\n";
        return true;
    } else {
        std::cout << "Attempting to match expression in cout_arg()\n";
        if (expr()) {
            std::cout << "Matched expression in cout_arg()\n";
            return true;
        } else {
            std::cerr << "Error: Expected string literal, 'endl', or expression in cout_arg() at " << currentText << "\n";
            return false;
        }
    }
}

bool Parser::expr() {
    if (!bool_term()) return false;
    while (match(Token::BOOL_OR)) {
        if (!bool_term()) return false;
    }
    return true;
}

bool Parser::bool_term() {
    if (!rel_expr()) return false;
    while (match(Token::BOOL_AND)) {
        if (!rel_expr()) return false;
    }
    return true;
}

bool Parser::rel_expr() {
    if (!arith_expr()) return false;
    if (match(Token::GT) || match(Token::LT) || match(Token::GTE) || match(Token::LTE) || match(Token::NE) || match(Token::EQ)) {
        if (!arith_expr()) return false;
    }
    return true;
}

bool Parser::arith_expr() {
    if (!arith_term()) return false;
    while (match(Token::OP_ADD) || match(Token::OP_SUB)) {
        if (!arith_term()) return false;
    }
    return true;
}

bool Parser::arith_term() {
    if (!arith_factor()) return false;
    while (match(Token::OP_MULT) || match(Token::OP_DIV) || match(Token::OP_MOD)) {
        if (!arith_factor()) return false;
    }
    return true;
}

bool Parser::arith_factor() {
    if (match(Token::NUMBER)) {
        return true;
    } else if (match(Token::IDENT)) {
        if (match(Token::OPEN_BRACKET)) {
            if (!expr()) return false;
            if (!match(Token::CLOSE_BRACKET)) return false;
        }
        return true;
    } else if (match(Token::OPEN_PAR)) {
        if (!expr()) return false;
        if (!match(Token::CLOSE_PAR)) return false;
        return true;
    }
    return false;
}

bool Parser::expr_list() {
    if (!expr()) return true; // Lista vacía
    while (match(Token::COMMA)) {
        if (!expr()) return false;
    }
    return true;
}



