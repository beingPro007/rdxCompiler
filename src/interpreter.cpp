#include "interpreter.h"

int Interpreter::evaluate(ASTNode *root)
{
    if (!root)
        return 0;

    if (root->type == TokenType::NUMBER)
        return std::stoi(root->value);

    int leftVal = evaluate(root->left);
    int rightVal = evaluate(root->right);

    if (root->type == TokenType::PLUS)
        return leftVal + rightVal;
    if (root->type == TokenType::MINUS)
        return leftVal - rightVal;
    if (root->type == TokenType::MULTIPLY)
        return leftVal * rightVal;
    if (root->type == TokenType::DIVIDE)
        return leftVal / rightVal;

    return 0;
}
