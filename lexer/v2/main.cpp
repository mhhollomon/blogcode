//****************************************
// Copyright 2018 - Mark Hollomon
//
// Attempt to use a lexer with Boost.Spirit X3
// Main
//****************************************

#include <iostream>

#include "lexer.hpp"
#include "parser.hpp"

auto vardef = tok_kw(tokVar) >> tokIdent >> tok_kw(tokSemi) ;
auto funcdef = tok_kw(tokFunc) >> tokIdent >> 
    tok_kw(tokOpenParen) >> tok_kw(tokCloseParen) >> tok_kw(tokSemi);
auto statement = vardef | funcdef;
auto program = +statement;

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

    std::vector<std::string> attr;
    
    
    bool r = x3::parse(iter, theEnd, program, attr);
    if (r) {
        if (iter != theEnd) {
            std::cout << "FAILED: didn't parse all the output\n";
            return 1;
        } else {
            std::cout << "SUCCESS: Good Input\n";
            for (auto const&a : attr) {
                std::cout << a << "\n";
            }
            return 0;
        }
    } else {
        std::cout << "FAILED: returned failure\n";
        return 1;
    }

}
