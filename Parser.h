//
// Created by Ignacio R. de Almeida on 5/8/21.
//

#ifndef PROJECT_1_PARSER_H
#define PROJECT_1_PARSER_H
#include "Token.h"
#include <vector>
#include <iostream>
#include "DatalogProgram.h"
#include "Rule.h"
#include "Parameter.h"
#include "Predicate.h"

class Parser {
private:
    int index;
    std::vector<Predicate> predicates;
    std::vector<Parameter> parameters;
    DatalogProgram mainDatalog;
    std::string id;
    Predicate predicate;
    Predicate headPredicate;
public:
    Parser(){};
//    void Parse();
    void ToMatch(std::vector<Token*> parseVector, TokenType givenType);
    DatalogProgram ParseDatalogProgram(std::vector<Token*> parseVector);
    void ParseSchemeList(std::vector<Token*> parseVector);
    void ParseFactList(std::vector<Token*> parseVector);
    void ParseRuleList(std::vector<Token*> parseVector);
    void ParseQueryList(std::vector<Token*> parseVector);
    void ParseScheme(std::vector<Token*> parseVector);
    void ParseFact(std::vector<Token*> parseVector);
    void ParseRule(std::vector<Token*> parseVector);
    void ParseQuery(std::vector<Token*> parseVector);
    void ParseHeadPredicate(std::vector<Token*> parseVector);
    void ParsePredicate(std::vector<Token*> parseVector);
    void ParsePredicateList(std::vector<Token*> parseVector);
    void ParseParameterList(std::vector<Token*> parseVector);
    void ParseStringList(std::vector<Token*> parseVector);
    void ParseIdList(std::vector<Token*> parseVector);
    void ParseParameter(std::vector<Token*> parseVector);
    std::string ToString(){return mainDatalog.ToString();}

};


#endif //PROJECT_1_PARSER_H
