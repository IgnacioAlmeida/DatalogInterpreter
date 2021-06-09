//
// Created by Ignacio R. de Almeida on 5/1/21.
//

#include "CommentAutomata.h"
//Create three - line, block and bad comment - Walter TA tip
void CommentAutomata::S0(const std::string& input) {
    if(input[inputRead] == '#'){
        inputRead++;
        index++;
        S1(input);
    }
    else
        Serr();
}

void CommentAutomata::S1(const std::string& input){
    if(input[inputRead] == '|'){
        inputRead++;
        index++;
        S2(input);
    }
    else while(input[inputRead] != '\n' && inputRead != (int)input.size()){
        inputRead++;
        index++;
    }
    if (input[inputRead] == '\n' || inputRead == (int)input.size()) {
        return;
    }
}

void CommentAutomata::S2(const std::string &input) {
    while (input[inputRead] != '|' && inputRead != (int)input.size()){
        if(input[inputRead] == '\n'){
            this->newLines+=1;
        }
        inputRead++;
        index++;
    }

    if (input[inputRead] == '|') {
        inputRead++;
        index++;
        if(input[inputRead] == '#'){
            inputRead++;
            index++;
            return;
        }
        else
            S2(input);//loop back
    }

    if(inputRead == (int)input.size()) {
        type = TokenType::UNDEFINED;
        return;
    }
}
