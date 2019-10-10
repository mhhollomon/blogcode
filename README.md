# blogcode
Example code for posts and articles on my blog [Code Vamping](https://www.codevamping.com)

Directory | Post
----------|----
parse_ident   | [Identifier Parsing in Boost::Spirit X3](https://www.codevamping.com/2018/09/identifier-parsing-in-boost-spirit-x3/), [Identifier Parsing - Redux](https://www.codevamping.com/2018/09/identifier-parsing-redux/)
custom_parser | [Identifier Parsing in Boost::Spirit X3 - Custom Parser](https://www.codevamping.com/2018/09/identifier-parsing-in-boost-spirit-x3-custom-parser/)
lexer         | Spirit X3 Separate Lexer - [Part I](https://www.codevamping.com/2018/09/spirit-x3-separate-lexer-part-i/) and [Part II](https://www.codevamping.com/2018/10/spirit-x3-separate-lexer-part-ii/)
errors        | [Spirit X3 Error Handling](https://www.codevamping.com/2018/12/spirit-x3-error-handling/)
file_org      | [Spirit X3 File Organization](https://www.codevamping.com/2018/12/spirit-x3-file-organization/)
identifiers   | [Better Identifiers](https://www.codevamping.com/2019/10/better-identifiers/)


CMake is used to build. If you want ot build everything, go to the to directory
and do..

```
mkdir build
cmake -B build
cmake --build build
```

However, each of the sudirectories are buildable by themselves. So you can also
cd into each individual diretory and run the same set of commands to build just
that directory.
