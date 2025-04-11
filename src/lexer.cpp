#include "lexer.h"
#include <cctype>
#include <stdexcept>
#include <iostream> // Add this line at the top of your lexer.cpp

Lexer::Lexer(const std::string &input) : input(input), pos(0)
{
    currentChar = pos < input.size() ? input[pos] : '\0';
}

void Lexer::advance()
{
    pos++;
    currentChar = pos < input.size() ? input[pos] : '\0';
}

char Lexer::peek()
{
    return (pos + 1 < input.size()) ? input[pos + 1] : '\0';
}

void Lexer::skipWhitespace()
{
    while (isspace(currentChar))
    {
        advance();
    }
}

std::string Lexer::number()
{
    std::string result;
    while (isdigit(currentChar))
    {
        result += currentChar;
        advance();
    }
    return result;
}

std::string Lexer::identifier()
{
    std::string result;
    while (isalnum(currentChar) || currentChar == '_')
    {
        result += currentChar;
        advance();
    }
    return result;
}

std::vector<Token> Lexer::tokenize()
{
    std::vector<Token> tokens;

    while (currentChar != '\0')
    {
        skipWhitespace();

        // Tokenize numbers
        if (isdigit(currentChar))
        {
            tokens.push_back({TokenType::NUMBER, number()});
        }
        // Tokenize identifiers and keywords (if, else, while)
        else if (isalpha(currentChar))
        {
            std::string id = identifier();
            if (id == "if")
                tokens.push_back({TokenType::IF, id});
            else if (id == "else")
                tokens.push_back({TokenType::ELSE, id});
            else if (id == "while")
                tokens.push_back({TokenType::WHILE, id});
            else
                tokens.push_back({TokenType::IDENTIFIER, id});
        }
        // Tokenize arithmetic operators
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
        // Tokenize parentheses and braces
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
        else if (currentChar == '{')
        {
            tokens.push_back({TokenType::LBRACE, "{"});
            advance();
        }
        else if (currentChar == '}')
        {
            tokens.push_back({TokenType::RBRACE, "}"});
            advance();
        }
        // Tokenize semicolons
        else if (currentChar == ';')
        {
            tokens.push_back({TokenType::SEMICOLON, ";"});
            advance();
        }
        // Tokenize assignment operator
        else if (currentChar == '=')
        {
            if (peek() == '=')
            {
                advance();
                advance();
                tokens.push_back({TokenType::EQ, "=="});
            }
            else
            {
                tokens.push_back({TokenType::ASSIGN, "="});
                advance();
            }
        }
        // Tokenize comparison operators
        else if (currentChar == '!')
        {
            if (peek() == '=')
            {
                advance();
                advance();
                tokens.push_back({TokenType::NEQ, "!="});
            }
            else
            {
                throw std::runtime_error("Unexpected character '!' at position " + std::to_string(pos));
            }
        }
        else if (currentChar == '<')
        {
            if (peek() == '=')
            {
                advance();
                advance();
                tokens.push_back({TokenType::LE, "<="});
            }
            else
            {
                tokens.push_back({TokenType::LT, "<"});
                advance();
            }
        }
        else if (currentChar == '>')
        {
            if (peek() == '=')
            {
                advance();
                advance();
                tokens.push_back({TokenType::GE, ">="});
            }
            else
            {
                tokens.push_back({TokenType::GT, ">"});
                advance();
            }
        }
        // Handle unexpected characters
        else
        {
            throw std::runtime_error("Unexpected character: " + std::string(1, currentChar));
        }

    }

    // Add the END token to mark the end of the input
    tokens.push_back({TokenType::END, ""});

    return tokens;
}
