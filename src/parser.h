#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include "lexer.h"

struct ASTNode
{
    TokenType type;
    std::string value;
    ASTNode *left, *right;

    ASTNode(TokenType type, std::string value)
        : type(type), value(value), left(nullptr), right(nullptr) {}

    // Fix: Add binary operation constructor
    ASTNode(TokenType type, std::string value, ASTNode *left, ASTNode *right)
        : type(type), value(value), left(left), right(right) {}
};

class Parser
{
private:
    std::vector<Token> tokens;
    size_t pos; // Fix: Ensure 'pos' is a member variable

    Token getCurrentToken();
    void eat(TokenType type);
    ASTNode *factor();
    ASTNode *term();
    ASTNode *expression();

public:
    Parser(const std::vector<Token> &tokens); // Fix: Use const reference
    ASTNode *parse();
    void printAST(ASTNode *node, int depth);
};

#endif
