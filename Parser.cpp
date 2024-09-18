#include "Parser.hpp"
#include "Ast.hpp"
#include <iostream>
#include <cstdlib>
#include <memory>
#include <vector>

void Parser::advance()
{
    currentToken = lexer.nextToken();
    currentText = lexer.tokenText();
    currentLine = lexer.getLine();
}

bool Parser::match(Token token)
{
    if (currentToken == token)
    {
        advance();
        return true;
    }
    return false;
}

void Parser::error(const std::string &expected)
{
    std::cerr << "Error: " << expected << " at line " << currentLine << ". Found: " << currentText << std::endl;
}

bool Parser::parse(double &result)
{
    if (!prg() || currentToken != Token::Eof)
    {
        error("Unexpected end of input or incomplete parse");
        return false;
    }
    return true;
}

std::shared_ptr<Program> Parser::prg()
{
    auto programNode = std::make_shared<Program>();

    while (currentToken == Token::KW_INT)
    {
        auto funcNode = func(); // Llamamos a `func()` que generará el nodo de función
        if (!funcNode)
            return nullptr;                         // Si hubo un error en la creación del nodo
        programNode->functions.push_back(funcNode); // Agregamos la función al nodo del programa
    }

    return programNode; // Retornamos el nodo raíz del AST
}

std::shared_ptr<FunctionDecl> Parser::func()
{
    if (!match(Token::KW_INT))
    {
        error("Expected 'int' at the beginning of function declaration");
        return nullptr;
    }

    auto funcNode = std::make_shared<FunctionDecl>(); // Nodo de función

    // Aquí guardamos el nombre del identificador antes de avanzar
    if (currentToken == Token::IDENT)
    {
        funcNode->name = currentText; // Guardamos el nombre de la función
        advance();                    // Luego avanzamos al siguiente token
    }
    else
    {
        error("Expected function name");
        return nullptr;
    }

    if (!match(Token::OPEN_PAR))
    {
        error("Expected '(' after function name");
        return nullptr;
    }

    if (!param_list(funcNode))
        return nullptr; // Llenamos los parámetros

    if (!match(Token::CLOSE_PAR))
    {
        error("Expected ')' after parameter list");
        return nullptr;
    }

    if (!match(Token::OPEN_CURLY))
    {
        error("Expected '{' to start function body");
        return nullptr;
    }

    while (currentToken == Token::KW_INT)
    {
        auto varDeclNode = var_decl(); // Procesamos las declaraciones de variables
        if (!varDeclNode)
            return nullptr;
        funcNode->varDecls.push_back(varDeclNode); // Agregamos las declaraciones de variables al nodo
    }

    while (currentToken != Token::CLOSE_CURLY)
    {
        auto stmtNode = stmt(); // Procesamos las sentencias dentro de la función
        if (!stmtNode)
            return nullptr;
        funcNode->statements.push_back(stmtNode); // Agregamos las sentencias al nodo de la función
    }

    if (!match(Token::CLOSE_CURLY))
    {
        error("Expected '}' at the end of function body");
        return nullptr;
    }

    return funcNode; // Devolvemos el nodo de la función
}

std::shared_ptr<VarDecl> Parser::var_decl()
{
    auto varDeclNode = std::make_shared<VarDecl>(); // Nodo de declaración de variable

    if (!match(Token::KW_INT))
    {
        error("Expected 'int' at the beginning of variable declaration");
        return nullptr;
    }

    do
    {
        std::string varName = currentText;
        bool isArray = false;

        if (!match(Token::IDENT))
        {
            error("Expected identifier in variable declaration");
            return nullptr;
        }

        if (match(Token::OPEN_BRACKET))
        {
            isArray = true;
            std::string arraySize = currentText;
            if (!match(Token::NUMBER))
            {
                error("Expected number inside brackets for array size");
                return nullptr;
            }
            if (!match(Token::CLOSE_BRACKET))
            {
                error("Expected closing bracket after array size");
                return nullptr;
            }
            varDeclNode->varNames.push_back({varName + "[" + arraySize + "]", isArray}); // Agregar tamaño al nombre
        }
        else
        {
            varDeclNode->varNames.push_back({varName, isArray});
        }
    } while (match(Token::COMMA)); // Permitimos múltiples declaraciones

    if (!match(Token::SEMICOLON))
    {
        error("Expected semicolon after variable declaration");
        return nullptr;
    }

    return varDeclNode; // Retornamos el nodo de declaración de variables
}

