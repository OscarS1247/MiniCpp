#ifndef GENERACION_HPP
#define GENERACION_HPP

#include <string>
#include <vector>
#include "Ast.hpp"
#include "Parser.hpp"

struct ECode {
    std::string place;
    std::string code;
};

class CodeGenerator {
public:
    CodeGenerator();
    ~CodeGenerator() = default;

    std::string generateAssembly(const Program* program);

private:
    int labelCount;
    std::string currentFunctionName;
    std::vector<std::string> tempRegisters;
    std::vector<bool> tempAvailability;
    std::string dataSection;

    std::string newTemp();
    void releaseTemp(const std::string& temp);
    std::string newLabel();
    std::string collectDataDeclarations(const AstNode* node, const std::string& functionName);
    ECode genCode(const AstNode* node);
    std::string genCodeForString(const std::string& str);
};

#endif // GENERACION_HPP
