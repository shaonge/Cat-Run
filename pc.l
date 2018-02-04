%{
/* Implementation of yyFlexScanner */
#include "scanner.h"

#undef  YY_DECL
#define YY_DECL int gss::Scanner::yylex(gss::Parser::semantic_type * const lval, gss::Parser::location_type *loc)

/* typedef to make the returns for the tokens shorter */
using token = gss::Parser::token;

/* define yyterminate as this instead of NULL */
#define yyterminate() return token::END

/* msvc2010 requires that we exclude this header file. */
#define YY_NO_UNISTD_H

/* update location on matching */
#define YY_USER_ACTION loc->step(); loc->columns(yyleng);
%}

%option debug
%option nodefault
%option yyclass="gss::Scanner"
%option noyywrap
%option c++

EXP ([Ee][+-]?(0|[1-9][0-9]*))

%%

%{          /** Code executed at the beginning of yylex **/
            yylval = lval;
%}

"+" |
"-" |
"*" |
"/" |
"=" |
"|" |
"," |
":" |
";" |
"(" |
")"     { return yytext[0]; }

">"  |
"<"  |
"<>" |
"==" |
">=" |
"<="    { yylval->build<std::string>(yytext); return token::CMP; }

"if"    { return token::IF; }
"then"  { return token::THEN; }
"else"  { return token::ELSE; }
"while" { return token::WHILE; }
"do"    { return token::DO; }
"def"   { return token::DEF; }

[a-zA-Z][a-zA-Z0-9]* {
                       yylval->build<std::string>(yytext);
                       return token::IDENTIFIER;
                     }

(0|[1-9][0-9]*)("."[0-9]+)?{EXP}? {
                                    yylval->build<double>(stod(std::string(yytext)));
                                    return token::CONSTANT;
                                  }

"//".*

[ \t]

"\n" { return token::EOL; }

<<EOF>> { return token::END; }

.

%%
