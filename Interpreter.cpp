//
// Created by Ignacio R. de Almeida on 5/22/21.
//

#include "Interpreter.h"
Interpreter::Interpreter(DatalogProgram transferredDatalog){
    this->datalog = transferredDatalog;
    schemes = datalog.GetSchemes();
    facts = datalog.GetFacts();
    queries = datalog.GetQueries();
    rules = datalog.GetRules();
    SetRelations();
    SetTuples();
    EvaluateRules();
    EvaluateQueries();
}
void Interpreter::SetRelations(){
    for (Predicate scheme : schemes){
        std::vector<std::string> parameters;

        for (Parameter parameter : scheme.GetParameters()){
            parameters.push_back(parameter.GetValue());
        }

        Header header(parameters);
        Relation relation(scheme.GetId(), header);
        database.SetDatabase(scheme.GetId(), relation);
    }
}
void Interpreter::SetTuples(){
    for (Predicate fact : facts){
        std::vector<std::string> values;

        for( Parameter parameter : fact.GetParameters()){
            values.push_back(parameter.GetValue());
        }
        Tuple tuple(values);
        std::string id = fact.GetId();
        Relation* relation = database.GetRelationPointer(id);
        relation->AddTuple(tuple);
    }
}

Relation Interpreter::EvaluatePredicate(Predicate &p) {
    Relation relation = database.GetRelation(p.GetId());
    std::vector<std::string> parameters;
    std::vector<int> renameIndices;
    std::vector<int> projectIndices;
    std::vector<std::string> newParameters;
    std::vector<int>newParametersIndexes;
    std::string name = p.GetId();
    Header header = relation.GetHeader();


    for(Parameter parameter : p.GetParameters()){
        parameters.push_back(parameter.GetValue());
    }

    for(unsigned int i = 0; i < parameters.size(); i++){
        if(parameters.at(i).at(0) == '\''){
            relation = relation.Select(i, parameters.at(i));
        }
        else{
            bool duplicateVariable = false;
            int index = 0;
            for(unsigned int j = 0; j < newParameters.size(); j++){
                if(parameters.at(i) == newParameters.at(j)){
                    duplicateVariable = true;
                    index = j;
                }
            }
            if(duplicateVariable){
                relation = relation.Select(index, i);
            }
            else if(newParameters.size() == 0){
                newParameters.push_back(parameters.at(i));
                newParametersIndexes.push_back(i);
            }
            else{
                newParameters.push_back(parameters.at(i));
                newParametersIndexes.push_back(i);
            }
        }
    }
    relation = relation.Project(newParametersIndexes);
    relation = relation.Rename(newParameters);

    return relation;
}

void Interpreter::EvaluateQueries() {
    std::cout << "Query Evaluation" << std::endl;
    for(Predicate query : queries){
        Relation relation = EvaluatePredicate(query);
        std::cout << query.ToString() << "? ";
        if(relation.GetRows().size() > 0){
            std::cout << "Yes(" << relation.GetRows().size() << ")" << std::endl;

            bool itExists = false;
            for(Parameter p : query.GetParameters()){
                if(p.GetType() == ParameterType::ID){
                    itExists = true;
                }
            }
            if(itExists){
                std::cout << relation.ToString();
            }
        }
        else{
            std::cout << "No" << std::endl;
        }
    }
}
void Interpreter::ToString() {
    std::cout << database.ToString() << std::endl;
}

void Interpreter::EvaluateRules(){
    Graph graph = Graph(rules);
    std::cout << graph.ToString() << std::endl;
    //std::cout << graph.ReverseToString() << std::endl;
    graph.DFS();
    graph.DFSForest();
    std::vector<std::set<int>> SCC = graph.GetSCC();

    std::cout << "Rule Evaluation" << std::endl;
    int initialCount = 0;
    int postCount = 0;

    for(unsigned int i = 0; i < SCC.size(); i++) {
        std::cout << "SCC: ";
        int itPassed = 0;
        std::ostringstream output;
        for (std::set<int>::iterator it = SCC.at(i).begin(); it != SCC.at(i).end(); it++) {
            output << "R" << *it;
            if (it != SCC.at(i).end()) {
                output << ",";
            }
        }
        std::string mainOutput = output.str();
        if (mainOutput.size() != 0) {
            mainOutput.pop_back();
        }
        std::cout << mainOutput << std::endl;

        do{
            initialCount = GetDatabaseSize();
            bool done = false;

            for(std::set<int>::iterator it = SCC.at(i).begin(); it != SCC.at(i).end(); it++){
                EvaluateRule(rules.at(*it));
                if((SCC.at(i).size() == 1) && (!graph.selfRule(*(SCC.at(i).begin())))){
                    done = true;
                }
            }

            postCount = database.DatabaseCounter();
            itPassed++;
            //use jump statement to leave the do while loop and cout passes
            if (done) goto exit;
        }while(initialCount != postCount);
        exit:
//    std::cout << std::endl << "Schemes populated after " << itPassed << " passes through the Rules." << std::endl << std::endl;
        std::cout << itPassed << " passes: " << mainOutput << std::endl;
    }
    std::cout << std::endl;
}

void Interpreter::EvaluateRule(Rule& rule) {
//    Evaluate the predicates on the right-hand side of the rule
    Relation relation = EvaluatePredicate(rule.GetPredicateList().at(0));
//    Join the relations that result
    for(unsigned int i = 0; i < rule.GetPredicateList().size(); i++){
        Relation r2  = EvaluatePredicate(rule.GetPredicateList().at(i));
        relation = relation.Join(r2);
    }
//    Project the columns that appear in the head predicate
    std::vector<int> indices;
    for(unsigned int i = 0; i < rule.GetHeadPredicate().GetParameters().size(); ++i){
        for (unsigned int j = 0; j < relation.GetHeader().GetAttributes().size(); ++j){
            if(rule.GetHeadPredicate().GetParameters().at(i).GetValue() == relation.GetHeader().GetAttributes().at(j)){
                indices.push_back(j);
            }
        }
    }

    relation = relation.Project(indices);
    std::string name = rule.GetHeadPredicate().GetId();

    //Rename the relation to make it union-compatible
    for(unsigned int i = 0; i < relation.GetHeader().GetAttributes().size(); i++){
        for(unsigned int j = 0; j < schemes.size(); j++){
            if(name == schemes.at(j).GetId()){
                relation.Rename(i, schemes.at(j).GetParameters().at(i).GetValue());
            }
        }
    }
    std::cout << rule.ToString() << "." << std::endl;
    //    Union with the relation in the database
    for(unsigned int k = 0; k < rule.GetPredicateList().size(); k++){
         relation = database.GetDatabase().at(name).Union(relation);
    }
}

int Interpreter::GetDatabaseSize(){
    int size = 0;

    for(std::map<std::string, Relation>::iterator it = database.GetDatabase().begin(); it != database.GetDatabase().end(); it++){
        size += it->second.GetRows().size();
    }

    return size;
}