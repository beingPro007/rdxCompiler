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
    END
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
