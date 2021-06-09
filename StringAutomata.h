//
// Created by Ignacio R. de Almeida on 5/1/21.
//

#ifndef PROJECT_1_STRINGAUTOMATA_H
#define PROJECT_1_STRINGAUTOMATA_H
#include "Automaton.h"

class StringAutomata : public Automaton{
private:
    void S1(const std::string& input);

public:
    StringAutomata() : Automaton(TokenType::STRING){}
    void S0(const std::string& input);
};


#endif //PROJECT_1_STRINGAUTOMATA_H
