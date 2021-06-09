#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include <iostream>
#include <vector>
#include "MatcherAutomaton.h"
#include "Token.h"
#include "CommentAutomata.h"
#include "StringAutomata.h"
#include "IDAutomata.h"

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    for(int i = 0; i < (int)automata.size(); i++){
        delete automata.at(i);
    }
    for(int i = 0; i < (int)tokens.size(); i++){
        delete tokens.at(i);
    }
}

void Lexer::CreateAutomata() {
    automata.push_back(new MatcherAutomaton(",", TokenType::COMMA));
    automata.push_back(new MatcherAutomaton(".", TokenType::PERIOD));
    automata.push_back(new MatcherAutomaton("?", TokenType::Q_MARK));
    automata.push_back(new MatcherAutomaton("(", TokenType::LEFT_PAREN));
    automata.push_back(new MatcherAutomaton(")", TokenType::RIGHT_PAREN));
    automata.push_back(new MatcherAutomaton("*", TokenType::MULTIPLY));
    automata.push_back(new MatcherAutomaton("+", TokenType::ADD));
    automata.push_back(new MatcherAutomaton("Schemes", TokenType::SCHEMES));
    automata.push_back(new MatcherAutomaton("Facts", TokenType::FACTS));
    automata.push_back(new MatcherAutomaton("Rules", TokenType::RULES));
    automata.push_back(new MatcherAutomaton("Queries", TokenType::QUERIES));
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new CommentAutomata());
    automata.push_back(new StringAutomata);
    automata.push_back(new IDAutomata);
    //automata.push_back((new MatcherAutomaton("", TokenType::EEOF)));
}

void Lexer::Run(std::string& input) {
    lineNumber = 1;

    // While there are more characters to tokenize
    while(input.size() > 0) {
        int maxRead = 0;
        Automaton* maxAutomaton = automata[0];

        // TODO: you need to handle whitespace inbetween tokens
        while(isspace(input[0])){
            if(input[0] == '\n'){
                lineNumber++;
            }
            input.erase(0,1);
        }


        // Here is the "Parallel" part of the algorithm
        // Each automaton runs with the same input

        for (unsigned int i = 0; i < automata.size();i++){
            int inputRead = automata.at(i)->Start(input);
            if(inputRead > maxRead){
                maxRead = inputRead;
                maxAutomaton = automata.at(i);
            }
        }
        // Here is the "Max" part of the algorithm
        if (maxRead > 0) {
            Token* newToken = maxAutomaton->CreateToken(input.substr(0, maxRead), lineNumber);
            //newToken->SetTokenType(input.substr(0, maxRead));
            lineNumber+=maxAutomaton->NewLinesRead();
            //Deletes tokens that are comments
            if(newToken->GetType() != TokenType::COMMENT){
                tokens.push_back(newToken);
            }
            if(newToken->GetType() == TokenType::COMMENT){
                delete newToken;
            }
            input.erase(0, maxRead);
        }
        // No automaton accepted input
        // Single character undefined token
        else if(input.size() == 0){
            break;
        }
        else {
            maxRead = 1;
            Token* newToken = new Token(TokenType::UNDEFINED, input.substr(0, 1), lineNumber);
            tokens.push_back(newToken);
            input.erase(0, 1);
        }
    }
    Token* endOfFileToken = new Token(TokenType::EEOF, "",lineNumber);
    tokens.push_back(endOfFileToken);
    //toString();
    //std::cout << "Total Tokens = " << tokens.size() << std::endl;



}

void Lexer::toString() {
    for(unsigned int i = 0; i < tokens.size(); i++){
        std::cout << tokens.at(i)->toString() << std::endl;
    }
}

std::vector<Token*> Lexer::GetTokens() {
    return tokens;
}