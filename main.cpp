#include <iostream>
#include <fstream>
#include "Lexer.hpp"
#include "Parser.hpp"
#include "Ast.hpp"
#include "Generacion.hpp" // Asegúrate de que este archivo esté correctamente incluido

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Not enough arguments\n";
        return 1;
    }

    std::ifstream in(argv[1]);
    if (!in.is_open()) {
        std::cerr << "Cannot open file\n";
        return 1;
    }

    Lexer lex(in);
    Parser parser(lex);
    auto programNode = parser.prg();

    if (programNode) {
        std::cout << "\nParsing successful!" << "\n";

        // Suponiendo que printAST es una función utilitaria para imprimir el AST
        printAST(programNode);

        // Utilizando la clase CodeGenerator para generar el ensamblador
        CodeGenerator generator;
        std::string assemblyCode = generator.generateAssembly(programNode.get());

        // Guardamos el código ensamblador en un archivo
        std::ofstream outFile("program.asm");
        if (outFile.is_open()) {
            outFile << assemblyCode;
            outFile.close();
            std::cout << "\nAssembly file 'program.asm' generated successfully!\n";
        } else {
            std::cerr << "Failed to open output file.\n";
        }
    } else {
        std::cerr << "\nParsing failed!\n";
    }

    return 0;
}


