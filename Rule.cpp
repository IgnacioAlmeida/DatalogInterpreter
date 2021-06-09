//
// Created by Ignacio R. de Almeida on 5/12/21.
//

#include "Rule.h"

Rule::Rule(Predicate headPredicate, std::vector<Predicate> predicateList) {
    this->headPredicate = headPredicate;
    this->predicateList = predicateList;
}

std::string Rule::ToString() {
    std::string output = headPredicate.ToString() + " :- " + predicateList.at(0).ToString();

    for(unsigned int i = 1; i < predicateList.size(); i++){
        output += "," + predicateList.at(i).ToString();
    }

    return output;
}

Predicate Rule::GetHeadPredicate() {
    return headPredicate;
}

std::vector<Predicate> Rule::GetPredicateList() {
    return predicateList;
}