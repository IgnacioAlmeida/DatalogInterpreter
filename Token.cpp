#include "Token.h"

Token::Token(TokenType type, std::string description, int line) {
    // TODO: initialize all member variables
    this->type = type;
    this->tokenValue = description;
    this->line = line;
}

std::string Token::toString() {
    std::string output;
    std::string description;
    switch(type){
        case TokenType::COMMA: description = "COMMA"; break;
        case TokenType::PERIOD: description = "PERIOD"; break;
        case TokenType::Q_MARK: description = "Q_MARK"; break;
        case TokenType::LEFT_PAREN: description = "LEFT_PAREN"; break;
        case TokenType::RIGHT_PAREN: description = "RIGHT_PAREN"; break;
        case TokenType::MULTIPLY: description = "MULTIPLY"; break;
        case TokenType::ADD: description = "ADD"; break;
        case TokenType::SCHEMES: description = "SCHEMES"; break;
        case TokenType::FACTS: description = "FACTS"; break;
        case TokenType::RULES: description = "RULES"; break;
        case TokenType::QUERIES: description = "QUERIES"; break;
        case TokenType::COLON: description = "COLON"; break;
        case TokenType::COLON_DASH: description = "COLON_DASH"; break;
        case TokenType::COMMENT: description = "COMMENT"; break;
        case TokenType::STRING: description = "STRING"; break;
        case TokenType::ID: description = "ID"; break;
        case TokenType::EEOF: description = "EOF"; break;
        case TokenType::UNDEFINED: description = "UNDEFINED"; break;
    }
    output = "(" + description + ",\"" + tokenValue + "\"," + std::to_string(line) + ")";
    return output;
}

TokenType Token::GetType() {
    return type;
}

std::string Token::GetValue(){
    return tokenValue;
}