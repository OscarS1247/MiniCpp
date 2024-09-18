#include "Generacion.hpp"
#include "Ast.hpp"
#include "Parser.hpp"
#include <sstream>
#include <stdexcept>
#include <iostream>
#include <fstream>

CodeGenerator::CodeGenerator() : labelCount(0), tempRegisters{"$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$t8", "$t9"}, tempAvailability(tempRegisters.size(), true) {}

std::string CodeGenerator::newTemp()
{
    for (size_t i = 0; i < tempRegisters.size(); ++i)
    {
        if (tempAvailability[i])
        {
            tempAvailability[i] = false;
            return tempRegisters[i];
        }
    }
    throw std::runtime_error("No available temporary registers");
}

void CodeGenerator::releaseTemp(const std::string &temp)
{
    for (size_t i = 0; i < tempRegisters.size(); ++i)
    {
        if (tempRegisters[i] == temp)
        {
            tempAvailability[i] = true;
            return;
        }
    }
    throw std::runtime_error("Attempting to release an invalid temporary register: " + temp);
}

std::string CodeGenerator::newLabel()
{
    std::ostringstream label;
    label << "L" << labelCount++;
    return label.str();
}

std::string CodeGenerator::collectDataDeclarations(const AstNode *node, const std::string &functionName)
{
    std::ostringstream data;
    if (node->kind() == 2)
    { // FunctionDecl
        const auto &func = dynamic_cast<const FunctionDecl *>(node);
        for (const auto &decl : func->varDecls)
        {
            const auto &varDecl = dynamic_cast<const VarDecl *>(decl.get());
            for (const auto &var : varDecl->varNames)
            {
                // Agregar el prefijo del nombre de la función a cada variable para evitar duplicados
                data << functionName << "_" << var.first << ": .word 0\n"; // Initialize all variables to 0
            }
        }
    }
    return data.str();
}

std::string CodeGenerator::genCodeForString(const std::string &str)
{
    static int stringCounter = 0;
    std::string label = "str_" + std::to_string(stringCounter++);
    std::ostringstream bytes;

    // Agrega cada carácter de la cadena como un byte
    for (char c : str)
    {
        bytes << int(c) << ", ";
    }
    bytes << "0"; // Agregar el terminador nulo para la cadena

    // Agrega la definición de la cadena a la sección de datos usando .byte
    dataSection += label + ": .byte " + bytes.str() + "\n";
    return label;
}

