//
// Created by Ignacio R. de Almeida on 5/22/21.
//

#ifndef PROJECT_1_HEADER_H
#define PROJECT_1_HEADER_H
#include <vector>
#include <string>

class Header {
private:
    std::vector<std::string> parameters;
public:
    Header(std::vector<std::string> parameters){this->parameters = parameters;}
    Header(){}
    std::vector<std::string>& GetAttributes(){return parameters;}
    std::string ToString();

};


#endif //PROJECT_1_HEADER_H
