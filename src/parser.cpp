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

// Factor handles numbers, variables, and expressions inside parentheses
ASTNode *Parser::factor()
{
    Token token = getCurrentToken();

    // If the token is a number, return a new ASTNode for that number
    if (token.type == TokenType::NUMBER)
    {
        eat(TokenType::NUMBER);
        return new ASTNode(token.type, token.value);
    }
    // If it's an identifier (variable), look it up in the map
    else if (token.type == TokenType::IDENTIFIER)
    {
        std::string varName = token.value;
        eat(TokenType::IDENTIFIER);

        // Look up the variable's value in the map
        if (variables.find(varName) != variables.end())
        {
            return new ASTNode(TokenType::NUMBER, std::to_string(variables[varName]));
        }
        else
        {
            throw std::runtime_error("Error: Undefined variable " + varName);
        }
    }
    // If it's a left parenthesis, parse an expression inside parentheses
    else if (token.type == TokenType::LPAREN)
    {
        eat(TokenType::LPAREN);
        ASTNode *node = expression();
        eat(TokenType::RPAREN);
        return node;
    }

    throw std::runtime_error("Unexpected token in factor()");
}

// Assignment handles assignment expressions like x = 5 + 3
ASTNode *Parser::assignment()
{
    if (getCurrentToken().type == TokenType::IDENTIFIER)
    {
        std::string varName = getCurrentToken().value;
        eat(TokenType::IDENTIFIER); // Eat the identifier

        eat(TokenType::ASSIGN); // Eat the '=' token

        ASTNode *expr = expression(); // Parse the right-hand side expression

        // Store the result of the assignment
        int value = evaluate(expr); // Evaluate the right-hand side
        variables[varName] = value; // Store in the variables map

        // Return the assignment AST node
        return new ASTNode(TokenType::ASSIGN, varName, expr, nullptr);
    }

    return nullptr; // If it's not an assignment, return nullptr
}

// Evaluates an ASTNode and returns the result
int Parser::evaluate(ASTNode *node)
{
    if (node->type == TokenType::NUMBER)
    {
        return std::stoi(node->value); // Convert number string to integer
    }
    else if (node->type == TokenType::PLUS)
    {
        return evaluate(node->left) + evaluate(node->right);
    }
    else if (node->type == TokenType::MINUS)
    {
        return evaluate(node->left) - evaluate(node->right);
    }
    else if (node->type == TokenType::MULTIPLY)
    {
        return evaluate(node->left) * evaluate(node->right);
    }
    else if (node->type == TokenType::DIVIDE)
    {
        return evaluate(node->left) / evaluate(node->right);
    }
    else if (node->type == TokenType::ASSIGN)
    {
        // Evaluate the right-hand side of the assignment and store it
        int value = evaluate(node->left); // Right-hand side expression
        variables[node->value] = value;   // Store the value in the variables map
        return value;                     // Return the assigned value
    }

    throw std::runtime_error("Unknown node type during evaluation");
}

// Term handles multiplication and division
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

// Expression handles addition and subtraction as well as assignments
ASTNode *Parser::expression()
{
    ASTNode *node = assignment(); // Try parsing assignment first

    if (node == nullptr)
    {
        node = term(); // If it's not an assignment, fall back to normal expression parsing
    }

    while (getCurrentToken().type == TokenType::PLUS || getCurrentToken().type == TokenType::MINUS)
    {
        Token token = getCurrentToken();
        eat(token.type);
        node = new ASTNode(token.type, token.value, node, term());
    }

    return node;
}

// Parse the entire expression and print the AST
ASTNode *Parser::parse()
{
    ASTNode *ast = expression();
    printAST(ast, 0);
    return ast;
}

// Prints the Abstract Syntax Tree (AST)
void Parser::printAST(ASTNode *node, int depth)
{
    if (node == nullptr)
        return;

    // Print the current node with indentation based on depth
    for (int i = 0; i < depth; ++i)
        std::cout << "   "; // Indentation

    std::cout << "+-- " << node->value << "\n"; // Show the node's value (e.g., operand or operator)

    // Recursively print the left child
    printAST(node->left, depth + 1);

    // Recursively print the right child
    printAST(node->right, depth + 1);
}
