#include "parser.h"
#include <iostream>
#include <stdexcept>

Parser::Parser(const std::vector<Token> &tokens) : tokens(tokens), pos(0) {}

Token Parser::getCurrentToken()
{
    return (pos < tokens.size()) ? tokens[pos] : Token{TokenType::END, ""};
}

Token Parser::getNextToken()
{
    return (pos + 1 < tokens.size()) ? tokens[pos + 1] : Token{TokenType::END, ""};
}

void Parser::eat(TokenType type)
{
    if (getCurrentToken().type == type)
    {
        std::cout << "Eating token: " << getCurrentToken().value << "\n"; // Debugging line
        pos++;
    }
    else
    {
        std::cerr << "Unexpected token: " << getCurrentToken().value << " at position " << pos << "\n"; // Debugging line
        throw std::runtime_error("Syntax Error: Unexpected token");
    }
}

// ----- Expression Parsing -----

ASTNode *Parser::factor()
{
    Token token = getCurrentToken();

    if (token.type == TokenType::NUMBER)
    {
        eat(TokenType::NUMBER);
        return new ASTNode(token.type, token.value);
    }
    else if (token.type == TokenType::IDENTIFIER)
    {
        eat(TokenType::IDENTIFIER);
        return new ASTNode(TokenType::IDENTIFIER, token.value);
    }
    else if (token.type == TokenType::LPAREN)
    {
        eat(TokenType::LPAREN);
        ASTNode *node = expression();
        eat(TokenType::RPAREN);
        return node;
    }

    throw std::runtime_error("Syntax Error in factor()");
}

ASTNode *Parser::term()
{
    ASTNode *node = factor();

    while (getCurrentToken().type == TokenType::MULTIPLY ||
           getCurrentToken().type == TokenType::DIVIDE)
    {
        Token op = getCurrentToken();
        eat(op.type);
        node = new ASTNode(op.type, op.value, node, factor());
    }

    return node;
}

ASTNode *Parser::expression()
{
    ASTNode *node = term();

    while (getCurrentToken().type == TokenType::PLUS ||
           getCurrentToken().type == TokenType::MINUS ||
           getCurrentToken().type == TokenType::GE || // Greater than or equal
           getCurrentToken().type == TokenType::LE || // Less than or equal
           getCurrentToken().type == TokenType::GT || // Greater than
           getCurrentToken().type == TokenType::LT || // Less than
           getCurrentToken().type == TokenType::EQ || // Equal
           getCurrentToken().type == TokenType::NEQ)  // Not equal
    {
        Token op = getCurrentToken();
        eat(op.type);
        node = new ASTNode(op.type, op.value, node, term());
    }

    return node;
}

// ----- Statement Handling -----

ASTNode *Parser::assignmentStatement()
{
    std::string varName = getCurrentToken().value;
    eat(TokenType::IDENTIFIER);
    eat(TokenType::ASSIGN);
    ASTNode *expr = expression();
    eat(TokenType::SEMICOLON);
    return new ASTNode(TokenType::ASSIGN, varName, expr);
}

ASTNode *Parser::ifStatement()
{
    eat(TokenType::IF);
    eat(TokenType::LPAREN);
    ASTNode *condition = expression();
    eat(TokenType::RPAREN);

    std::cout << "Condition parsed: " << condition->value << "\n"; // Debugging line

    ASTNode *thenBranch = statement();

    ASTNode *elseBranch = nullptr;
    if (getCurrentToken().type == TokenType::ELSE)
    {
        eat(TokenType::ELSE);
        std::cout << "Parsing ELSE branch\n"; // Debugging line
        elseBranch = statement();
    }

    return new ASTNode(TokenType::IF, "if", condition, thenBranch, elseBranch);
}

ASTNode *Parser::statement()
{
    std::cout << "Current token in statement: " << getCurrentToken().value << "\n"; // Debugging line

    if (getCurrentToken().type == TokenType::IF)
    {
        return ifStatement();
    }
    else if (getCurrentToken().type == TokenType::IDENTIFIER &&
             getNextToken().type == TokenType::ASSIGN)
    {
        return assignmentStatement();
    }
    else
    {
        ASTNode *expr = expression();
        eat(TokenType::SEMICOLON);
        return expr;
    }
}

ASTNode *Parser::block()
{
    return statement(); // Simplified for now — one-statement block
}

// ----- Parser Entry -----

ASTNode *Parser::parse()
{
    std::cout << "Starting parsing\n"; // Debugging line
    ASTNode *ast = statement();
    printAST(ast, 0);
    return ast;
}

// ----- AST Printer -----

void Parser::printAST(ASTNode *node, int depth)
{
    if (!node)
        return;

    for (int i = 0; i < depth; ++i)
        std::cout << "   ";
    std::cout << "+-- " << node->value << "\n";

    printAST(node->left, depth + 1);
    printAST(node->right, depth + 1);
    if (node->extra)
        printAST(node->extra, depth + 1);
}

// ----- Evaluator (basic) -----

int Parser::evaluate(ASTNode *node)
{
    if (!node)
        throw std::runtime_error("Null node");

    switch (node->type)
    {
    case TokenType::NUMBER:
        return std::stoi(node->value);
    case TokenType::PLUS:
        return evaluate(node->left) + evaluate(node->right);
    case TokenType::MINUS:
        return evaluate(node->left) - evaluate(node->right);
    case TokenType::MULTIPLY:
        return evaluate(node->left) * evaluate(node->right);
    case TokenType::DIVIDE:
        return evaluate(node->left) / evaluate(node->right);
    case TokenType::GT:
        return evaluate(node->left) > evaluate(node->right);
    case TokenType::LT:
        return evaluate(node->left) < evaluate(node->right);
    case TokenType::GE:
        return evaluate(node->left) >= evaluate(node->right);
    case TokenType::LE:
        return evaluate(node->left) <= evaluate(node->right);
    case TokenType::EQ:
        return evaluate(node->left) == evaluate(node->right);
    case TokenType::NEQ:
        return evaluate(node->left) != evaluate(node->right);
    case TokenType::IF:
        return evaluate(node->left) ? evaluate(node->right) : evaluate(node->extra);
    case TokenType::ASSIGN:
    {
        int val = evaluate(node->left);
        variables[node->value] = val;
        return val;
    }
    case TokenType::IDENTIFIER:
        return variables[node->value];
    default:
        throw std::runtime_error("Unknown node type in evaluate()");
    }
}
