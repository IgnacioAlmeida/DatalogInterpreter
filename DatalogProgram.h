//
// Created by Ignacio R. de Almeida on 5/12/21.
//

#ifndef PROJECT_1_DATALOGPROGRAM_H
#define PROJECT_1_DATALOGPROGRAM_H
#include <vector>
#include "Token.h"
#include "Predicate.h"
#include "Rule.h"
#include <set>
#include <string>

class DatalogProgram {
private:
    std::vector<Predicate> facts;
    std::vector<Predicate> schemes;
    std::vector<Predicate> queries;
    std::vector<Rule> rules;
    std::set<std::string> domains;
public:
    std::string ToString();
    std::vector<Predicate>& GetFacts();
    std::vector<Predicate>& GetSchemes();
    std::vector<Predicate>& GetQueries();
    std::vector<Rule>& GetRules();
    void SetFacts(Predicate& facts);
    void SetSchemes(Predicate& Schemes);
    void SetQueries(Predicate& Queries);
    void SetDomains();
    void SetRules(Rule& rules);

};


#endif //PROJECT_1_DATALOGPROGRAM_H
