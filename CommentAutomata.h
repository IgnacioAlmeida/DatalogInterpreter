//
// Created by Ignacio R. de Almeida on 5/1/21.
//

#ifndef PROJECT_1_COMMENTAUTOMATA_H
#define PROJECT_1_COMMENTAUTOMATA_H
#include "Automaton.h"

class CommentAutomata : public Automaton{
private:
    void S1(const std::string& input);
    void S2(const std::string& input);

public:
    CommentAutomata() : Automaton(TokenType::COMMENT) {};
    void S0(const std::string& input);
};


#endif //PROJECT_1_COMMENTAUTOMATA_H
