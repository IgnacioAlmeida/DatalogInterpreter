#ifndef TOKEN_H
#define TOKEN_H
#include <string>

 enum class TokenType {
    COMMA,
    PERIOD,
    Q_MARK,
    LEFT_PAREN,
    RIGHT_PAREN,
    COLON,
    COLON_DASH,
    MULTIPLY,
    ADD,
    SCHEMES,
    FACTS,
    RULES,
    QUERIES,
    ID,
    STRING,
    COMMENT,
    EEOF,
    UNDEFINED
};

class Token
{
private:
    std::string tokenValue;
    int line;
    TokenType type;
public:
    Token(TokenType type, std::string description, int line);
    std::string toString();
    TokenType GetType();
    std::string GetValue();
};

#endif // TOKEN_H

