//
// Created by Ignacio R. de Almeida on 5/1/21.
//

#ifndef PROJECT_1_IDAUTOMATA_H
#define PROJECT_1_IDAUTOMATA_H
#include "Automaton.h"

class IDAutomata : public Automaton{
private:
    void S1(const std::string& input);
public:
    IDAutomata() : Automaton(TokenType::ID){};
    void S0(const std::string& input);
};


#endif //PROJECT_1_IDAUTOMATA_H
