/* Generated by re2c 3.0 on Sat Aug 17 02:40:28 2024 */
#line 1 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
#include <cstring>
#include "Lexer.hpp"

#line 7 "LexerImpl.cpp"
#define YYMAXFILL 9
#line 4 "/home/oscar/Compiladores3/MiniC++/Lexer.re"


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
        
#line 53 "LexerImpl.cpp"
{
	char yych;
	if ((db.lim - db.cur) < 9) if (!db.fill(9)) return Token::Error;
	yych = *db.cur;
	switch (yych) {
		case 0x00: goto yy1;
		case '\t':
		case ' ': goto yy4;
		case '\n': goto yy6;
		case '!': goto yy7;
		case '"': goto yy8;
		case '%': goto yy9;
		case '&': goto yy10;
		case '(': goto yy12;
		case ')': goto yy13;
		case '*': goto yy14;
		case '+': goto yy15;
		case ',': goto yy16;
		case '-': goto yy17;
		case '/': goto yy18;
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy20;
		case ';': goto yy22;
		case '<': goto yy23;
		case '=': goto yy25;
		case '>': goto yy27;
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'F':
		case 'G':
		case 'H':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'T':
		case 'U':
		case 'V':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'f':
		case 'g':
		case 'h':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 't':
		case 'u':
		case 'v':
		case 'x':
		case 'y':
		case 'z': goto yy29;
		case 'E':
		case 'e': goto yy32;
		case 'I':
		case 'i': goto yy33;
		case 'S':
		case 's': goto yy34;
		case 'W':
		case 'w': goto yy35;
		case '[': goto yy36;
		case ']': goto yy37;
		case '{': goto yy38;
		case '|': goto yy39;
		case '}': goto yy40;
		default: goto yy2;
	}
yy1:
	++db.cur;
#line 64 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ return (YYMAXFILL == db.lim - db.tok)? Token::Eof : Token::Error;}
#line 152 "LexerImpl.cpp"
yy2:
	++db.cur;
yy3:
#line 63 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ return Token::Other; }
#line 158 "LexerImpl.cpp"
yy4:
	++db.cur;
	if (db.lim <= db.cur) if (!db.fill(1)) return Token::Error;
	yych = *db.cur;
	switch (yych) {
		case '\t':
		case ' ': goto yy4;
		default: goto yy5;
	}
yy5:
#line 66 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{continue;}
#line 171 "LexerImpl.cpp"
yy6:
	++db.cur;
#line 67 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{++line; continue;}
#line 176 "LexerImpl.cpp"
yy7:
	yych = *++db.cur;
	switch (yych) {
		case '=': goto yy41;
		default: goto yy3;
	}
yy8:
	++db.cur;
	if (db.lim <= db.cur) if (!db.fill(1)) return Token::Error;
	yych = *db.cur;
	switch (yych) {
		case '"': goto yy42;
		default: goto yy8;
	}
yy9:
	++db.cur;
#line 91 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::OP_MOD; }
#line 195 "LexerImpl.cpp"
yy10:
	yych = *++db.cur;
	switch (yych) {
		case '&': goto yy43;
		default: goto yy11;
	}
yy11:
#line 117 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::AMPERSAND; }
#line 205 "LexerImpl.cpp"
yy12:
	++db.cur;
#line 107 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::OPEN_PAR; }
#line 210 "LexerImpl.cpp"
yy13:
	++db.cur;
#line 108 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::CLOSE_PAR; }
#line 215 "LexerImpl.cpp"
yy14:
	++db.cur;
#line 89 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::OP_MULT; }
#line 220 "LexerImpl.cpp"
yy15:
	++db.cur;
#line 87 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::OP_ADD; }
#line 225 "LexerImpl.cpp"
yy16:
	++db.cur;
#line 113 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::COMMA; }
#line 230 "LexerImpl.cpp"
yy17:
	++db.cur;
#line 88 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::OP_SUB; }
#line 235 "LexerImpl.cpp"
yy18:
	yych = *++db.cur;
	switch (yych) {
		case '*': goto yy44;
		case '/': goto yy45;
		default: goto yy19;
	}
yy19:
#line 90 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::OP_DIV; }
#line 246 "LexerImpl.cpp"
yy20:
	++db.cur;
	if (db.lim <= db.cur) if (!db.fill(1)) return Token::Error;
	yych = *db.cur;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9': goto yy20;
		default: goto yy21;
	}
yy21:
#line 115 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::NUMBER; }
#line 267 "LexerImpl.cpp"
yy22:
	++db.cur;
