//
// Created by Ignacio R. de Almeida on 5/12/21.
//

#include "DatalogProgram.h"

std::string DatalogProgram::ToString() {
    std::string factsList;
    std::string schemesList;
    std::string queriesList;
    std::string rulesList;
    std::string domainsList;
    std::string output;

    factsList = "Facts(" + std::to_string(facts.size()) + "):\n";
    for(int unsigned i = 0; i < facts.size(); i++){
        factsList += " " + facts.at(i).ToString() + ".\n";
    }

    schemesList = "Schemes(" + std::to_string(schemes.size()) + "):\n";
    for(int unsigned i = 0; i < schemes.size(); i++){
        schemesList += " " + schemes.at(i).ToString() + "\n";
    }

    queriesList = "Queries(" + std::to_string(queries.size()) + "):\n";
    for(int unsigned i = 0; i < queries.size(); i++){
        queriesList += " " + queries.at(i).ToString() + "?\n";
    }

    rulesList = "Rules(" + std::to_string(rules.size()) + "):\n";
    for(int unsigned i = 0; i < rules.size(); i++){
        rulesList += " " + rules.at(i).ToString() + ".\n";
    }

    domainsList = "Domain(" + std::to_string(domains.size()) + "):\n";
    std::set<std::string>::iterator it = domains.begin();
    while(it != domains.end()){
        domainsList += " " + *it + "\n";
        it++;
    }

    output = schemesList + factsList + rulesList + queriesList + domainsList;

    return output;
}

std::vector<Predicate>& DatalogProgram::GetFacts(){
    return facts;
}
std::vector<Predicate>& DatalogProgram::GetSchemes(){
    return schemes;
}
std::vector<Predicate>& DatalogProgram::GetQueries(){
    return queries;
}
std::vector<Rule>& DatalogProgram::GetRules(){
    return rules;
}

void DatalogProgram::SetFacts(Predicate& facts){
    this->facts.push_back(facts);
}
void DatalogProgram::SetSchemes(Predicate& schemes){
    this->schemes.push_back(schemes);
}
void DatalogProgram::SetQueries(Predicate& queries){
    this->queries.push_back(queries);
}
void DatalogProgram::SetDomains(){
    for(int unsigned i = 0; i < facts.size(); i++){
        for(Parameter parameter : facts.at(i).GetParameters()){
            if(parameter.GetType() == ParameterType::STRING){
                std::string domain = parameter.GetValue();
                this->domains.insert(domain);
            }
        }
    }
}
void DatalogProgram::SetRules(Rule& rules){
    this->rules.push_back(rules);
}