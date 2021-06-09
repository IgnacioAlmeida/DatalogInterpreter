#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include "Automaton.h"
#include "Token.h"

class Lexer
{
private:
    std::vector<Automaton*> automata;
    std::vector<Token*> tokens;
    void CreateAutomata();
    int lineNumber;

public:
    Lexer();
    ~Lexer();

    void Run(std::string& input);
    void toString();
    std::vector<Token*> GetTokens();
};

#endif // LEXER_H

