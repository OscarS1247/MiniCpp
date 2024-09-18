#include "Ast.hpp"
#include <iostream>
#include <string>

// Función recursiva para imprimir el AST con indentación
void printAST(const std::shared_ptr<AstNode> &node, int indent)
{
    if (!node)
        return;

    // Imprimimos la indentación actual
    for (int i = 0; i < indent; ++i)
        std::cout << "  ";

    // Usamos node->kind() para determinar el tipo de nodo y luego imprimir su información
    switch (node->kind())
    {
    case 1:
    { // Program
        auto program = std::static_pointer_cast<Program>(node);
        std::cout << "Program\n";
        for (const auto &func : program->functions)
        {
            printAST(func, indent + 1);
        }
        break;
    }
    case 2:
    { // FunctionDecl
        auto func = std::static_pointer_cast<FunctionDecl>(node);
        std::cout << "Function: " << func->name << "(";
        // Imprimir los parámetros de la función
        for (size_t i = 0; i < func->parameters.size(); ++i)
        {
            const auto &param = func->parameters[i];
            std::cout << param.first; // El nombre del parámetro
            if (param.second)
            {
                std::cout << "&"; // Si es un parámetro por referencia
            }
            if (func->isArrayParam[i])
            {
                std::cout << "[]"; // Si es un arreglo
            }
            if (i < func->parameters.size() - 1)
            {
                std::cout << ", "; // Separar los parámetros con comas
            }
        }
        std::cout << ")\n";
        for (const auto &varDecl : func->varDecls)
        {
            printAST(varDecl, indent + 1); // Asegúrate de llamar a printAST para las declaraciones
        }
        for (const auto &stmt : func->statements)
        {
            printAST(stmt, indent + 1);
        }
        break;
    }
    case 3:
    { // VarDecl
        auto varDecl = std::static_pointer_cast<VarDecl>(node);
        std::cout << "VarDecl\n";
        for (const auto &var : varDecl->varNames)
        {
            for (int i = 0; i < indent + 1; ++i)
                std::cout << "  ";
            std::cout << "Variable: " << var.first;
            std::cout << "\n";
        }
        break;
    }
    case 4:
    { // Statement (base class, puedes agregar más nodos derivados aquí)
        std::cout << "Statement\n";
        break;
    }
    case 6:
    { // IfStmt
        auto ifStmt = std::static_pointer_cast<IfStmt>(node);
        std::cout << "IfStmt\n";
        for (int i = 0; i < indent + 1; ++i)
            std::cout << "  ";
        std::cout << "Condition:\n";
        printAST(ifStmt->condition, indent + 2);

        for (int i = 0; i < indent + 1; ++i)
            std::cout << "  ";
        std::cout << "ThenBranch:\n";
        for (const auto &stmt : ifStmt->thenBranch)
        {
            printAST(stmt, indent + 2);
        }

        if (!ifStmt->elseBranch.empty())
        {
            for (int i = 0; i < indent + 1; ++i)
                std::cout << "  ";
            std::cout << "ElseBranch:\n";
            for (const auto &stmt : ifStmt->elseBranch)
            {
                printAST(stmt, indent + 2);
            }
        }
        break;
    }
    case 7:
    { // WhileStmt
        auto whileStmt = std::static_pointer_cast<WhileStmt>(node);
        std::cout << "WhileStmt\n";
        for (int i = 0; i < indent + 1; ++i)
            std::cout << "  ";
        std::cout << "Condition:\n";
        printAST(whileStmt->condition, indent + 2);

        for (int i = 0; i < indent + 1; ++i)
            std::cout << "  ";
        std::cout << "Body:\n";
        for (const auto &stmt : whileStmt->body)
        {
            printAST(stmt, indent + 2);
        }
        break;
    }
    case 8:
    { // AssignStmt
        auto assignStmt = std::static_pointer_cast<AssignStmt>(node);
        std::cout << "AssignStmt: " << assignStmt->identifier << "\n";
        if (assignStmt->indexExpr)
        {
            for (int i = 0; i < indent + 1; ++i)
                std::cout << "  ";
            std::cout << "IndexExpr:\n";
            printAST(assignStmt->indexExpr, indent + 2);
        }
        for (int i = 0; i < indent + 1; ++i)
            std::cout << "  ";
        std::cout << "AssignExpr:\n";
        printAST(assignStmt->assignExpr, indent + 2);
        break;
    }
    case 11:
    { // CallStmt
        auto call = std::static_pointer_cast<CallStmt>(node);
        std::cout << "CallStmt: " << call->identifier << "\n";
        for (const auto &arg : call->callArgs)
        {
            printAST(arg, indent + 1);
        }
        break;
    }
    case 9:
    { // BinaryExpr
        auto binExpr = std::static_pointer_cast<BinaryExpr>(node);
        std::cout << "BinaryExpr: Operator " << binExpr->oper << "\n";
        for (int i = 0; i < indent + 1; ++i)
            std::cout << "  ";
        std::cout << "Left:\n";
        printAST(binExpr->left, indent + 2);
        for (int i = 0; i < indent + 1; ++i)
            std::cout << "  ";
        std::cout << "Right:\n";
        printAST(binExpr->right, indent + 2);
        break;
    }
    case 10:
    { // LiteralExpr
        auto literal = std::static_pointer_cast<LiteralExpr>(node);
        std::cout << "LiteralExpr: ";
        if (literal->type == LiteralExpr::STRING)
        {
            std::cout << "\"" << literal->value << "\""; // Imprime el valor de la cadena
        }
        else if (literal->type == LiteralExpr::NUMBER)
        {
            std::cout << literal->value;
        }
        else if (literal->type == LiteralExpr::IDENTIFIER)
        {
            std::cout << literal->value;
        }
        std::cout << "\n";
        break;
    }
    case 12:
    { // ArrayAccessExpr
        auto arrayAccess = std::static_pointer_cast<ArrayAccessExpr>(node);
        std::cout << "ArrayAccessExpr: " << arrayAccess->arrayName->value << "\n";
        for (int i = 0; i < indent + 1; ++i)
            std::cout << "  ";
        std::cout << "Index:\n";
        printAST(arrayAccess->index, indent + 2);
        break;
    }
    default:
        std::cout << "Unknown Node Type\n";
    }
}
