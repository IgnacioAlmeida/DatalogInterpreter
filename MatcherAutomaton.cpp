//
// Created by Ignacio R. de Almeida on 5/1/21.
//

#include "MatcherAutomaton.h"

MatcherAutomaton::MatcherAutomaton(std::string toMatch, TokenType tokenType){
    this->toMatch = toMatch;
    type = tokenType;
}

void MatcherAutomaton::S0(const std::string& input) {

    Start(input);
}

int MatcherAutomaton::Start(const std::string &input) {
    bool isMatch = true;
    inputRead = 0; // member variable inherited from Automaton class
    for (int i = 0; i < (int)toMatch.size() && isMatch; i++) {
        if (input[i] != toMatch[i]) {
            isMatch = false;
        }
    }
    if (isMatch) {
        inputRead = toMatch.size();
    }
    return inputRead;
}

