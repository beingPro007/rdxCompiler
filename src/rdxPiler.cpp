#include "lexer.h"
#include "parser.h"
#include "interpreter.h"
#include <iostream>
#include <string>
#include "colors.h"

void printHeader()
{
    std::cout << BOLD << CYAN;
    std::cout << R"(
 _____ ______   ___  ________   ___          ________  ________  _____ ______   ________  ___  ___       _______   ________     
|\   _ \  _   \|\  \|\   ___  \|\  \        |\   ____\|\   __  \|\   _ \  _   \|\   __  \|\  \|\  \     |\  ___ \ |\   __  \    
\ \  \\\__\ \  \ \  \ \  \\ \  \ \  \       \ \  \___|\ \  \|\  \ \  \\\__\ \  \ \  \|\  \ \  \ \  \    \ \   __/|\ \  \|\  \   
 \ \  \\|__| \  \ \  \ \  \\ \  \ \  \       \ \  \    \ \  \\\  \ \  \\|__| \  \ \   ____\ \  \ \  \    \ \  \_|/_\ \   _  _\  
  \ \  \    \ \  \ \  \ \  \\ \  \ \  \       \ \  \____\ \  \\\  \ \  \    \ \  \ \  \___|\ \  \ \  \____\ \  \_|\ \ \  \\  \| 
   \ \__\    \ \__\ \__\ \__\\ \__\ \__\       \ \_______\ \_______\ \__\    \ \__\ \__\    \ \__\ \_______\ \_______\ \__\\ _\ 
    \|__|     \|__|\|__|\|__| \|__|\|__|        \|_______|\|_______|\|__|     \|__|\|__|     \|__|\|_______|\|_______|\|__|\|__|
    )" << RESET;
    std::cout << BOLD << WHITE << "\n               Mini Compiler\n\n"
              << RESET;
    std::cout << "------------------------------------------\n";
    std::cout << "|         Welcome to Mini Compiler       |\n";
    std::cout << "|               v1.0                     |\n";
    std::cout << "------------------------------------------\n";
}

int main()
{
    printHeader();

    std::string input;
    std::cout << CYAN << "Enter expression: " << RESET;
    std::getline(std::cin, input);

    Lexer lexer(input);
    std::vector<Token> tokens = lexer.tokenize();

    Parser parser(tokens);
    ASTNode *ast = parser.parse();

    std::cout << BOLD << MAGENTA
              << "\n+----------------------------------------+\n"
              << "|   Abstract Syntax Tree (AST)          |\n"
              << "+----------------------------------------+\n"
              << RESET;
    parser.printAST(ast, 0);

    int result = parser.evaluate(ast);

    std::cout << BOLD << YELLOW
              << "\n+--- Evaluation Result: "
              << GREEN << result
              << RESET << " ---+\n";

    std::cout << BOLD << BLUE << "\n--> Done!" << RESET << "\n";

    return 0;
}
