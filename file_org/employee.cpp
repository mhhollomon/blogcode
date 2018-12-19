/*=============================================================================
    Copyright (c) 2001-2018 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include <boost/config/warning_disable.hpp>
#include <boost/spirit/home/x3.hpp>

#include "ast.hpp"
#include "employee.hpp"

namespace client { 
	namespace parser {

        ///////////////////////////////////////////////////////////////////////////////
        //  Our employee parser definition
        ///////////////////////////////////////////////////////////////////////////////
        namespace x3 = boost::spirit::x3;
        namespace ascii = boost::spirit::x3::ascii;

        using x3::int_;
        using x3::lit;
        using x3::double_;
        using x3::lexeme;
        using ascii::char_;

        x3::rule<class employee, ast::employee> const employee = "employee";

        auto const quoted_string = lexeme['"' >> +(char_ - '"') >> '"'];

        auto const employee_def =
            lit("employee")
            >> '{'
            >>  int_ >> ','
            >>  quoted_string >> ','
            >>  quoted_string >> ','
            >>  double_
            >>  '}'
            ;

        BOOST_SPIRIT_DEFINE(employee);
        using employee_type = x3::rule<class employee, ast::employee>;
        using context_type = x3::phrase_parse_context<x3::ascii::space_type>::type;
		BOOST_SPIRIT_INSTANTIATE(employee_type, iterator_type, context_type);
	}

    namespace x3 = boost::spirit::x3;

	std::pair<bool, ast::employee>do_parse(parser::iterator_type &first, parser::iterator_type const &last) {
        ast::employee e;

        bool r = phrase_parse(first, last, parser::employee_type(), x3::ascii::space, e);

        return std::make_pair(r, e);
    }
}
