//
// Created by Ignacio R. de Almeida on 6/7/21.
//

#ifndef PROJECT_1_GRAPH_H
#define PROJECT_1_GRAPH_H
#include <map>
#include <set>
#include <iostream>
#include "Rule.h"
#include <set>
#include "Predicate.h"
//TODO Two graph objects, one for forward and one for reverse
class Graph {
private:
    //int is rule index  and set<int> are all the rules that have edges with the node asked
    std::map<int, std::set<int>> adjacencies;
    std::map<int, std::set<int>> reverseAdjacencies;
    std::map<int, bool> visited;
public:
    Graph(std::vector<Rule> rules);
    std::string ToString();
    std::string ReverseToString();
};


#endif //PROJECT_1_GRAPH_H
