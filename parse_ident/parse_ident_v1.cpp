#include <iostream>
#include <string>

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/home/x3.hpp>

//****************************
// The parser
//****************************
namespace x3 = boost::spirit::x3;

using x3::lexeme;
using x3::alnum;

auto const kw_var = x3::lit("var");

auto const ident = lexeme[ +alnum ];

auto const stmt = kw_var >> ident;

auto const program = +stmt;

//****************************
// Main
//****************************
int main(int argc, char**argv)
{
    if (argc < 2) {
        std::cout << "Need something to parse\n";
        exit(1);
    }

    std::string input(argv[1]);

    auto iter     = input.cbegin();
    auto end_iter = input.cend();

    std::cout << "parsing : " << input << "\n";
    bool r = x3::phrase_parse(iter, end_iter, program, x3::ascii::space);

    if (iter != end_iter) {
        auto distance = end_iter - iter;
        std::cout << "Failed: didn't parse everything\n";
        std::cout << "stopped " << distance << " characters from the end "
                  << "( '" << *iter << "' )\n";
        return 1;
    } else if (r) {
        std::cout << "Good input\n";
        return 0;
    } else {
        std::cout << "Parse failed\n";
        return 1;
    }
}