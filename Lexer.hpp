#pragma once

#include <string>
#include <fstream>

enum Token
{
    //Keywords
    KW_INT,
    KW_IF,
    KW_ELSE,
    KW_WHILE,
    KW_COUT,
    KW_CIN,
    KW_ENDL,

    //Operadores
    OP_ASSIGN,     // '='
    OP_ADD,        // '+'
    OP_SUB,        // '-'
    OP_MULT,       // '*'
    OP_DIV,        // '/'
    OP_MOD,        // '%'
    GT,            // '>'
    LT,            // '<'
    GTE,           // '>='
    LTE,           // '<='
    NE,            // '!='
    EQ,            // '=='
    BOOL_OR,       // '||'
    BOOL_AND,      // '&&'
    LT_LT,         // '<<'
    GT_GT,         // '>>'

    //Identificadores
    IDENT,         // [a-zA-Z_][a-zA-Z0-9_]*

    //Literales
    STRING_LITERAL, // ".*" 

    //Delimitadores
    OPEN_PAR,      //(
    CLOSE_PAR,     //)
    OPEN_CURLY,    //{
    CLOSE_CURLY,   //}
    OPEN_BRACKET,  //[
    CLOSE_BRACKET, //]
    COMMA,         //,    

    //Otros
    NUMBER,        // [0-9]+
    SEMICOLON,     // ;
    AMPERSAND,     // &  
    Other,
    Error,
    Eof
};

class Lexer
{
public:
    static const size_t SIZE = 512;

    Lexer(std::ifstream &in) : db(in), line(1) {}

    Token nextToken();

    std::string tokenText() const { return text; }

    int getLine() const { return line; }

private:
    struct DataBuffer
    {
        char *buf;
        char *lim;
        char *cur;
        char *mark;
        char *tok;
        bool eof;
        std::ifstream &in;

        DataBuffer(std::ifstream &in);

        std::string tokenText() const { return std::string(tok, cur); }

        ~DataBuffer() { delete[] buf; }

        bool fill(size_t need);
    };

private:
    DataBuffer db;
    std::string text;
    int line;
};