bool Parser::ident_decl()
{
    if (match(Token::AMPERSAND))
    {
        if (!match(Token::IDENT))
        {
            error("Expected identifier after & in variable declaration");
            return false;
        }
        return true;
    }

    if (!match(Token::IDENT))
    {
        error("Expected identifier in variable declaration");
        return false;
    }

    if (match(Token::OPEN_BRACKET))
    {
        if (match(Token::NUMBER))
        {
        }
        if (!match(Token::CLOSE_BRACKET))
        {
            error("Expected closing bracket after array size");
            return false;
        }
    }

    return true;
}

bool Parser::param_list(std::shared_ptr<FunctionDecl> funcNode)
{
    if (match(Token::KW_INT))
    {
        if (!param(funcNode))
            return false;
        while (match(Token::COMMA))
        {
            if (match(Token::KW_INT))
            {
                if (!param(funcNode))
                    return false;
            }
        }
    }
    return true;
}

bool Parser::param(std::shared_ptr<FunctionDecl> funcNode)
{
    bool isRef = match(Token::AMPERSAND); // Verificamos si el parámetro es por referencia
    std::string paramName = currentText;
    if (!match(Token::IDENT))
    {
        error("Expected identifier in parameter declaration");
        return false;
    }

    bool isArray = false;

    // Si el parámetro es un arreglo
    if (match(Token::OPEN_BRACKET))
    {
        isArray = true;
        // Soportamos tanto `[]` como `[n]` en la declaración de parámetros
        if (match(Token::NUMBER))
        {
            // Simplemente avanzamos; no necesitamos guardar el tamaño del arreglo en los parámetros
        }
        if (!match(Token::CLOSE_BRACKET))
        {
            error("Expected closing bracket ']' after array size in parameter declaration");
            return false;
        }
    }

    // Agregamos el parámetro con toda la información: nombre, si es por referencia y si es un arreglo
    funcNode->parameters.push_back({paramName, isRef}); // isRef solo indica si es por referencia
    funcNode->isArrayParam.push_back(isArray);         // Almacenamos si es un arreglo por separado
    return true;
}

