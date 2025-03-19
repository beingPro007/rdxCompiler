#ifndef TOKENS_HPP
#define TOKENS_HPP

#include <string>

// Enum for different token types
enum class TokenType
{
    NUMBER,      // Numeric literals (e.g., 123, 3.14)
    IDENTIFIER,  // Variable names (e.g., myVar, x)
    KEYWORD,     // Reserved words (e.g., "print")
    OPERATOR,    // Operators (+, -, *, /, =)
    PARENTHESIS, // Parentheses ( and )
    END_OF_FILE  // End of file indicator
};

// Token structure
struct Token
{
    TokenType type;
    std::string value;
};

#endif // TOKENS_HPP
