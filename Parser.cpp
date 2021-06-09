//
// Created by Ignacio R. de Almeida on 5/8/21.
//

#include "Parser.h"
//void Parser::Parse() {
//    ParseDatalogProgram();
//    return;
//}
void Parser::ToMatch(std::vector<Token*> parseVector, TokenType givenType){
    if(parseVector.at(index)->GetType() == givenType){
        index++;
    }
    //I also need to check if EOF is all that's left
    else{
        throw "Failure!\n\t" + parseVector.at(index)->toString();
    }

}
DatalogProgram Parser::ParseDatalogProgram(std::vector<Token*> parseVector){
    //datalogProgram	->	SCHEMES COLON scheme schemeList FACTS COLON factList
    //                      RULES COLON ruleList QUERIES COLON query queryList EOF
    ToMatch(parseVector, TokenType::SCHEMES);
    ToMatch(parseVector, TokenType::COLON);
    ParseScheme(parseVector);
    ParseSchemeList(parseVector);
    ToMatch(parseVector, TokenType::FACTS);
    ToMatch(parseVector, TokenType::COLON);
    ParseFactList(parseVector);
    ToMatch(parseVector, TokenType::RULES);
    ToMatch(parseVector, TokenType::COLON);
    ParseRuleList(parseVector);
    ToMatch(parseVector, TokenType::QUERIES);
    ToMatch(parseVector, TokenType::COLON);
    ParseQuery(parseVector);
    ParseQueryList(parseVector);
    ToMatch(parseVector, TokenType::EEOF);
    mainDatalog.SetDomains();
    return mainDatalog;
}
void Parser::ParseSchemeList(std::vector<Token*> parseVector){
    parameters.clear();
    //schemeList	->	scheme schemeList | lambda
    if(parseVector.at(index)->GetType() == TokenType::ID) {
        ParseScheme(parseVector);
        ParseSchemeList(parseVector);
    }
    else if(parseVector.at(index)->GetType() == TokenType::FACTS){
        return;
    }
}
void Parser::ParseFactList(std::vector<Token*> parseVector){
    parameters.clear();
    //factList	->	fact factList | lambda
    if(parseVector.at(index)->GetType() == TokenType::ID) {
        ParseFact(parseVector);
        ParseFactList(parseVector);
    }
    else if(parseVector.at(index)->GetType() == TokenType::RULES) {
        return;
    }
}
void Parser::ParseRuleList(std::vector<Token*> parseVector){
    parameters.clear();
    //ruleList	->	rule ruleList | lambda
    if(parseVector.at(index)->GetType() == TokenType::ID) {
        ParseRule(parseVector);
        ParseRuleList(parseVector);
    }
    else if(parseVector.at(index)->GetType() == TokenType::QUERIES) {
        return;
    }
}
void Parser::ParseQueryList(std::vector<Token*> parseVector){
    parameters.clear();
    //queryList	->	query queryList | lambda
    if(parseVector.at(index)->GetType() == TokenType::ID) {
        ParseQuery(parseVector);
        ParseQueryList(parseVector);
    }
    else if(parseVector.at(index)->GetType() == TokenType::EEOF){
        return;
    }
}
void Parser::ParseScheme(std::vector<Token*> parseVector){
    id = parseVector.at(index)->GetValue();
    //scheme   	-> 	ID LEFT_PAREN ID idList RIGHT_PAREN
    ToMatch(parseVector, TokenType::ID);
    ToMatch(parseVector, TokenType::LEFT_PAREN);

    //Filling vector todo
    Parameter parameter(parseVector.at(index)->GetValue(), ParameterType::ID);
    parameters.push_back(parameter);

    ToMatch(parseVector, TokenType::ID);

    ParseIdList(parseVector);
    ToMatch(parseVector, TokenType::RIGHT_PAREN);

    //Filling vector TODO
    predicate = Predicate(id, parameters);
    mainDatalog.SetSchemes(predicate);

}
void Parser::ParseFact(std::vector<Token*> parseVector){
    id = parseVector.at(index)->GetValue();
    //fact    	->	ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
    ToMatch(parseVector, TokenType::ID);
    ToMatch(parseVector, TokenType::LEFT_PAREN);
    //TODO
    Parameter parameter(parseVector.at(index)->GetValue(), ParameterType::STRING);
    parameters.push_back(parameter);

    ToMatch(parseVector, TokenType::STRING);

    ParseStringList(parseVector);

    //Filling vector TODO
    predicate = Predicate(id, parameters);
    mainDatalog.SetFacts(predicate);

    ToMatch(parseVector, TokenType::RIGHT_PAREN);
    ToMatch(parseVector, TokenType::PERIOD);
}
void Parser::ParseRule(std::vector<Token*> parseVector){
    //rule    	->	headPredicate COLON_DASH predicate predicateList PERIOD
    ParseHeadPredicate(parseVector);
    //TODO
    headPredicate = Predicate(id, parameters);
    parameters.clear();
    id = parseVector.at(index)->GetValue();

    ToMatch(parseVector, TokenType::COLON_DASH);
    ParsePredicate(parseVector);
    ParsePredicateList(parseVector);
    ToMatch(parseVector, TokenType::PERIOD);

    //TODO - OUT OF RANGE
    Rule thisRule(headPredicate, predicates);
    mainDatalog.SetRules(thisRule);
    predicates.clear();

}
void Parser::ParseQuery(std::vector<Token*> parseVector){
    //query	        ->      predicate Q_MARK
    ParsePredicate(parseVector);
    mainDatalog.SetQueries(predicate);
    ToMatch(parseVector, TokenType::Q_MARK);
}
void Parser::ParseHeadPredicate(std::vector<Token*> parseVector){
    id = parseVector.at(index)->GetValue();
    //headPredicate	->	ID LEFT_PAREN ID idList RIGHT_PAREN
    ToMatch(parseVector, TokenType::ID);
    ToMatch(parseVector, TokenType::LEFT_PAREN);

    //TODO
    Parameter parameter(parseVector.at(index)->GetValue(), ParameterType::ID);
    parameters.push_back(parameter);

    ToMatch(parseVector, TokenType::ID);
    ParseIdList(parseVector);
    ToMatch(parseVector, TokenType::RIGHT_PAREN);

}
void Parser::ParsePredicate(std::vector<Token*> parseVector){
    id = parseVector.at(index)->GetValue();
    //predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN
    ToMatch(parseVector, TokenType::ID);
    ToMatch(parseVector, TokenType::LEFT_PAREN);
    ParseParameter(parseVector);
    ParseParameterList(parseVector);
    ToMatch(parseVector, TokenType::RIGHT_PAREN);

    //TODO
    predicate = Predicate(id, parameters);
    predicates.push_back(predicate);
}
void Parser::ParsePredicateList(std::vector<Token*> parseVector){
    parameters.clear();
    //predicateList	->	COMMA predicate predicateList | lambda
    if(parseVector.at(index)->GetType() == TokenType::COMMA) {
        ToMatch(parseVector, TokenType::COMMA);
        ParsePredicate(parseVector);
        ParsePredicateList(parseVector);
    }
    else if(parseVector.at(index)->GetType() == TokenType::PERIOD){
        return;
    }
}
void Parser::ParseParameterList(std::vector<Token*> parseVector){
    //parameterList	-> 	COMMA parameter parameterList | lambda
    if(parseVector.at(index)->GetType() == TokenType::COMMA) {
        ToMatch(parseVector, TokenType::COMMA);
        ParseParameter(parseVector);
        ParseParameterList(parseVector);
    }
    else if(parseVector.at(index)->GetType() == TokenType::RIGHT_PAREN) {
        return;
    }
}
void Parser::ParseStringList(std::vector<Token*> parseVector){
    //stringList	-> 	COMMA STRING stringList | lambda
    if(parseVector.at(index)->GetType() == TokenType::COMMA) {
        ToMatch(parseVector, TokenType::COMMA);

        //TODO
        Parameter parameter(parseVector.at(index)->GetValue(), ParameterType::STRING);
        parameters.push_back(parameter);

        ToMatch(parseVector, TokenType::STRING);
        ParseStringList(parseVector);
    }
    else if(parseVector.at(index)->GetType() == TokenType::RIGHT_PAREN){
        return;
    }


}
void Parser::ParseIdList(std::vector<Token*> parseVector){
    //idList  	-> 	COMMA ID idList | lambda
    if(parseVector.at(index)->GetType() == TokenType::COMMA) {
        ToMatch(parseVector, TokenType::COMMA);

        //Filling vector todo
        Parameter parameter(parseVector.at(index)->GetValue(), ParameterType::ID);
        parameters.push_back(parameter);

        ToMatch(parseVector, TokenType::ID);
        ParseIdList(parseVector);
    }
    else if(parseVector.at(index)->GetType() == TokenType::RIGHT_PAREN) {
        return;
    }
}
void Parser::ParseParameter(std::vector<Token*> parseVector){
    //parameter	->	STRING | ID
    if(parseVector.at(index)->GetType() == TokenType::STRING) {
        //TODO
        Parameter parameter(parseVector.at(index)->GetValue(), ParameterType::STRING);
        parameters.push_back(parameter);

        ToMatch(parseVector, TokenType::STRING);
    }
    else if(parseVector.at(index)->GetType() == TokenType::ID){
        //TODO
        Parameter parameter(parseVector.at(index)->GetValue(), ParameterType::ID);
        parameters.push_back(parameter);

        ToMatch(parseVector, TokenType::ID);
    }
}