std::shared_ptr<Statement> Parser::stmt()
{
    if (currentToken == Token::IDENT)
    {
        std::string identifier = currentText;
        advance();

        // Verifica si es un acceso a arreglo
        if (match(Token::OPEN_BRACKET))
        {
            auto arrayAccess = std::make_shared<ArrayAccessExpr>();
            arrayAccess->arrayName = std::make_shared<LiteralExpr>();
            arrayAccess->arrayName->type = LiteralExpr::IDENTIFIER;
            arrayAccess->arrayName->value = identifier;

            arrayAccess->index = expr(); // La expresión que evalúa el índice
            if (!arrayAccess->index)
            {
                error("Expected expression inside brackets for array access");
                return nullptr;
            }
            if (!match(Token::CLOSE_BRACKET))
            {
                error("Expected closing bracket after array index");
                return nullptr;
            }

            // Ahora manejamos la asignación al arreglo
            if (match(Token::OP_ASSIGN))
            {
                auto assignStmt = std::make_shared<AssignStmt>();
                assignStmt->identifier = identifier;
                assignStmt->indexExpr = arrayAccess->index; // Guardamos el índice del arreglo

                assignStmt->assignExpr = expr(); // Procesamos la expresión de la asignación
                if (!assignStmt->assignExpr)
                {
                    error("Expected expression after '=' in array assignment");
                    return nullptr;
                }

                if (!match(Token::SEMICOLON))
                {
                    error("Expected ';' after array assignment");
                    return nullptr;
                }

                return assignStmt; // Retornamos el nodo de asignación
            }

            error("Expected '=' after array access");
            return nullptr;
        }

        // Verifica si es una llamada a función
        if (match(Token::OPEN_PAR))
        {
            auto callStmt = std::make_shared<CallStmt>();
            callStmt->identifier = identifier;

            // Llenamos el vector de argumentos de la función
            callStmt->callArgs = expr_list(); // Aquí se utiliza la lista de expresiones para los argumentos

            if (!match(Token::CLOSE_PAR))
            {
                error("Expected ')' after function call");
                return nullptr;
            }

            if (!match(Token::SEMICOLON))
            {
                error("Expected ';' after function call");
                return nullptr;
            }

            return callStmt; // Retornamos el nodo de la llamada a la función
        }

        // Si no es una llamada a función ni acceso a arreglo, debe ser una asignación
        if (!match(Token::OP_ASSIGN))
        {
            error("Expected '=' after identifier");
            return nullptr;
        }
        auto assignStmt = std::make_shared<AssignStmt>();
        assignStmt->identifier = identifier;
        assignStmt->assignExpr = expr(); // La expresión de asignación
        if (!assignStmt->assignExpr)
        {
            error("Expected expression after '='");
            return nullptr;
        }
        if (!match(Token::SEMICOLON))
        {
            error("Expected ';' after assignment");
            return nullptr;
        }
        return assignStmt;
    }
    else if (match(Token::KW_IF))
    {
        auto ifStmt = std::make_shared<IfStmt>();

        if (!match(Token::OPEN_PAR))
        {
            error("Expected '(' after 'if'");
            return nullptr;
        }

        ifStmt->condition = expr();
        if (!ifStmt->condition)
        {
            error("Expected expression in 'if' condition");
            return nullptr;
        }

        if (!match(Token::CLOSE_PAR))
        {
            error("Expected ')' after 'if' condition");
            return nullptr;
        }

        if (!match(Token::OPEN_CURLY))
        {
            error("Expected '{' to start 'if' body");
            return nullptr;
        }

        // Procesamos las sentencias dentro del bloque 'then'
        while (currentToken != Token::CLOSE_CURLY)
        {
            auto thenStmt = stmt();
            if (!thenStmt)
                return nullptr;
            ifStmt->thenBranch.push_back(thenStmt);
        }

        if (!match(Token::CLOSE_CURLY))
        {
            error("Expected '}' to close 'if' body");
            return nullptr;
        }

        // Procesamos el bloque 'else' si existe
        if (match(Token::KW_ELSE))
        {
            if (!match(Token::OPEN_CURLY))
            {
                error("Expected '{' to start 'else' body");
                return nullptr;
            }

            while (currentToken != Token::CLOSE_CURLY)
            {
                auto elseStmt = stmt();
                if (!elseStmt)
                    return nullptr;
                ifStmt->elseBranch.push_back(elseStmt);
            }

            if (!match(Token::CLOSE_CURLY))
            {
                error("Expected '}' to close 'else' body");
                return nullptr;
            }
        }

        return ifStmt; // Devolvemos el nodo 'if'
    }
    else if (match(Token::KW_WHILE))
    {
        auto whileStmt = std::make_shared<WhileStmt>();

        if (!match(Token::OPEN_PAR))
        {
            error("Expected '(' after 'while'");
            return nullptr;
        }

        whileStmt->condition = expr();
        if (!whileStmt->condition)
        {
            error("Expected expression in 'while' condition");
            return nullptr;
        }

        if (!match(Token::CLOSE_PAR))
        {
            error("Expected ')' after 'while' condition");
            return nullptr;
        }

        if (!match(Token::OPEN_CURLY))
        {
            error("Expected '{' to start 'while' body");
            return nullptr;
        }

        // Procesamos las sentencias dentro del bloque 'while'
        while (currentToken != Token::CLOSE_CURLY)
        {
            auto bodyStmt = stmt();
            if (!bodyStmt)
                return nullptr;
            whileStmt->body.push_back(bodyStmt);
        }

        if (!match(Token::CLOSE_CURLY))
        {
            error("Expected '}' to close 'while' body");
            return nullptr;
        }

        return whileStmt; // Devolvemos el nodo 'while'
    }
    else if (match(Token::KW_COUT))
    {
        auto callStmt = std::make_shared<CallStmt>();
        callStmt->identifier = "cout";

        while (match(Token::LT_LT))
        {
            auto arg = cout_arg();
            if (!arg)
                return nullptr;
            callStmt->callArgs.push_back(arg);
        }

        if (!match(Token::SEMICOLON))
        {
            error("Expected ';' after 'cout' statement");
            return nullptr;
        }

        return callStmt; // Devolvemos el nodo 'cout'
    }
    else if (match(Token::KW_CIN))
    {
        auto callStmt = std::make_shared<CallStmt>();
        callStmt->identifier = "cin";

        if (!match(Token::GT_GT))
        {
            error("Expected '>>' after 'cin'");
            return nullptr;
        }

        while (true)
        {
            std::string id = currentText;
            if (!match(Token::IDENT))
            {
                error("Expected identifier after '>>' in 'cin'");
                return nullptr;
            }

            auto arg = std::make_shared<LiteralExpr>();
            arg->type = LiteralExpr::IDENTIFIER;
            arg->value = id;
            callStmt->callArgs.push_back(arg);

            if (!match(Token::GT_GT))
            {
                break; // Salimos del bucle cuando no hay más '>>'
            }
        }

        if (!match(Token::SEMICOLON))
        {
            error("Expected ';' after 'cin' statement");
            return nullptr;
        }

        return callStmt; // Devolvemos el nodo 'cin'
    }

    error("Unexpected token");
    return nullptr;
}

