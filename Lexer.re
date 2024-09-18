#include <cstring>
#include "Lexer.hpp"

/*!max:re2c*/

Lexer::DataBuffer::DataBuffer(std::ifstream &in)
    : in(in),
      buf(new char[SIZE + YYMAXFILL]), 
      lim(buf + SIZE),
      cur(lim),
      tok(lim),
      eof(false)
{
}

bool Lexer::DataBuffer::fill(size_t need)
{
    if (eof)
        return false;

    const size_t free = tok - buf;
    if (free < need)
        return false;

    memmove(buf, tok, lim - tok);
    lim -= free;
    cur -= free;
    tok -= free;

    in.read(lim, free);
    lim += in.gcount();

    if (lim < buf + SIZE)
    {
        eof = true;
        memset(lim, 0, YYMAXFILL);
        lim += YYMAXFILL;
    }
    return true;
}

Token Lexer::nextToken()
{
    while (true) {
        db.tok = db.cur;
        /*!re2c
            re2c:define:YYCTYPE = char;
            re2c:define:YYCURSOR = db.cur;
            re2c:define:YYLIMIT = db.lim;
            re2c:define:YYMARKER = db.mark;
            re2c:define:YYFILL = "if (!db.fill(@@)) return Token::Error;";
            re2c:define:YYFILL:naked = 1;

            end = "\x00";
            wsp = [ \t]+;
            newline = '\n';
            num = [0-9]+; 
            id = [a-zA-Z_][a-zA-Z0-9_]*;
            str_lit = "\"" [^\"]* "\"";
            line_comment = "//" [^\n]*;
            block_comment = "/*" ([^*] | "*" [^/])* "*/";

            * { return Token::Other; }
            end { return (YYMAXFILL == db.lim - db.tok)? Token::Eof : Token::Error;}
            
            wsp {continue;}
            newline {++line; continue;}
            line_comment { ++line; continue; }
            block_comment { 
                for (char *p = db.tok; p < db.cur; ++p) {
                    if (*p == '\n') {
                        line++;
                    }
                }
                continue; 
            }

            'int' { text = db.tokenText(); return Token::KW_INT; }
            'if' { text = db.tokenText(); return Token::KW_IF; }
            'else' { text = db.tokenText(); return Token::KW_ELSE; }
            'while' { text = db.tokenText(); return Token::KW_WHILE; }
            'std::cout' { text = db.tokenText(); return Token::KW_COUT; }
            'std::cin' { text = db.tokenText(); return Token::KW_CIN; }
            'std::endl' { text = db.tokenText(); return Token::KW_ENDL; }

            '=' { text = db.tokenText(); return Token::OP_ASSIGN; }
            '+' { text = db.tokenText(); return Token::OP_ADD; }
            '-' { text = db.tokenText(); return Token::OP_SUB; }
            '*' { text = db.tokenText(); return Token::OP_MULT; }
            '/' { text = db.tokenText(); return Token::OP_DIV; }
            '%' { text = db.tokenText(); return Token::OP_MOD; }
            '>' { text = db.tokenText(); return Token::GT; }
            '<' { text = db.tokenText(); return Token::LT; }
            '>=' { text = db.tokenText(); return Token::GTE; }
            '<=' { text = db.tokenText(); return Token::LTE; }
            '!=' { text = db.tokenText(); return Token::NE; }
            '==' { text = db.tokenText(); return Token::EQ; }
            '||' { text = db.tokenText(); return Token::BOOL_OR; }
            '&&' { text = db.tokenText(); return Token::BOOL_AND; }
            '<<' { text = db.tokenText(); return Token::LT_LT; }
            '>>' { text = db.tokenText(); return Token::GT_GT; }

            id { text = db.tokenText(); return Token::IDENT; }

            str_lit { text = db.tokenText(); return Token::STRING_LITERAL; }

            '(' { text = db.tokenText(); return Token::OPEN_PAR; }
            ')' { text = db.tokenText(); return Token::CLOSE_PAR; }
            '{' { text = db.tokenText(); return Token::OPEN_CURLY; }
            '}' { text = db.tokenText(); return Token::CLOSE_CURLY; }
            '[' { text = db.tokenText(); return Token::OPEN_BRACKET; }
            ']' { text = db.tokenText(); return Token::CLOSE_BRACKET; }
            ',' { text = db.tokenText(); return Token::COMMA; }

            num { text = db.tokenText(); return Token::NUMBER; }
            ';' { text = db.tokenText(); return Token::SEMICOLON; }
            '&' { text = db.tokenText(); return Token::AMPERSAND; }
        */     
    }
}