#include "Lexer.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Parser.h"
#include "Interpreter.h"

int main(int argc, char** argv) {
    Parser* parser = new Parser();
    Lexer* lexer = new Lexer();
    std::ifstream inputFile (argv[1]);
    std::string input;
    DatalogProgram datalog;

    if (!inputFile.is_open()) {
        std::cout << "File could not be found or opened." << std::endl;
        return 1;
    }

    while(inputFile.peek() != EOF){
        input += inputFile.get();
    }

    lexer->Run(input);

    try{
        datalog = parser->ParseDatalogProgram(lexer->GetTokens());
    }
    catch(std::string error){
        std::cout << error << std::endl;
    }

    Interpreter interpreter(datalog);
    delete lexer;

    return 0;
}