std::shared_ptr<Expression> Parser::cout_arg()
{
    if (currentToken == Token::STRING_LITERAL) // Verificamos sin avanzar
    {
        std::cout << "String Literal Found: " << currentText << std::endl;
        auto literal = std::make_shared<LiteralExpr>();
        literal->type = LiteralExpr::STRING;
        literal->value = currentText; // Capturamos el valor antes de avanzar
        advance();                    // Ahora avanzamos
        return literal;
    }
    else if (match(Token::KW_ENDL))
    {
        // Manejamos `endl` como un caso especial si es necesario
        auto literal = std::make_shared<LiteralExpr>();
        literal->type = LiteralExpr::IDENTIFIER;
        literal->value = "endl";
        return literal;
    }
    else
    {
        return expr(); // Manejamos expresiones como argumentos
    }
}

std::shared_ptr<Expression> Parser::expr()
{
    auto left = bool_term();

    if (!left)
    {
        error("Expected boolean term");
        return nullptr;
    }

    while (currentToken == Token::BOOL_OR)
    {
        int oper = currentToken; // Guardamos el operador lógico
        advance();               // Avanzamos al siguiente token

        auto binExpr = std::make_shared<BinaryExpr>();
        binExpr->oper = oper; // Asignamos el operador guardado

        auto right = bool_term();
        if (!right)
        {
            error("Expected boolean term after '||'");
            return nullptr;
        }

        binExpr->left = left;
        binExpr->right = right;
        left = binExpr;
    }

    if (currentToken == Token::CLOSE_PAR)
    {
        return left;
    }

    return left; // Retornamos la expresión resultante
}

