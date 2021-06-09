//
// Created by Ignacio R. de Almeida on 6/7/21.
//

#include "Graph.h"

Graph::Graph(std::vector<Rule> rules){
    for(unsigned int i = 0; i <  rules.size(); i++){
        adjacencies[i];
        reverseAdjacencies[i];
    }
    //Creates adjacencies and reverseAdjacencies
    for(unsigned int i = 0; i < rules.size(); i++){
        std::vector<Predicate> parameters = rules.at(i).GetPredicateList();
        for(unsigned int j = 0; j < parameters.size(); j++){
            for(unsigned int k = 0; k < rules.size(); k++){
                if(rules.at(k).GetHeadPredicate().GetId() == parameters.at(j).GetId()){
                    adjacencies[i].insert(k);
                    reverseAdjacencies[k].insert(i);
                    visited[i] = false;
                }
            }
        }
    }
}
std::string Graph::ToString() {
    std::string output =  "Dependency Graph\n";
    for(std::map<int, std::set<int>>::iterator it = adjacencies.begin(); it != adjacencies.end(); it++){
        output += "R" + std::to_string(it->first) + ":";
        for(std::set<int>::iterator itr = it->second.begin(); itr != it->second.end(); itr++){
            output += "R" + std::to_string(*itr) + ",";
        }
        if(it->second.size() > 0){
            output.pop_back();
        }
        output += "\n";
    }
    return output;
}

std::string Graph::ReverseToString() {
    std::string output =  "Reverse Dependency Graph\n";
    for(std::map<int, std::set<int>>::iterator it = reverseAdjacencies.begin(); it != reverseAdjacencies.end(); it++){
        output += "R" + std::to_string(it->first) + ":";
        for(std::set<int>::iterator itr = it->second.begin(); itr != it->second.end(); itr++){
            output += "R" + std::to_string(*itr) + ",";
        }
        if(it->second.size() > 0){
            output.pop_back();
        }
        output += "\n";
    }
    return output;
}