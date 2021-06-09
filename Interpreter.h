//
// Created by Ignacio R. de Almeida on 5/22/21.
//

#ifndef PROJECT_1_INTERPRETER_H
#define PROJECT_1_INTERPRETER_H
#include "Database.h"
#include "Tuple.h"
#include "Header.h"
#include "Relation.h"
#include "Parser.h"
#include <vector>
#include "Graph.h"
//Takes datalog program and turns it into a database to work on
//Stores it as a data member so it can access the scheme, rules, etc and turn them into a database
//datalog program  and database  object as a data member
//Make a relation for each scheme-Predicate, and put that relation in the database data member
//Make a Tuple for each fact-Predicate and put that tuple in the appropriate Relation in the Database

class Interpreter {
private:
    DatalogProgram datalog;
    Database database;
    std::vector<Predicate> schemes;
    std::vector<Predicate> facts;
    std::vector<Rule> rules;
    std::vector<Predicate> queries;
    //Graph forwardGraph
    //Graph backward Graph

public:
    Interpreter(DatalogProgram transferredDatalog);
    void SetRelations();
    void SetTuples();
    int GetDatabaseSize();
    void EvaluateQueries();
    void EvaluateRules();
    void EvaluateRule(Rule& rule);
    Relation EvaluatePredicate(Predicate &p);
    void ToString();
};


#endif //PROJECT_1_INTERPRETER_H