std::shared_ptr<Expression> Parser::bool_term()
{
    auto left = rel_expr();
    if (!left)
    {
        error("Expected relational expression");
        return nullptr;
    }

    while (currentToken == Token::BOOL_AND)
    {
        int oper = currentToken; // Guardamos el operador lógico
        advance();               // Avanzamos al siguiente token

        auto binExpr = std::make_shared<BinaryExpr>();
        binExpr->oper = oper; // Asignamos el operador guardado

        auto right = rel_expr();
        if (!right)
        {
            error("Expected relational expression after '&&'");
            return nullptr;
        }

        binExpr->left = left;
        binExpr->right = right;
        left = binExpr;
    }

    if (currentToken == Token::CLOSE_PAR)
    {
        return left;
    }

    return left;
}

std::shared_ptr<Expression> Parser::rel_expr()
{
    auto left = arith_expr();
    if (!left)
    {
        error("Expected arithmetic expression");
        return nullptr;
    }
    if (currentToken == Token::GT || currentToken == Token::LT || currentToken == Token::GTE || currentToken == Token::LTE || currentToken == Token::NE || currentToken == Token::EQ)
    {
        int oper = currentToken; // Guardamos el operador relacional
        advance();               // Avanzamos al siguiente token

        auto binExpr = std::make_shared<BinaryExpr>();
        binExpr->oper = oper; // Asignamos el operador guardado

        auto right = arith_expr();
        if (!right)
        {
            error("Expected arithmetic expression after relational operator");
            return nullptr;
        }

        binExpr->left = left;
        binExpr->right = right;
        return binExpr;
    }
    if (currentToken == Token::CLOSE_PAR)
    {
        return left;
    }

    return left; // Si no hay operador relacional, retornamos la expresión aritmética
}

std::shared_ptr<Expression> Parser::arith_expr()
{
    auto left = arith_term();
    if (!left)
    {
        error("Expected arithmetic term");
        return nullptr;
    }

    while (currentToken == Token::OP_ADD || currentToken == Token::OP_SUB)
    {
        int oper = currentToken; // Guardamos el operador actual
        advance();               // Avanzamos al siguiente token

        auto binExpr = std::make_shared<BinaryExpr>();
        binExpr->oper = oper; // Asignamos el operador guardado

        auto right = arith_term();
        if (!right)
        {
            error("Expected arithmetic term after operator");
            return nullptr;
        }

        binExpr->left = left;
        binExpr->right = right;
        left = binExpr;
    }

    if (currentToken == Token::CLOSE_PAR)
    {
        return left;
    }

    return left;
}

std::shared_ptr<Expression> Parser::arith_term()
{
    auto left = arith_factor();
    if (!left)
    {
        error("Expected arithmetic factor");
        return nullptr;
    }

    while (currentToken == Token::OP_MULT || currentToken == Token::OP_DIV || currentToken == Token::OP_MOD)
    {
        int oper = currentToken; // Guardamos el operador actual
        advance();               // Avanzamos al siguiente token

        auto binExpr = std::make_shared<BinaryExpr>();
        binExpr->oper = oper; // Asignamos el operador guardado

        auto right = arith_factor();
        if (!right)
        {
            error("Expected arithmetic factor after operator");
            return nullptr;
        }

        binExpr->left = left;
        binExpr->right = right;
        left = binExpr;
    }

    if (currentToken == Token::CLOSE_PAR)
    {
        return left;
    }

    return left;
}

