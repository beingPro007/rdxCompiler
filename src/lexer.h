#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

enum class TokenType
{
    NUMBER,
    IDENTIFIER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    ASSIGN,
    SEMICOLON,
    LPAREN,
    RPAREN,
    IF,
    ELSE,
    EQ,  // ==
    NEQ, // !=
    GT,  // >
    LT,  // <
    GE,  // >=
    LE,  // <=
    WHILE,
    LBRACE,
    RBRACE,
    LTE,
    GTE,
    END
};

struct Token
{
    TokenType type;
    std::string value;

    Token(TokenType t, const std::string &v) : type(t), value(v) {}
};

class Lexer
{
public:
    Lexer(const std::string &input);
    std::vector<Token> tokenize();

private:
    std::string input;
    size_t pos;
    char currentChar;

    void advance();
    char peek();
    void skipWhitespace();
    std::string number();
    std::string identifier();
};

#endif
