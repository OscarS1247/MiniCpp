#include <iostream>
#include "Lexer.hpp"
#include "Parser.hpp"

int main(int argc, char **argv)
{

    if(argc != 2){
        std::cerr <<"Not enough arguments\n";
        return 1;
    }

    std::ifstream in(argv[1]);
    std::ifstream in2(argv[1]);

    if(!in.is_open() && !in2.is_open()){
        std::cerr <<"Cannot open file\n";
        return 1;
    }

    Lexer lex(in);
    Lexer lex2(in2);
    Parser parser(lex);
    double result;


    Token tk = lex2.nextToken();

    while (tk != Token::Error && tk != Token::Eof)
    {
        switch (tk)
        {
        case Token::Other:
            //std::cout<<"Other: "<<lex2.tokenText()<<"\n";
            break;
        case Token::KW_INT: 
            std::cout<<"KW_INT: "<<lex2.tokenText()<<"\n";
            break;
        case Token::KW_IF:
            std::cout<<"KW_IF: "<<lex2.tokenText()<<"\n";
            break;
        case Token::KW_ELSE:
            std::cout<<"KW_ELSE: "<<lex2.tokenText()<<"\n";
            break;
        case Token::KW_WHILE:
            std::cout<<"KW_WHILE: "<<lex2.tokenText()<<"\n";
            break;
        case Token::KW_COUT:
            std::cout<<"KW_COUT: "<<lex2.tokenText()<<"\n";
            break;
        case Token::KW_CIN:
            std::cout<<"KW_CIN: "<<lex2.tokenText()<<"\n";
            break;
        case Token::KW_ENDL:
            std::cout<<"KW_ENDL: "<<lex2.tokenText()<<"\n";
            break;
        case Token::OP_ASSIGN:
            std::cout<<"OP_ASSIGN: "<<lex2.tokenText()<<"\n";
            break;
        case Token::OP_ADD:
            std::cout<<"OP_ADD: "<<lex2.tokenText()<<"\n";
            break;
        case Token::OP_SUB:
            std::cout<<"OP_SUB: "<<lex2.tokenText()<<"\n";
            break;
        case Token::OP_MULT:
            std::cout<<"OP_MULT: "<<lex2.tokenText()<<"\n";
            break;
        case Token::OP_DIV:
            std::cout<<"OP_DIV: "<<lex2.tokenText()<<"\n";
            break;
        case Token::OP_MOD:
            std::cout<<"OP_MOD: "<<lex2.tokenText()<<"\n";
            break;
        case Token::GT:
            std::cout<<"GT: "<<lex2.tokenText()<<"\n";
            break;
        case Token::LT:
            std::cout<<"LT: "<<lex2.tokenText()<<"\n";
            break;
        case Token::GTE:
            std::cout<<"GTE: "<<lex2.tokenText()<<"\n";
            break;
        case Token::LTE:
            std::cout<<"LTE: "<<lex2.tokenText()<<"\n";
            break;
        case Token::NE:
            std::cout<<"NE: "<<lex2.tokenText()<<"\n";
            break;
        case Token::EQ: 
            std::cout<<"EQ: "<<lex2.tokenText()<<"\n";
            break;
        case Token::BOOL_OR:    
            std::cout<<"BOOL_OR: "<<lex2.tokenText()<<"\n";
            break;
        case Token::BOOL_AND:   
            std::cout<<"BOOL_AND: "<<lex2.tokenText()<<"\n";
            break;
        case Token::LT_LT:
            std::cout<<"LT_LT: "<<lex2.tokenText()<<"\n";
            break;
        case Token::GT_GT:
            std::cout<<"GT_GT: "<<lex2.tokenText()<<"\n";
            break;
        case Token::IDENT:
            std::cout<<"IDENT: "<<lex2.tokenText()<<"\n";
            break;
        case Token::STRING_LITERAL:
            std::cout<<"STRING_LITERAL: "<<lex2.tokenText()<<"\n";
            break;
        case Token::OPEN_PAR:
            std::cout<<"OPEN_PAR: "<<lex2.tokenText()<<"\n";
            break;
        case Token::CLOSE_PAR:
            std::cout<<"CLOSE_PAR: "<<lex2.tokenText()<<"\n";
            break;
        case Token::OPEN_CURLY:
            std::cout<<"OPEN_CURLY: "<<lex2.tokenText()<<"\n";
            break;
        case Token::CLOSE_CURLY:
            std::cout<<"CLOSE_CURLY: "<<lex2.tokenText()<<"\n";
            break;
        case Token::OPEN_BRACKET:
            std::cout<<"OPEN_BRACKET: "<<lex2.tokenText()<<"\n";
            break;
        case Token::CLOSE_BRACKET:
            std::cout<<"CLOSE_BRACKET: "<<lex2.tokenText()<<"\n";
            break;
        case Token::COMMA:
            std::cout<<"COMMA: "<<lex2.tokenText()<<"\n";
            break;
        case Token::NUMBER:
            std::cout<<"NUMBER: "<<lex2.tokenText()<<"\n";
            break;
        case Token::SEMICOLON:
            std::cout<<"SEMICOLON: "<<lex2.tokenText()<<"\n";
            break;
        case Token::AMPERSAND:
            std::cout<<"AMPERSAND: "<<lex2.tokenText()<<"\n";
            break;
        default:
            break;
        }
   
        tk = lex2.nextToken();
    }

    std::cout<<"Token: " <<static_cast<int>(tk)<<"\n";

    if (parser.parse(result)) {
        std::cout << "\nParsing successful! Result: " << result << "\n";
    } else {
        std::cerr << "\nParsing failed!\n";
    }

    return 0;
}