//
// Created by Ignacio R. de Almeida on 5/1/21.
//

#include "IDAutomata.h"

void IDAutomata::S0(const std::string &input) {
    if(isalpha(input[inputRead])){
        inputRead++;
        index++;
        S1(input);
    }
    else
        Serr();
}

void IDAutomata::S1(const std::string &input){
    while(isalpha(input[inputRead]) || isdigit(input[inputRead])){
        inputRead++;
        index++;
        S1(input);
    }
}