ECode CodeGenerator::genCode(const AstNode *node)
{
    ECode result;

    switch (node->kind())
    {
    case 1: // Program
    {
        const auto &program = dynamic_cast<const Program *>(node);
        for (const auto &func : program->functions)
        {
            result.code += genCode(func.get()).code; // Generamos el código de cada función
        }
        break;
    }
    case 2: // FunctionDecl
    {
        auto func = dynamic_cast<const FunctionDecl *>(node);

        currentFunctionName = func->name; // Actualizamos el nombre de la función actual

        // Código para el cuerpo de la función
        for (const auto &stmt : func->statements)
        {
            ECode stmtCode = genCode(stmt.get());
            result.code += stmtCode.code; // Generar el código de las sentencias
        }

        result.code += "jr $ra\n"; // Regresar a la instrucción que llamó la función

        break;
    }

    case 6: // IfStmt
    {
        auto ifStmt = dynamic_cast<const IfStmt *>(node);

        // Generar etiquetas únicas para el bloque 'else' y el final del 'if'
        std::string elseLabel = newLabel();
        std::string endLabel = newLabel();

        // Generar código para la condición
        ECode condCode = genCode(ifStmt->condition.get());
        result.code += condCode.code; // Añadimos el código para evaluar la condición

        // Suponiendo que la condición es de tipo comparación, como a < b
        result.code += "beq " + condCode.place + ", $zero, " + elseLabel + "\n"; // Si la condición es falsa, salta al bloque 'else'

        // Código para el bloque 'then'
        for (const auto &stmt : ifStmt->thenBranch)
        {
            ECode thenCode = genCode(stmt.get());
            result.code += thenCode.code; // Añadimos el código del bloque 'then'
        }
        result.code += "j " + endLabel + "\n"; // Salta al final del 'if'

        // Etiqueta del bloque 'else'
        result.code += elseLabel + ":\n";
        if (!ifStmt->elseBranch.empty()) // Si existe el bloque 'else'
        {
            for (const auto &stmt : ifStmt->elseBranch)
            {
                ECode elseCode = genCode(stmt.get());
                result.code += elseCode.code; // Añadimos el código del bloque 'else'
            }
        }

        // Etiqueta del final del 'if'
        result.code += endLabel + ":\n";

        break;
    }
    case 7: // WhileStmt
    {
        auto whileStmt = dynamic_cast<const WhileStmt *>(node);

        // Generar etiquetas únicas para el inicio y el final del ciclo
        std::string loopStartLabel = newLabel();
        std::string loopEndLabel = newLabel();

        // Etiqueta del inicio del ciclo
        result.code += loopStartLabel + ":\n";

        // Generar código para evaluar la condición
        ECode condCode = genCode(whileStmt->condition.get());
        result.code += condCode.code; // Añadir el código de la condición

        // Si la condición es falsa, saltar al final del ciclo
        result.code += "beq " + condCode.place + ", $zero, " + loopEndLabel + "\n";

        // Generar código para el cuerpo del ciclo
        for (const auto &stmt : whileStmt->body)
        {
            ECode bodyCode = genCode(stmt.get());
            result.code += bodyCode.code; // Añadir el código del cuerpo del ciclo
        }

        // Saltar al inicio del ciclo para reevaluar la condición
        result.code += "j " + loopStartLabel + "\n";

        // Etiqueta del final del ciclo
        result.code += loopEndLabel + ":\n";

        // Liberar el registro temporal de la condición
        releaseTemp(condCode.place);

        break;
    }

    case 8: // AssignStmt
    {
        auto assignStmt = dynamic_cast<const AssignStmt *>(node);
        ECode exprCode = genCode(assignStmt->assignExpr.get());

        std::string tempAddress = newTemp(); // Generamos un registro temporal para la dirección de la variable

        std::string prefixedVarName = currentFunctionName + "_" + assignStmt->identifier;

        result.code += exprCode.code;                                         // Generamos el código de la expresión
        result.code += "la " + tempAddress + ", " + prefixedVarName + "\n";   // Cargar la dirección de la variable en el temporal
        result.code += "sw " + exprCode.place + ", 0(" + tempAddress + ")\n"; // Almacenar el valor en la dirección

        releaseTemp(exprCode.place); // Liberamos el temporal usado para el valor
        releaseTemp(tempAddress);    // Liberamos el temporal usado para la dirección
        break;
    }

    case 10: // LiteralExpr
    {
        const auto &literal = dynamic_cast<const LiteralExpr *>(node);
        result.place = newTemp(); // Asignamos un registro temporal

        if (literal->type == LiteralExpr::NUMBER)
        {
            // Concatenamos en lugar de sobrescribir
            result.code += "li " + result.place + ", " + literal->value + "\n"; // Cargamos el valor inmediato
        }
        else if (literal->type == LiteralExpr::IDENTIFIER)
        {
            // Usar el nombre de la función como prefijo para el identificador
            std::string prefixedVarName = currentFunctionName + "_" + literal->value;

            // Asegúrate de que prefixedVarName sea una etiqueta válida
            std::string addrTemp = newTemp();                                // Asignamos un temporal para la dirección
            result.code += "la " + addrTemp + ", " + prefixedVarName + "\n"; // Cargamos la dirección de la variable (etiqueta)
            result.code += "lw " + result.place + ", 0(" + addrTemp + ")\n"; // Cargamos el valor de la variable en el registro
            releaseTemp(addrTemp);                                           // Liberamos el registro temporal
        }
        else if (literal->type == LiteralExpr::STRING)
        {
            // Obtener la etiqueta de la cadena literal
            std::string stringLabel = genCodeForString(literal->value);      // Obtenemos la etiqueta para la cadena
            result.code += "la " + result.place + ", " + stringLabel + "\n"; // Cargamos la dirección de la cadena (etiqueta)
            releaseTemp(result.place);                                       // Liberamos el registro temporal
        }
        break;
    }

    case 9:
    { // BinaryExpr
        auto binExpr = dynamic_cast<const BinaryExpr *>(node);
        ECode leftCode = genCode(binExpr->left.get());
        ECode rightCode = genCode(binExpr->right.get());

        std::string temp = newTemp(); // Asignamos un registro temporal

        // Operadores Aritmeticos
        if (binExpr->oper == Token::OP_ADD)
        {
            result.code += leftCode.code + rightCode.code;
            result.code += "add " + temp + ", " + leftCode.place + ", " + rightCode.place + "\n";
        }
        else if (binExpr->oper == Token::OP_SUB)
        {
            result.code += leftCode.code + rightCode.code;
            result.code += "sub " + temp + ", " + leftCode.place + ", " + rightCode.place + "\n";
        }
        else if (binExpr->oper == Token::OP_MULT)
        {
            result.code += leftCode.code + rightCode.code;
            result.code += "mul " + temp + ", " + leftCode.place + ", " + rightCode.place + "\n"; // Multiplicación
        }
        else if (binExpr->oper == Token::OP_DIV)
        {
            result.code += leftCode.code + rightCode.code;
            result.code += "div " + leftCode.place + ", " + rightCode.place + "\n"; // División
            result.code += "mflo " + temp + "\n";                                   // Obtener el cociente de la división
        }

        // Operadores de comparación
        else if (binExpr->oper == Token::LT)
        {
            result.code += leftCode.code + rightCode.code;
            result.code += "slt " + temp + ", " + leftCode.place + ", " + rightCode.place + "\n"; // Menor que
        }
        else if (binExpr->oper == Token::GT)
        {
            result.code += leftCode.code + rightCode.code;
            result.code += "slt " + temp + ", " + rightCode.place + ", " + leftCode.place + "\n"; // Mayor que (right < left)
        }
        else if (binExpr->oper == Token::LTE)
        {
            result.code += leftCode.code + rightCode.code;
            result.code += "slt " + temp + ", " + rightCode.place + ", " + leftCode.place + "\n"; // right < left
            result.code += "xori " + temp + ", " + temp + ", 1\n";                                // Invertir el resultado (equivalente a left <= right)
        }
        else if (binExpr->oper == Token::GTE)
        {
            result.code += leftCode.code + rightCode.code;
            result.code += "slt " + temp + ", " + leftCode.place + ", " + rightCode.place + "\n"; // left < right
            result.code += "xori " + temp + ", " + temp + ", 1\n";                                // Invertir el resultado (equivalente a left >= right)
        }
        else if (binExpr->oper == Token::EQ)
        {
            result.code += leftCode.code + rightCode.code;
            std::string trueLabel = newLabel();
            std::string endLabel = newLabel();

            // Si los registros son iguales, saltamos a trueLabel
            result.code += "beq " + leftCode.place + ", " + rightCode.place + ", " + trueLabel + "\n";

            // Si no son iguales, asignamos 0 al resultado
            result.code += "li " + temp + ", 0\n";
            result.code += "j " + endLabel + "\n";

            // trueLabel: Si son iguales, asignamos 1 al resultado
            result.code += trueLabel + ":\n";
            result.code += "li " + temp + ", 1\n";

            // endLabel: Continuar la ejecución
            result.code += endLabel + ":\n";

            result.place = temp;
        }
        else if (binExpr->oper == Token::NE)
        {
            result.code += leftCode.code + rightCode.code;
            std::string trueLabel = newLabel();
            std::string endLabel = newLabel();

            // Si los registros son diferentes, saltamos a trueLabel
            result.code += "bne " + leftCode.place + ", " + rightCode.place + ", " + trueLabel + "\n";

            // Si son iguales, asignamos 0 al resultado
            result.code += "li " + temp + ", 0\n";
            result.code += "j " + endLabel + "\n";

            // trueLabel: Si son diferentes, asignamos 1 al resultado
            result.code += trueLabel + ":\n";
            result.code += "li " + temp + ", 1\n";

            // endLabel: Continuar la ejecución
            result.code += endLabel + ":\n";

            result.place = temp;
        }

        // Operadores lógicos
        else if (binExpr->oper == Token::BOOL_AND)
        {
            result.code += leftCode.code + rightCode.code;
            result.code += "and " + temp + ", " + leftCode.place + ", " + rightCode.place + "\n"; // AND lógico
        }
        else if (binExpr->oper == Token::BOOL_OR)
        {
            result.code += leftCode.code + rightCode.code;
            result.code += "or " + temp + ", " + leftCode.place + ", " + rightCode.place + "\n"; // OR lógico
        }

        result.place = temp; // El resultado se guarda en este temporal
        releaseTemp(leftCode.place);
        releaseTemp(rightCode.place);
        releaseTemp(temp);
        break;
    }
    case 11: // CallStmt (cin / cout / llamada a función)
    {
        auto callStmt = dynamic_cast<const CallStmt *>(node);

        // Diferenciar entre cin, cout y llamadas a funciones
        if (callStmt->identifier == "cout")
        {
            // Código para std::cout
            for (const auto &arg : callStmt->callArgs)
            {
                ECode argCode = genCode(arg.get());

                // Comprobamos si es una cadena, número o identificador para generar el código correcto
                if (arg->kind() == 10) // LiteralExpr
                {
                    auto literalExpr = dynamic_cast<const LiteralExpr *>(arg.get());

                    if (literalExpr->value == "endl") // Detectamos `endl` para salto de línea
                    {
                        result.code += "li $v0, 11\nli $a0, 10\nsyscall\n"; // Imprimir salto de línea
                    }
                    else if (literalExpr->type == LiteralExpr::STRING)
                    {
                        // Usamos directamente la etiqueta generada para la cadena
                        std::string stringLabel = genCodeForString(literalExpr->value);     // Obtener la etiqueta de la cadena
                        result.code += "li $v0, 4\nla $a0, " + stringLabel + "\nsyscall\n"; // Usar la etiqueta directamente para imprimir la cadena
                    }
                    else if (literalExpr->type == LiteralExpr::NUMBER)
                    {
                        result.code += argCode.code;
                        result.code += "li $v0, 1\nmove $a0, " + argCode.place + "\nsyscall\n"; // Imprimir número
                        releaseTemp(argCode.place);                                             // Liberamos el temporal usado para el número
                    }
                    else if (literalExpr->type == LiteralExpr::IDENTIFIER)
                    {
                        // Usar el nombre de la función como prefijo para el identificador (variable)
                        std::string prefixedVarName = currentFunctionName + "_" + literalExpr->value;

                        std::string addrTemp = newTemp();                                       // Asignamos un temporal para la dirección
                        result.code += "la " + addrTemp + ", " + prefixedVarName + "\n";        // Cargamos la dirección de la variable
                        result.code += "lw " + argCode.place + ", 0(" + addrTemp + ")\n";       // Cargamos el valor de la variable
                        result.code += "li $v0, 1\nmove $a0, " + argCode.place + "\nsyscall\n"; // Imprimir la variable
                        releaseTemp(argCode.place);                                             // Liberamos el temporal
                        releaseTemp(addrTemp);                                                  // Liberamos el temporal usado para la dirección
                    }
                }
            }
        }
        else if (callStmt->identifier == "cin")
        {
            // Código para std::cin
            for (const auto &arg : callStmt->callArgs)
            {
                ECode argCode = genCode(arg.get());

                // Solo manejamos identificadores para cin (no es posible leer directamente a un número o cadena)
                if (arg->kind() == 10) // LiteralExpr
                {
                    auto literalExpr = dynamic_cast<const LiteralExpr *>(arg.get());

                    if (literalExpr->type == LiteralExpr::IDENTIFIER)
                    {
                        // Usar el nombre de la función como prefijo para el identificador (variable)
                        std::string prefixedVarName = currentFunctionName + "_" + literalExpr->value;

                        std::string addrTemp = newTemp(); // Asignamos un temporal para la dirección

                        // Generar código para leer un entero desde std::cin
                        result.code += "li $v0, 5\n";                                    // Preparamos la syscall para leer un entero
                        result.code += "syscall\n";                                      // Ejecutamos la syscall para leer el valor en $v0
                        result.code += "la " + addrTemp + ", " + prefixedVarName + "\n"; // Cargamos la dirección de la variable
                        result.code += "sw $v0, 0(" + addrTemp + ")\n";                  // Guardamos el valor leído en la variable

                        releaseTemp(addrTemp); // Liberamos el temporal usado para la dirección
                    }
                    else
                    {
                        throw std::runtime_error("cin can only assign to variables (identifiers)");
                    }
                }
            }
        }
        else
   {
    // Código para llamadas a funciones regulares, sin uso de la pila
    for (size_t i = 0; i < callStmt->callArgs.size() && i < 4; ++i)
    {
        ECode argCode = genCode(callStmt->callArgs[i].get());
        result.code += argCode.code;
        result.code += "move $a" + std::to_string(i) + ", " + argCode.place + "\n"; // Pasar el argumento al registro $a0, $a1, etc.
        releaseTemp(argCode.place); // Liberar el temporal usado por el argumento
    }

    // Llamar a la función
    result.code += "jal " + callStmt->identifier + "\n"; // Saltar a la función

    // Usar el valor de retorno (si es necesario)
    if (!callStmt->isVoid) // Si la función tiene valor de retorno
    {
        if (result.place.empty()) {
            result.place = newTemp(); // Asignar un temporal si no lo tiene
        }
        result.code += "move " + result.place + ", $v0\n"; // El valor de retorno está en $v0
        releaseTemp(result.place); // Liberar el temporal usado para el valor de retorno
    }
}

    break;
}
    default:
        throw std::runtime_error("Unknown node type in code generation");
    }

    return result;
}

std::string CodeGenerator::generateAssembly(const Program *program)
{
    std::string textSection;
    dataSection.clear(); // limpia la sección de datos anterior para evitar duplicados

    // Recorrer cada función y agregar sus declaraciones de variables al dataSection
    for (const auto &func : program->functions)
    {
        // Pasamos el nombre de la función como prefijo
        const auto &funcDecl = dynamic_cast<const FunctionDecl *>(func.get());
        dataSection += collectDataDeclarations(func.get(), funcDecl->name); // Usar el nombre de la función como prefijo
        textSection += genCode(func.get()).code;
    }

    std::string output = ".data\n" + dataSection + ".text\n" + textSection;
    return output;
}
