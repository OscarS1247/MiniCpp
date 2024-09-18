#ifndef AST_HPP
#define AST_HPP

#include <memory>
#include <vector>
#include <string>

// Base class for all AST nodes
class AstNode {
public:
    virtual ~AstNode() = default;
    virtual int kind() const = 0;
};

// Program node (root of the AST)
class Program : public AstNode {
public:
    std::vector<std::shared_ptr<AstNode>> functions;

    int kind() const override { return 1; }
};

// Function declaration node
class FunctionDecl : public AstNode {
public:
    std::string name;
    std::vector<std::pair<std::string, bool>> parameters; // Pair of parameter name and whether it is a reference
    std::vector<std::shared_ptr<AstNode>> varDecls;
    std::vector<std::shared_ptr<AstNode>> statements;
    std::vector<bool> isArrayParam;

    int kind() const override { return 2; }
};

// Variable declaration node
class VarDecl : public AstNode {
public:
    std::vector<std::pair<std::string, bool>> varNames; // Variable names and array status (if array, then true)

    int kind() const override { return 3; }
};

// Statement node (base class for all statements)
class Statement : public AstNode {
public:
    int kind() const override { return 4; }
};

// Expression node (base class for all expressions)
class Expression : public Statement {
public:
    int kind() const override { return 5; }
};

// If statement node
class IfStmt : public Statement {
public:
    std::shared_ptr<Expression> condition;
    std::vector<std::shared_ptr<Statement>> thenBranch;
    std::vector<std::shared_ptr<Statement>> elseBranch;

    int kind() const override { return 6; }
};

// While statement node
class WhileStmt : public Statement {
public:
    std::shared_ptr<Expression> condition;
    std::vector<std::shared_ptr<Statement>> body;

    int kind() const override { return 7; }
};

// Assignment and function call node
class AssignStmt : public Statement {
public:
    std::string identifier;
    std::shared_ptr<Expression> indexExpr;  // For array indexing, null if not applicable
    std::shared_ptr<Expression> assignExpr; 
    int kind() const override { return 8; }
};

class CallStmt : public Statement {
public:
    std::string identifier;
    std::vector<std::shared_ptr<Expression>> callArgs; 
    std::vector<bool> isRef;  // Indica si el argumento es por referencia
    bool isVoid;                          // Indica si la función tiene un valor de retorno (void o no)

    int kind() const override { return 11; }
};

// Binary expression node
class BinaryExpr : public Expression {
public:
    int oper; // Operator type, such as +, -, *, /, etc.
    std::shared_ptr<Expression> left;
    std::shared_ptr<Expression> right;

    int kind() const override { return 9; }
};

// Literal numbers and identifiers
class LiteralExpr : public Expression {
public:
    enum Type { NUMBER, IDENTIFIER, STRING } type;
    std::string value; // This can be a number or identifier

    int kind() const override { return 10; }
};

class ArrayAccessExpr : public Expression {
public:
    std::shared_ptr<LiteralExpr> arrayName;  // El nombre del arreglo (literal)
    std::shared_ptr<Expression> index;       // La expresión del índice

    int kind() const override { return 12; }  // Número único para este tipo de nodo
};

void printAST(const std::shared_ptr<AstNode>& node, int indent = 0);

#endif // AST_HPP