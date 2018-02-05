//
// Created by 14667 on 2018/2/3.
//

#ifndef PROGRAMMABLECALCULATOR_SCANNER_H
#define PROGRAMMABLECALCULATOR_SCANNER_H

#if !defined(yyFlexLexerOnce)

#include <FlexLexer.h>

#endif

#include "location.hh"
#include "parser.tab.hh"

#include <istream>

namespace gss {

class Scanner : public yyFlexLexer {
  public:
    Scanner(std::istream *in) : yyFlexLexer(in) {}

    // get rid of override virtual function warning
    using FlexLexer::yylex;

    virtual int yylex(Parser::semantic_type *const lval, Parser::location_type *location);
    // YY_DECL defined in mc_lexer.l
    // Method body created by flex in mc_lexer.yy.cc

  private:
    /* yyval ptr */
    Parser::semantic_type *yylval = nullptr;
};

} /* end namespace gss */

#endif // PROGRAMMABLECALCULATOR_SCANNER_H
