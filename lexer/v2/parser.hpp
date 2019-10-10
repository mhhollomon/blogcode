#if !defined(LEXER_PARSER_H_)
#define LEXER_PARSER_H_

//****************************************
// Copyright 2018 - Mark Hollomon
//
// Attempt to use a lexer with Boost.Spirit X3
// Main
//****************************************

#include <boost/spirit/home/x3.hpp>

#include "lexer.hpp"

namespace x3 = boost::spirit::x3;

struct tok_sym: x3::parser<tok_sym> {
    
    using attribute_type = std::string;
    
    tok_sym(TokenType t = tokNil) : m_tt{t} {};
    
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
    return (tok_sym(left) >> right);
}
  
template<typename T>
auto operator>>(T left, TokenType right)
{
    return (left >> tok_sym(right));
}


struct tok_kw: x3::parser<tok_kw> {
    
    using attribute_type = x3::unused_type;
    
    tok_kw(TokenType t = tokNil) : m_tt{t} {};
    
    template<typename Iterator, typename Context, typename RContext, typename Attribute>
    bool parse(Iterator &first, Iterator const& last, Context const& context, 
               RContext const& rcontext, Attribute& attr) const
    {
        
        if ((*first).istype(m_tt)) {
            ++first;
            return true;
        }
        
        return false;
    }
    
private:
    TokenType m_tt;
};



#endif
