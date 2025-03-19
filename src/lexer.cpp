#include "lexer.h"
#include <cctype>

Lexer::Lexer(const std::string &input) : input(input), pos(0) {}

void Lexer::advance()
{
    pos++;
}

std::vector<Token> Lexer::tokenize()
{
    std::vector<Token> tokens;

    while (pos < input.length())
    {
        char currentChar = input[pos];

        if (isdigit(currentChar))
        {
            std::string num;
            while (pos < input.length() && isdigit(input[pos]))
            {
                num += input[pos];
                advance();
            }
            tokens.push_back({TokenType::NUMBER, num});
        }
        else if (currentChar == '+')
        {
            tokens.push_back({TokenType::PLUS, "+"});
            advance();
        }
        else if (currentChar == '-')
        {
            tokens.push_back({TokenType::MINUS, "-"});
            advance();
        }
        else if (currentChar == '*')
        {
            tokens.push_back({TokenType::MULTIPLY, "*"});
            advance();
        }
        else if (currentChar == '/')
        {
            tokens.push_back({TokenType::DIVIDE, "/"});
            advance();
        }
        else if (currentChar == '(')
        {
            tokens.push_back({TokenType::LPAREN, "("});
            advance();
        }
        else if (currentChar == ')')
        {
            tokens.push_back({TokenType::RPAREN, ")"});
            advance();
        }
        else
        {
            advance(); // Ignore spaces and unknown characters
        }
    }

    tokens.push_back({TokenType::END, ""});
    return tokens;
}
