#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <unordered_map>
#include "lexer.h"

// Forward declare Parser class here if necessary
class Parser;

// AST Node definition
struct ASTNode
{
    TokenType type;
    std::string value;
    ASTNode *left, *right;

    ASTNode(TokenType type, std::string value)
        : type(type), value(value), left(nullptr), right(nullptr) {}

    ASTNode(TokenType type, std::string value, ASTNode *left, ASTNode *right)
        : type(type), value(value), left(left), right(right) {}
};

// Parser class declaration
class Parser
{
public:
    Parser(const std::vector<Token> &tokens);
    ASTNode *parse();
    ASTNode *expression();
    ASTNode *term();
    ASTNode *factor();
    ASTNode *assignment();
    void eat(TokenType type);
    Token getCurrentToken();
    void printAST(ASTNode *node, int depth);
    int evaluate(ASTNode *node); // ← move this here

private:
    std::vector<Token> tokens;
    size_t pos;
    std::unordered_map<std::string, int> variables;
};

#endif // PARSER_H
