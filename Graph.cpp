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
                }
            }
        }
    }

    //Mark all vertices as false since they haven't been visited
    for (unsigned int i = 0; i < reverseAdjacencies.size(); ++i) {
        visited.push_back(false);
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

void Graph::DFS(){
    for(unsigned int i = 0 ; i < reverseAdjacencies.size(); i++) {
        if (!visited.at(i)) {
            DFS(i);
        }
    }
}

void Graph::DFS(int v){
    visited.at(v) = true;
    std::set<int>::iterator it = reverseAdjacencies[v].begin();
    for(unsigned int i = 0; i < reverseAdjacencies[v].size(); i++){
        if(!visited.at(*it)){
            DFS(*it);
        }
        it++;
    }
    postOrder.push(v);
}

void Graph::DFSForest() {
    for(unsigned int i = 0; i < adjacencies.size(); i++){
        visited.at(i) = false;
    }
    while(postOrder.size() > 0){
        if(!visited.at(postOrder.top())){
            std::set<int> mySet;
            DFSForest(postOrder.top(), mySet);
            SCC.push_back(mySet);
        }
        postOrder.pop();
    }
}

std::set<int> Graph::DFSForest(int v, std::set<int>& mySet){
    visited.at(v) = true;
    std::set<int>::iterator it = adjacencies[v].begin();
    for(unsigned int i = 0; i < adjacencies[v].size(); i++){
        if(!visited.at(*it)){
            DFSForest(*it, mySet);
        }
        it++;
    }
    mySet.insert(v);
    return mySet;
}

bool Graph::selfRule(int rule) {
    std::set<int>::iterator it = adjacencies[rule].begin();
    for(unsigned int i = 0; i < adjacencies[rule].size(); i++){
        if(*it == rule){
            return true;
        }
        it++;
    }
    return false;
}