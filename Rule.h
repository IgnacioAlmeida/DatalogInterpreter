//
// Created by Ignacio R. de Almeida on 5/12/21.
//

#ifndef PROJECT_1_RULE_H
#define PROJECT_1_RULE_H
#include "Predicate.h"
#include <vector>
#include <string>

class Rule {
private:
    //It contains a head predicate followed by :- and a list of predicates
    Predicate headPredicate;
    std::vector<Predicate> predicateList;
public:
    Rule(Predicate headPredicate, std::vector<Predicate> predicateList);

    std::string ToString();
    Predicate GetHeadPredicate();
    std::vector<Predicate> GetPredicateList();
};


#endif //PROJECT_1_RULE_H
