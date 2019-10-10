#if !defined(LEXER_PARSER_H_)
#define LEXER_PARSER_H_

//****************************************
// Copyright 2018 - Mark Hollomon
//
// Attempt to use a lexer with Boost.Spirit X3
// Parser  Version 1
//****************************************

#include <boost/spirit/home/x3.hpp>

#include "lexer.hpp"

namespace x3 = boost::spirit::x3;

struct tok: x3::parser<tok> {
    
    using attribute_type = std::string;
    
    tok(TokenType t = tokNil) : m_tt{t} {};
    
    template<typename Iterator, typename Context, typename RContext, typename Attribute>
    bool parse(Iterator &first, Iterator const& last, Context const& context, 
               RContext const& rcontext, Attribute& attr) const
    {
        
        if ((*first).istype(m_tt)) {
            attr = (*first).lexeme;
            ++first;
            return true;
        }
        
        return false;
    }
    
private:
    TokenType m_tt;
};

template<typename T>
auto operator>>(TokenType left, T right)
{
    return (tok(left) >> right);
}
  
template<typename T>
auto operator>>(T left, TokenType right)
{
    return (left >> tok(right));
}


#endif
