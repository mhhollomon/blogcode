/*=============================================================================
    Copyright (c) 2002-2018 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_X3_MINIMAL_EMPLOYEE_HPP)
#define BOOST_SPIRIT_X3_MINIMAL_EMPLOYEE_HPP

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/home/x3.hpp>

#include "ast.hpp"

namespace client
{
    ///////////////////////////////////////////////////////////////////////////////
    //  Our employee parser declaration
    ///////////////////////////////////////////////////////////////////////////////
    namespace parser
    {
        namespace x3 = boost::spirit::x3;

        using iterator_type = std::string::const_iterator;
    }

    std::pair<bool, ast::employee>do_parse(parser::iterator_type &first, parser::iterator_type const &last);
}

#endif