#line 116 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::SEMICOLON; }
#line 272 "LexerImpl.cpp"
yy23:
	yych = *++db.cur;
	switch (yych) {
		case '<': goto yy47;
		case '=': goto yy48;
		default: goto yy24;
	}
yy24:
#line 93 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::LT; }
#line 283 "LexerImpl.cpp"
yy25:
	yych = *++db.cur;
	switch (yych) {
		case '=': goto yy49;
		default: goto yy26;
	}
yy26:
#line 86 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::OP_ASSIGN; }
#line 293 "LexerImpl.cpp"
yy27:
	yych = *++db.cur;
	switch (yych) {
		case '=': goto yy50;
		case '>': goto yy51;
		default: goto yy28;
	}
yy28:
#line 92 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::GT; }
#line 304 "LexerImpl.cpp"
yy29:
	++db.cur;
	if (db.lim <= db.cur) if (!db.fill(1)) return Token::Error;
	yych = *db.cur;
yy30:
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z': goto yy29;
		default: goto yy31;
	}
yy31:
#line 103 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::IDENT; }
#line 379 "LexerImpl.cpp"
yy32:
	yych = *++db.cur;
	switch (yych) {
		case 'L':
		case 'l': goto yy52;
		default: goto yy30;
	}
yy33:
	yych = *++db.cur;
	switch (yych) {
		case 'F':
		case 'f': goto yy53;
		case 'N':
		case 'n': goto yy55;
		default: goto yy30;
	}
yy34:
	yych = *++db.cur;
	switch (yych) {
		case 'T':
		case 't': goto yy56;
		default: goto yy30;
	}
yy35:
	yych = *++db.cur;
	switch (yych) {
		case 'H':
		case 'h': goto yy57;
		default: goto yy30;
	}
yy36:
	++db.cur;
#line 111 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::OPEN_BRACKET; }
#line 414 "LexerImpl.cpp"
yy37:
	++db.cur;
#line 112 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::CLOSE_BRACKET; }
#line 419 "LexerImpl.cpp"
yy38:
	++db.cur;
#line 109 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::OPEN_CURLY; }
#line 424 "LexerImpl.cpp"
yy39:
	yych = *++db.cur;
	switch (yych) {
		case '|': goto yy58;
		default: goto yy3;
	}
yy40:
	++db.cur;
#line 110 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::CLOSE_CURLY; }
#line 435 "LexerImpl.cpp"
yy41:
	++db.cur;
#line 96 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::NE; }
#line 440 "LexerImpl.cpp"
yy42:
	++db.cur;
#line 105 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::STRING_LITERAL; }
#line 445 "LexerImpl.cpp"
yy43:
	++db.cur;
#line 99 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::BOOL_AND; }
#line 450 "LexerImpl.cpp"
yy44:
	++db.cur;
	if (db.lim <= db.cur) if (!db.fill(1)) return Token::Error;
	yych = *db.cur;
	switch (yych) {
		case '*': goto yy59;
		default: goto yy44;
	}
yy45:
	++db.cur;
	if (db.lim <= db.cur) if (!db.fill(1)) return Token::Error;
	yych = *db.cur;
	switch (yych) {
		case '\n': goto yy46;
		default: goto yy45;
	}
yy46:
#line 68 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ ++line; continue; }
#line 470 "LexerImpl.cpp"
yy47:
	++db.cur;
#line 100 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::LT_LT; }
#line 475 "LexerImpl.cpp"
yy48:
	++db.cur;
#line 95 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::LTE; }
#line 480 "LexerImpl.cpp"
yy49:
	++db.cur;
#line 97 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::EQ; }
#line 485 "LexerImpl.cpp"
yy50:
	++db.cur;
#line 94 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::GTE; }
#line 490 "LexerImpl.cpp"
yy51:
	++db.cur;
#line 101 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::GT_GT; }
#line 495 "LexerImpl.cpp"
yy52:
	yych = *++db.cur;
	switch (yych) {
		case 'S':
		case 's': goto yy60;
		default: goto yy30;
	}
yy53:
	yych = *++db.cur;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z': goto yy29;
		default: goto yy54;
	}
yy54:
#line 79 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::KW_IF; }
#line 574 "LexerImpl.cpp"
yy55:
	yych = *++db.cur;
	switch (yych) {
		case 'T':
		case 't': goto yy61;
		default: goto yy30;
	}
