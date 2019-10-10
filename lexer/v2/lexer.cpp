//***********************************
//* Copyright 2108 Mark Hollomon
//*
//***********************************

#include <cctype>
#include <iostream>

#include "lexer.hpp"

// I got tired of typing
using iit = input_iterator_type;

// forward declaration
token get_next_token(iit &iter, iit &end);

//*****************************
//* LEXER CLASS
//*****************************

lexer::lexer(const iit &start, const iit&end) : m_start(start), m_end(end) {
}


//******************************
//* ITERATOR
//******************************

lexer::iterator::iterator(iit &start, iit &end): 
    m_end(end)
{
    m_curr_tok = get_next_token(start, end);
}


lexer::iterator::iterator(iit &end) { 
    m_curr_tok.toktype = tokEOF;
    m_curr_tok.start_iter = end;
    m_curr_tok.end_iter = end;
    m_curr_tok.lexeme = "";
}


lexer::iterator::reference lexer::iterator::operator*() { 
    return m_curr_tok; 
}

lexer::iterator::pointer lexer::iterator::operator->() { 
    return &m_curr_tok; 
}

lexer::iterator lexer::iterator::operator++() {
    m_curr_tok = get_next_token(m_curr_tok.end_iter, m_end); 
    return *this; 
}


lexer::iterator lexer::iterator::operator++(int junk) { 
    self_type t = *this; ++(*this); return t;
}


//****************************
//* GET_NEXT_TOKEN
//****************************


// returns true if there is more input.
// returns false if it reaches the end of the input.
bool skip_space(iit &iter, iit &ender) {
    while (iter != ender) {
        if (! std::isspace(*iter)) break;
        ++iter;
    }
    if (iter == ender) return false;
    
    return true;
}


token get_next_token(iit &iter, iit &end) {
    token retval;
    
    if (! skip_space(iter, end)) {
        return token::mkend(end);
    }
    
    // skip_space guarantees we are not at the end of 
    // input but are at a non-space character.
    
    retval.start_iter = iter;
    retval.lexeme = "";
    
    // check punctuation first
    switch (*iter) {
        case ';' : retval.toktype = tokSemi; break;
        case '(' : retval.toktype = tokOpenParen; break;
        case ')' : retval.toktype = tokCloseParen; break;
    };
    
    if (retval.toktype != tokNil) {
        retval.lexeme = *iter;
        retval.end_iter = ++iter;
        return retval;
    }
    
    while (iter != end) {
        if (std::isalnum(*iter))
            retval.lexeme += *iter;
        else if (*iter == '_')
            retval.lexeme += '_';
        else
            break;
        
        ++iter;
    }
    
    if (iter == retval.start_iter) {
        // we didn't consume any input. (Except maybe spaces).
        // So just signal the end. Otherwise any outer loop
        // will spin forever.
        return token::mkend(end);
    }
    
    if (retval.lexeme == "var" )
        retval.toktype = tokVar;
    else if (retval.lexeme == "func" )
        retval.toktype = tokFunc;
    else
        retval.toktype = tokIdent;
        
    retval.end_iter = iter;

    
    return retval;
}

