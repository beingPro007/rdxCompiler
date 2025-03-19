#include "lexer.h"
#include "parser.h"
#include "interpreter.h"
#include <iostream>

int main()
{
    std::string input;
    std::cout << "Enter expression: ";
    std::getline(std::cin, input);

    Lexer lexer(input);
    std::vector<Token> tokens = lexer.tokenize();

    Parser parser(tokens);
    ASTNode *ast = parser.parse();

    std::cout << "\nAbstract Syntax Tree (AST):\n";
    parser.printAST(ast, 0);

    Interpreter interpreter;
    int result = interpreter.evaluate(ast);

    std::cout << "\nEvaluation Result: " << result << std::endl;

    return 0;
}
