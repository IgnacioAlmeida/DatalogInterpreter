//
// Created by Ignacio R. de Almeida on 5/1/21.
//

#include "StringAutomata.h"

void StringAutomata::S0(const std::string &input) {
    if(input[inputRead] == '\''){
        inputRead++;
        index++;
        S1(input);
    }
    else
        Serr();
}

void StringAutomata::S1(const std::string &input){

    while(((input[inputRead] == '\'') && (input[inputRead + 1] == '\'')) ||
            ((input[inputRead] != '\'') && (inputRead < (int)input.size()))){

        if(input[inputRead] == '\'' && input[inputRead + 1] == '\''){
            inputRead++;
            index++;
        }
        if(input[inputRead] =='\n') {
            this->newLines++;
        }
        inputRead++;
        index++;
        if(inputRead == (int)input.size()){
            type = TokenType::UNDEFINED;
            return;
        }
    }
    if(input[inputRead] == '\''){
        inputRead++;
        index++;
        return;
    }
}