yy56:
	yych = *++db.cur;
	switch (yych) {
		case 'D':
		case 'd': goto yy63;
		default: goto yy30;
	}
yy57:
	yych = *++db.cur;
	switch (yych) {
		case 'I':
		case 'i': goto yy64;
		default: goto yy30;
	}
yy58:
	++db.cur;
#line 98 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::BOOL_OR; }
#line 600 "LexerImpl.cpp"
yy59:
	++db.cur;
	if (db.lim <= db.cur) if (!db.fill(1)) return Token::Error;
	yych = *db.cur;
	switch (yych) {
		case '/': goto yy65;
		default: goto yy44;
	}
yy60:
	yych = *++db.cur;
	switch (yych) {
		case 'E':
		case 'e': goto yy66;
		default: goto yy30;
	}
yy61:
	yych = *++db.cur;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z': goto yy29;
		default: goto yy62;
	}
yy62:
#line 78 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::KW_INT; }
#line 687 "LexerImpl.cpp"
yy63:
	yych = *(db.mark = ++db.cur);
	switch (yych) {
		case ':': goto yy68;
		default: goto yy30;
	}
yy64:
	yych = *++db.cur;
	switch (yych) {
		case 'L':
		case 'l': goto yy70;
		default: goto yy30;
	}
yy65:
	++db.cur;
#line 69 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ 
                for (char *p = db.tok; p < db.cur; ++p) {
                    if (*p == '\n') {
                        line++;
                    }
                }
                continue; 
            }
#line 712 "LexerImpl.cpp"
yy66:
	yych = *++db.cur;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z': goto yy29;
		default: goto yy67;
	}
yy67:
#line 80 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::KW_ELSE; }
#line 784 "LexerImpl.cpp"
yy68:
	yych = *++db.cur;
	switch (yych) {
		case ':': goto yy71;
		default: goto yy69;
	}
yy69:
	db.cur = db.mark;
	goto yy31;
yy70:
	yych = *++db.cur;
	switch (yych) {
		case 'E':
		case 'e': goto yy72;
		default: goto yy30;
	}
yy71:
	yych = *++db.cur;
	switch (yych) {
		case 'C':
		case 'c': goto yy74;
		case 'E':
		case 'e': goto yy75;
		default: goto yy69;
	}
yy72:
	yych = *++db.cur;
	switch (yych) {
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '_':
		case 'a':
		case 'b':
		case 'c':
		case 'd':
		case 'e':
		case 'f':
		case 'g':
		case 'h':
		case 'i':
		case 'j':
		case 'k':
		case 'l':
		case 'm':
		case 'n':
		case 'o':
		case 'p':
		case 'q':
		case 'r':
		case 's':
		case 't':
		case 'u':
		case 'v':
		case 'w':
		case 'x':
		case 'y':
		case 'z': goto yy29;
		default: goto yy73;
	}
yy73:
#line 81 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::KW_WHILE; }
#line 881 "LexerImpl.cpp"
yy74:
	yych = *++db.cur;
	switch (yych) {
		case 'I':
		case 'i': goto yy76;
		case 'O':
		case 'o': goto yy77;
		default: goto yy69;
	}
yy75:
	yych = *++db.cur;
	switch (yych) {
		case 'N':
		case 'n': goto yy78;
		default: goto yy69;
	}
yy76:
	yych = *++db.cur;
	switch (yych) {
		case 'N':
		case 'n': goto yy79;
		default: goto yy69;
	}
yy77:
	yych = *++db.cur;
	switch (yych) {
		case 'U':
		case 'u': goto yy80;
		default: goto yy69;
	}
yy78:
	yych = *++db.cur;
	switch (yych) {
		case 'D':
		case 'd': goto yy81;
		default: goto yy69;
	}
yy79:
	++db.cur;
#line 83 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::KW_CIN; }
#line 923 "LexerImpl.cpp"
yy80:
	yych = *++db.cur;
	switch (yych) {
		case 'T':
		case 't': goto yy82;
		default: goto yy69;
	}
yy81:
	yych = *++db.cur;
	switch (yych) {
		case 'L':
		case 'l': goto yy83;
		default: goto yy69;
	}
yy82:
	++db.cur;
#line 82 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::KW_COUT; }
#line 942 "LexerImpl.cpp"
yy83:
	++db.cur;
#line 84 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
	{ text = db.tokenText(); return Token::KW_ENDL; }
#line 947 "LexerImpl.cpp"
}
#line 118 "/home/oscar/Compiladores3/MiniC++/Lexer.re"
     
    }
}