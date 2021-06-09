//
// Created by Ignacio R. de Almeida on 5/22/21.
//

#include "Relation.h"

std::string Relation::ToString() {
    std::string output;

    for (const Tuple& t : rows){
        std::vector<std::string> values = t.GetValues();

        for(unsigned int i = 0; i < header.GetAttributes().size(); i++){
            if(i != 0){
                output += ", ";
            }
            else{
                output += " ";
            }
            if(header.GetAttributes().at(i).at(0) != '\''){
                output += header.GetAttributes().at(i) + "=" + values.at(i);
            }
        }
        output += "\n";
    }
    return output;
}

void Relation::AddTuple(const Tuple& tuple) {
    rows.insert(tuple);
}

Relation Relation::Select(int columnIndex, std::string value) {
    //Create empty relation
    Relation relation(name, header);
    //We only include tuples with matching values at given column
    for(const Tuple& t : rows){
        if(t.GetValues().at(columnIndex) == value){
            relation.AddTuple(t);
        }
    }
    return relation;
}

Relation Relation::Select(int columnIndex, int columnIndexB){
    Relation relation(name, header);
    //We only include tuples with matching values
    for(const Tuple& t : rows){
        if(t.GetValues().at(columnIndex) == t.GetValues().at(columnIndexB)){
            relation.AddTuple(t);
        }
    }
    return relation;
}

Relation Relation::Project(std::vector<int>& indices){
    //Look at all the tuples and keep the desired indices
    std::vector<std::string> columns;
    for(unsigned int i = 0; i < indices.size(); i++){
        columns.push_back(header.GetAttributes().at(indices.at(i)));
    }
    Header newHeader = Header(columns);
    Relation relation(name, newHeader);

    for(const Tuple& t : rows){
        std::vector<std::string> values;
        for(unsigned int i = 0; i < indices.size(); i++){
            values.push_back(t.GetValues().at(indices.at(i)));
        }
        Tuple tuple(values);
        relation.AddTuple(tuple);
    }
    return relation;
}

Relation Relation::Rename(std::vector<std::string> attributes){
    std::vector<std::string> columns;
    for(unsigned int i = 0; i < attributes.size(); i++){
        columns.push_back(attributes.at(i));
    }
    Header newHeader = Header(columns);
    Relation relation(name, newHeader);

    for(const Tuple& t : rows){
        if(t.GetValues().size() > 0 || t.GetValues().size() == 0){
            relation.AddTuple(t.GetValues());
        }
    }
    return relation;

}

void Relation::Rename(int i, std::string attribute){
    header.GetAttributes().at(i) = attribute;
}

Header Relation::CombineHeaders(std::vector<std::string>firstHeader, std::vector<std::string>secondHeader){
    std::vector<std::string> combinedHeaders = firstHeader;
    //Stores all the matching column names
    for(unsigned int i = 0; i < firstHeader.size(); i++){
        for(unsigned int j = 0; j < secondHeader.size(); j++) {
            if (firstHeader.at(i) == secondHeader.at(j)) {
                matchedColumns.insert(std::pair<int, int>(j, i));
            }
        }
    }
    //add new headers from secondHeader to fistHeader
    for(unsigned int i = 0; i < secondHeader.size(); i++){
        std::map<int,int>::iterator it = matchedColumns.find(i);
        if(it == matchedColumns.end()){
            combinedHeaders.push_back(secondHeader.at(i));
        }
    }

    Header combinedHeader = Header(combinedHeaders);
    return combinedHeader;
//1) Make a vector of strings and put everything from h1
//2) make two nested for loops (Outside is h2 and inside h1)
//3)loop through each header and try to find out where they are overlapping
//4)if they match, push back j and i to the map (pay attention to j and i order)
// 5) bool add = false (inbtwn of nested loop)
//6) if they don't match add = true
//7) after the inner loop ) if add then vector of strings.push back h2.at(i);
//may need to adjust combinetuples and isjoinable functions
}

bool Relation::isJoinable(const Tuple& firstTuple, const Tuple& secondTuple){
    if(!matchedColumns.empty()){
        for(std::map<int, int>::iterator it = matchedColumns.begin();
            it != matchedColumns.end(); it++){
            if(secondTuple.GetValues().at(it->first) != firstTuple.GetValues().at(it->second))
                return false;
        }
    }
    return true;
}

Tuple Relation::CombineTuples(const Tuple& firstTuple, const Tuple& secondTuple){
    std::vector<std::string> combinedTuples = firstTuple.GetValues();
    std::vector<std::string> secondTupleValues = secondTuple.GetValues();

    for(unsigned int i = 0; i < secondTupleValues.size(); i++){
        std::map<int, int>::iterator it = matchedColumns.find(i);
        if(it == matchedColumns.end()){
            combinedTuples.push_back(secondTupleValues.at(i));
        }
    }

    Tuple combinedTuple = Tuple(combinedTuples);

    return combinedTuple;
}

Relation Relation::Join(Relation& toJoin){
    Header firstHeader = Header(GetHeader());
    Header secondHeader = toJoin.GetHeader();

    Header combinedHeader = CombineHeaders(firstHeader.GetAttributes(), secondHeader.GetAttributes());

    //make a new empty relation using combined header
    Relation relation = Relation("empty", combinedHeader);
    //Go through every pair of tuples
    //a) See if you can combine the tuples. Does every column that is supposed to match actually match?
    //b) If the tuples can be combined, then combine them
    for (const Tuple& t1 : rows){
        for (const Tuple& t2 : toJoin.GetRows()){
            if(isJoinable(t1, t2)){
                relation.AddTuple(CombineTuples(t1, t2));
            }
        }
    }

    return relation;
}

Relation Relation::Union(Relation& givenRelation){
    for(std::set<Tuple>::iterator it = givenRelation.GetRows().begin(); it != givenRelation.GetRows().end(); it++){
        int firstSize = GetRowsSize();
        AddTuple(*it);
        Tuple tuple = *it;

        if(GetRowsSize() != firstSize){
            std::cout << " ";
            for(unsigned int i = 0; i < header.GetAttributes().size(); i++){
                    std::cout << header.GetAttributes().at(i) << "=" << tuple.GetValues().at(i);
                    if((std::size_t)i < header.GetAttributes().size() - 1){
                        std::cout << ", ";
                    }
            }
            std::cout << std::endl;
        }
    }
    return *this;
}


