#ifndef AST_H
#define AST_H

#include "lexer.h"

// AST Node
struct ASTNode
{
    TokenType type;
    std::string value;
    ASTNode *left;
    ASTNode *right;

    ASTNode(TokenType type, std::string value) : type(type), value(value), left(nullptr), right(nullptr) {}
};

#endif
