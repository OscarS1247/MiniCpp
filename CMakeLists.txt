cmake_minimum_required(VERSION 3.14)
project(MiniC++)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#find_package(re2c REQUIRED) 

add_custom_command(
    OUTPUT LexerImpl.cpp
    COMMAND re2c -o LexerImpl.cpp ${PROJECT_SOURCE_DIR}/Lexer.re 
    MAIN_DEPENDENCY ${PROJECT_SOURCE_DIR}/Lexer.re
)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})

add_executable(${PROJECT_NAME} Lexer.hpp LexerImpl.cpp main.cpp Parser.hpp Parser.cpp Ast.hpp Ast.cpp Generacion.cpp Generacion.hpp) 