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
        else if (isalpha(currentChar)) // Detect variable names (identifiers)
        {
            std::string id;
            while (pos < input.length() && isalnum(input[pos]))
            {
                id += input[pos];
                advance();
            }
            tokens.push_back({TokenType::IDENTIFIER, id});
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
        else if (currentChar == '=')
        {
            tokens.push_back({TokenType::ASSIGN, "="});
            advance();
        }
        else if (currentChar == '{')
        {
            tokens.push_back({TokenType::LBRACE, "{"});
            pos++;
        }
        else if (currentChar == '}')
        {
            tokens.push_back({TokenType::RBRACE, "}"});
            pos++;
        }
        else if (std::isalpha(currentChar))
        {
            std::string identifier;
            while (pos < input.length() && std::isalnum(input[pos]))
            {
                identifier += input[pos++];
            }

            if (identifier == "if")
                tokens.push_back({TokenType::IF, identifier});
            else if (identifier == "else")
                tokens.push_back({TokenType::ELSE, identifier});
            else if (identifier == "while")
                tokens.push_back({TokenType::WHILE, identifier});
            else
                tokens.push_back({TokenType::IDENTIFIER, identifier});
        }

        else
        {
            advance(); // Ignore spaces and unknown characters
        }
    }

    tokens.push_back({TokenType::END, ""});
    return tokens;
}
