#if !defined(LEXER_HPP_)
#define LEXER_HPP_

//****************************************
// Copyright 2018 - Mark Hollomon
//
// Attempt to use a lexer with Boost.Spirit X3
// Lexer header file
//****************************************

#include <string>
#include <iterator>
#include <memory>

using input_iterator_type = std::string::const_iterator;

enum TokenType {
    tokNil,
    tokFunc,
    tokVar,
    tokIdent,
    tokSemi,
    tokOpenParen,
    tokCloseParen,
    tokEOF
};

struct token {
    token(TokenType tt = tokNil) : toktype(tt) {};
    
    TokenType toktype;
    input_iterator_type start_iter;
    input_iterator_type end_iter;
    std::string lexeme;
    
    bool operator==(const token rhs) const {
        // don't need to check lexeme.
        return (
            (toktype == rhs.toktype) && 
            (start_iter == rhs.start_iter) &&
            (end_iter == rhs.end_iter)
            );
    };
    bool istype(TokenType t) const { return toktype == t; };
    
    static token mkend(input_iterator_type iter) {
        auto e = token(tokEOF);
        e.start_iter = iter;
        e.end_iter = iter;
        return e;
    };
};

class lexer {
public:
    lexer(const input_iterator_type &start, const input_iterator_type &end);
        
    class iterator {
    public:
        using self_type = iterator;
        using value_type = token;
        using reference = value_type &;
        using pointer = value_type *;
        using iterator_category = std::forward_iterator_tag;
        using difference_type = int;
        
        iterator(input_iterator_type &start, input_iterator_type &end);
        iterator(input_iterator_type &end);
        iterator() = default;
        
        self_type operator++();
        self_type operator++(int junk);
        reference operator*();
        pointer operator->();
        bool operator==(const self_type& rhs) const { return m_curr_tok == rhs.m_curr_tok; };
        bool operator!=(const self_type& rhs) const { return !(m_curr_tok == rhs.m_curr_tok); };

    private:
        input_iterator_type m_end;
        token m_curr_tok;
    };
    
    
    iterator begin() { return iterator(m_start, m_end); };
    iterator end() { return iterator(m_end); };
private:
    input_iterator_type m_start;
    input_iterator_type m_end;
};

#endif
