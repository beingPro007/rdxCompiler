#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <string>

enum class TokenType
{
    NUMBER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    LPAREN,
    RPAREN,
    IDENTIFIER, // For variable names like x
    ASSIGN,     // For the assignment operator '='
    END,
    IF,
    ELSE,
    WHILE,
    LT,
    GT,
    LTE,
    GTE,
    EQ,
    NEQ,
    LBRACE,
    RBRACE,
};

struct Token
{
    TokenType type;
    std::string value;
};

class Lexer
{
public:
    std::string input;
    size_t pos;

    Lexer(const std::string &input);
    std::vector<Token> tokenize();

private:
    void advance();
};

#endif
