#include <iostream>
#include <string>
#include <cctype>

#include <boost/spirit/home/x3.hpp>

namespace x3 = boost::spirit::x3;


//****************************
// Custom parser
//****************************

struct keyword: x3::parser<keyword> {
    
    using attribute_type = std::string;
    
    keyword(std::string s) : m_kw(s) {};
    
    template<typename Iterator, typename Context, typename RContext, typename Attribute>
    bool parse(Iterator &first, Iterator const& last, Context const& context, 
               RContext const&rcontext, Attribute& attr) const
    {
        Iterator save = first;
        
        auto kbeg = m_kw.begin();
        auto const kend = m_kw.end();
        
        while ((first != last) & (kbeg != kend)) {
            if (*first != *kbeg) break;
            ++first; ++ kbeg;
        }
        
        if (kbeg == kend) {
            attr = m_kw;
            return true;
        } else {
            first = save;
            return false;
        }

        
    }
    
    std::string m_kw;
};

template<>
struct x3::get_info<keyword>
{
    typedef std::string result_type;
    std::string operator()( keyword const& kw) const
    {
        return "keyword " + kw.m_kw;
    }
};

//****************************
// The gramar
//****************************

using x3::lexeme;
using x3::alnum;
using x3::alpha;
using x3::ascii::char_;

x3::symbols<int> symtab;

auto const ualnum = alnum | char_('_');

auto mkkw = [](std::string kw) { 
        symtab.add(kw);
        return keyword(kw); 
        };


auto const kw_var = mkkw("var");
auto const kw_func = mkkw("func");

auto const reserved = lexeme[symtab >> !ualnum];

auto const ident = lexeme[ *char_('_') >> alpha >> *ualnum ] - reserved;

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
