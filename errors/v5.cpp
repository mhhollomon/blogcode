#include <iostream>
#include <string>

#include <boost/config/warning_disable.hpp>
#include <boost/spirit/home/x3.hpp>

//****************************
// The parser
//****************************
namespace x3 = boost::spirit::x3;

// tag for the counter
struct error_counter_tag;
// counter functor
template <typename Iterator>
struct error_counter {
    int error_count =0;
    void operator()(Iterator const& first, Iterator const& last) {
        error_count += 1;
    }
};

template <typename Iterator, typename Exception, typename Context>
struct error_reporter {
   x3::error_handler_result operator() (
      Iterator const& first, Iterator const& last, Exception const& x,
      Context const& context) {

      std::cout << "ERROR! : " << x.what() << "\n";
      std::string message = "Error! Expecting: " + x.which() + " here:";
      std::cout << message << "\n";

      auto curr = first;
      auto iter = x.where();

      int prefix_size = 0;
      while ( curr != iter ) {
         std::cout << *curr;
         ++prefix_size;
         ++curr;
      }

      int char_count = 0;
      for (;char_count < 10; ++char_count) {
         if (iter == last) break;
         std::cout << *iter;
         ++iter;
      }
      std::cout << "\n";
      for (; prefix_size > 0; --prefix_size) {
         std::cout << '-';
      }

      std::cout << "^";
      for (; char_count > 1; --char_count){
         std::cout << '-';
      }
      std::cout << "\n";

      return x3::error_handler_result::fail;


   }
};

struct stmt_tag {

template <typename Iterator, typename Exception, typename Context>
   x3::error_handler_result on_error(
      Iterator& first, Iterator const& last, Exception const& x,
      Context const& context)
   {
      error_reporter<Iterator, Exception, Context> er;

      er(first, last, x ,context);

      auto& counter = x3::get<error_counter_tag>(context).get();

      counter(first, last);

      first = x.where();
      return x3::error_handler_result::accept;
    }

};


using x3::lexeme;
using x3::alnum;
using x3::alpha;
using x3::char_;

x3::symbols<int> symtab;

auto mkkw = [](std::string kw) { 
   symtab.add(kw);
   return lexeme[x3::lit(kw) >> !alnum]; 
   };

auto const kw_var = mkkw("var");
auto const kw_func = mkkw("func");

auto const ualnum = alnum | char_('_');
auto const reserved = lexeme[symtab >> !ualnum];
auto const ident = lexeme[ *char_('_') >> alpha >> *ualnum ] - reserved;

auto const vardec = kw_var > ident > ';' ;
auto const funcdec = kw_func > ident > ';' ;

x3::rule<stmt_tag> const stmt = "stmt";

auto const stmt_def = vardec | funcdec ;

auto const program = +stmt;

BOOST_SPIRIT_DEFINE(stmt);


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

   using boost::spirit::x3::with;
   auto errcnt   = error_counter<decltype(iter)>();
   auto const parser = with<error_counter_tag>(std::ref(errcnt))
       [ program ];
   bool r = x3::phrase_parse(iter, end_iter, parser, x3::ascii::space);

   if (errcnt.error_count > 0) {
       std::cout << "Failed:" << errcnt.error_count << " errors occured\n";
       return 1;
   } else if (iter != end_iter) {
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
