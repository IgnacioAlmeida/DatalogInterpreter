cmake_minimum_required(VERSION 3.10.2)
project(project-1)

set(CMAKE_CXX_STANDARD 14)


include_directories(.)

add_executable(project-1
        Automaton.h
        ColonAutomaton.cpp
        ColonAutomaton.h
        ColonDashAutomaton.cpp
        ColonDashAutomaton.h
        Lexer.cpp
        Lexer.h
        Token.cpp
        Token.h
        main.cpp
        MatcherAutomaton.cpp
        MatcherAutomaton.h
        StringAutomata.cpp
        StringAutomata.h
        IDAutomata.cpp
        IDAutomata.h
        CommentAutomata.cpp
        CommentAutomata.h
        Parser.cpp
        Parser.h
        DatalogProgram.cpp
        DatalogProgram.h
        Predicate.cpp
        Predicate.h
        Rule.cpp
        Rule.h
        Parameter.cpp
        Parameter.h
        Tuple.cpp
        Tuple.h
        Header.cpp
        Header.h
        Relation.cpp
        Relation.h
        Database.cpp
        Database.h
        Interpreter.cpp
        Interpreter.h Graph.cpp Graph.h)
