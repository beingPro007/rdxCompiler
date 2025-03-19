#include "parser.h"
#include <iostream>
#include <stdexcept>

Parser::Parser(const std::vector<Token> &tokens) : tokens(tokens), pos(0) {} // Fix: Correct constructor

Token Parser::getCurrentToken()
{
    if (pos < tokens.size())
        return tokens[pos];
    return {TokenType::END, ""}; 
}

void Parser::eat(TokenType type)
{
    if (getCurrentToken().type == type)
        pos++;
    else
        throw std::runtime_error("Syntax Error: Unexpected token");
}

ASTNode *Parser::factor()
{
    Token token = getCurrentToken();

    if (token.type == TokenType::NUMBER)
    {
        eat(TokenType::NUMBER);
        return new ASTNode(token.type, token.value);
    }
    else if (token.type == TokenType::LPAREN)
    {
        eat(TokenType::LPAREN);
        ASTNode *node = expression();
        eat(TokenType::RPAREN);
        return node;
    }

    throw std::runtime_error("Unexpected token in factor()");
}

ASTNode *Parser::term()
{
    ASTNode *node = factor();

    while (getCurrentToken().type == TokenType::MULTIPLY ||
           getCurrentToken().type == TokenType::DIVIDE)
    {
        Token token = getCurrentToken();
        eat(token.type);
        node = new ASTNode(token.type, token.value, node, factor()); // Fix: Use correct constructor
    }

    return node;
}

ASTNode *Parser::expression()
{
    ASTNode *node = term();

    while (getCurrentToken().type == TokenType::PLUS ||
           getCurrentToken().type == TokenType::MINUS)
    {
        Token token = getCurrentToken();
        eat(token.type);
        node = new ASTNode(token.type, token.value, node, term()); // Fix: Use correct constructor
    }

    return node;
}

ASTNode *Parser::parse()
{
    ASTNode *ast = expression();
    printAST(ast, 0);
    return ast;
}

void Parser::printAST(ASTNode *node, int depth)
{
    if (!node)
        return;

    for (int i = 0; i < depth; i++)
        std::cout << "  ";
    std::cout << node->value << "\n";

    if (node->left)
        printAST(node->left, depth + 1);
    if (node->right)
        printAST(node->right, depth + 1);
}
