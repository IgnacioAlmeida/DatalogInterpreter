//
// Created by Ignacio R. de Almeida on 5/22/21.
//

#ifndef PROJECT_1_RELATION_H
#define PROJECT_1_RELATION_H
#include <string>
#include <iostream>
#include "Tuple.h"
#include "Header.h"
#include <set>
#include <map>
//• select: parameters are index and value (relation column and value to select)
//• select: parameters are index and index (relation columns to select on same values)
//• project: parameter is list of indices (the columns to keep)
//• rename: parameter is list of attributes (defines the new header)
//The methods select, project, rename all return a new Relation object.
class Relation {
private:
    std::string name;
    Header header;
    std::set<Tuple> rows;
    std::map<int, int> matchedColumns;
public:
    Relation(std::string name, Header header){this->name = name; this->header = header;}
    Relation(){}
    std::set<Tuple>& GetRows(){return rows;}
    int GetRowsSize(){return rows.size();}
    void AddTuple(const Tuple& tuple);
    std::string ToString();
    Header GetHeader(){return header;}
    Header CombineHeaders(std::vector<std::string>firstHeader, std::vector<std::string>secondHeader);
    bool isJoinable(const Tuple& firstTuple, const Tuple& secondTuple);
    Tuple CombineTuples(const Tuple& firstTuple, const Tuple& secondTuple);

    Relation Select(int columnIndex, std::string value);
    Relation Select(int columnIndex, int ColumnIndexB);
    Relation Project(std::vector<int>& indices);
    Relation Rename(std::vector<std::string> attributes);
    void Rename(int i, std::string attribute);
    Relation Join(Relation& toJoin);
    Relation Union(Relation& givenRel);
};


#endif //PROJECT_1_RELATION_H
