//****************************************
// Copyright 2018 - Mark Hollomon
//
// Attempt to use a lexer with Boost.Spirit X3
// Main
//****************************************

#include <iostream>

#include "lexer.hpp"

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cout << "Need something to parse\n";
        return 1;
    }

    std::string input(argv[1]);
    auto ibeg = input.begin();
    auto iend = input.end();
    
    std::cout << "Parsing : " << input << "\n";
    lexer lex(ibeg, iend);
    
    auto iter = lex.begin();
    auto theEnd = lex.end();
    
    
    int count = 0;
    while (iter != theEnd) {
        auto t = *iter;
        std::cout << t.lexeme << " (" << t.start_iter - ibeg << ", " << t.end_iter - ibeg << ")\n";
        ++iter;
        ++count;
        if (count > 10) {
            std::cout << "Exceeded loop count\n";
            return 1;
        }
    }
    
    return 0;
}