std::shared_ptr<Expression> Parser::arith_factor()
{
    // Guardamos el valor de currentText antes de hacer el match
    if (currentToken == Token::NUMBER)
    {
        std::string value = currentText; // Guardamos el valor del número
        if (match(Token::NUMBER))
        {
            auto literal = std::make_shared<LiteralExpr>();
            literal->type = LiteralExpr::NUMBER;
            literal->value = value; // Asignamos el valor guardado
            return literal;
        }
    }
    else if (currentToken == Token::IDENT)
    {
        std::string value = currentText; // Guardamos el valor del identificador
        if (match(Token::IDENT))
        {
            auto literal = std::make_shared<LiteralExpr>();
            literal->type = LiteralExpr::IDENTIFIER;
            literal->value = value; // Asignamos el nombre del identificador

            // Verificamos si es un acceso a arreglo
            if (match(Token::OPEN_BRACKET))
            {
                auto indexExpr = expr();
                if (!indexExpr)
                {
                    error("Expected expression inside brackets");
                    return nullptr;
                }
                if (!match(Token::CLOSE_BRACKET))
                {
                    error("Expected closing bracket after expression");
                    return nullptr;
                }

                auto arrayAccess = std::make_shared<ArrayAccessExpr>();
                arrayAccess->arrayName = literal; // Guardamos el nombre del arreglo
                arrayAccess->index = indexExpr;   // Guardamos la expresión del índice
                return arrayAccess;               // Retornamos el nodo de acceso a arreglo
            }
            return literal;
        }
    }
    else if (match(Token::OPEN_PAR))
    {
        auto subExpr = expr(); // Evaluamos la expresión dentro de los paréntesis
        if (!subExpr)
        {
            error("Expected expression inside parentheses");
            return nullptr;
        }
        if (!match(Token::CLOSE_PAR))
        {
            error("Expected closing parenthesis");
            return nullptr;
        }
        return subExpr;
    }

    error("Expected number, identifier, or expression");
    return nullptr;
}

std::vector<std::shared_ptr<Expression>> Parser::expr_list()
{
    std::vector<std::shared_ptr<Expression>> expressions;

    // Evaluamos la primera expresión
    auto firstExpr = expr();
    if (!firstExpr)
    {
        return expressions; // Si no hay expresión, devolvemos una lista vacía (es válida)
    }
    expressions.push_back(firstExpr); // Agregamos la primera expresión

    // Mientras haya comas, continuamos procesando expresiones adicionales
    while (match(Token::COMMA))
    {
        auto nextExpr = expr(); // Evaluamos la siguiente expresión
        if (!nextExpr)
        {
            error("Expected expression after ','");
            return {}; // Si ocurre un error, devolvemos un vector vacío como señal de fallo
        }
        expressions.push_back(nextExpr); // Agregamos la siguiente expresión
    }

    return expressions; // Retornamos todas las expresiones evaluadas
}

/*bool Parser::type() {
    if (match(Token::KW_INT)) {
        if (match(Token::OPEN_BRACKET)) {
            if (!match(Token::NUMBER)) {
                error("Expected number inside brackets");
                return false;
            }
            if (!match(Token::CLOSE_BRACKET)) {
                error("Expected closing bracket after array size");
                return false;
            }
        }
        return true;
    }
    error("Expected type");
    return false;
}*/

/*bool Parser::var_decl() {
    if (!type()) {
        error("Expected type in variable declaration");
        return false;
    }

    do {
        if (!match(Token::IDENT)) {
            error("Expected identifier after type in variable declaration");
            return false;
        }

        if (match(Token::OPEN_BRACKET)) {
            if (!match(Token::NUMBER)) {
                error("Expected number inside brackets in array declaration");
                return false;
            }

            if (!match(Token::CLOSE_BRACKET)) {
                error("Expected closing bracket after array size in array declaration");
                return false;
            }
        }

    } while (match(Token::COMMA)); // Para manejar múltiples declaraciones en una línea

    if (!match(Token::SEMICOLON)) {
        error("Expected semicolon after variable declaration");
        return false;
    }

    return true;
}*/

/*bool Parser::func_call()
{
    if (!match(Token::IDENT))
    {
        error("Expected function name");
        return false;
    }

    if (!match(Token::OPEN_PAR))
    {
        error("Expected '(' after function name");
        return false;
    }`

    if (!expr_list())
    {
        return false;
    }

    if (!match(Token::CLOSE_PAR))
    {
        error("Expected ')' after function arguments");
        return false;
    }

    return true;
}*/