#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include <map>

// AST Node Structure
struct ASTNode
{
    TokenType type;
    std::string value;
    ASTNode *left;
    ASTNode *right;
    ASTNode *extra; // For third child (e.g., else block)

    ASTNode(TokenType type, const std::string &value,
            ASTNode *left = nullptr, ASTNode *right = nullptr, ASTNode *extra = nullptr)
        : type(type), value(value), left(left), right(right), extra(extra) {}
};

class Parser
{
private:
    std::vector<Token> tokens;
    size_t pos;

    Token getCurrentToken();
    Token getNextToken();
    void eat(TokenType type);

    // Expression parsing
    ASTNode *factor();
    ASTNode *term();
    ASTNode *expression();

    // Statements
    ASTNode *statement();
    ASTNode *assignmentStatement();
    ASTNode *ifStatement();
    ASTNode *block();

public:
    Parser(const std::vector<Token> &tokens);
    ASTNode *parse();
    void printAST(ASTNode *node, int depth = 0);

    int evaluate(ASTNode *node); // for testing/interpretation
    std::map<std::string, int> variables;
};

#endif // PARSER_H
