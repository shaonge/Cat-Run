%skeleton "lalr1.cc"
%require "3.0"
%debug
%defines
%define api.namespace {ssg}
%define parser_class_name {Parser}

%code requires {
   #include <memory>
   #include <list>

   namespace ssg {
      class ASTNode;
      class Scanner;
      class Context;
      
      using ASTNodePtrList = std::list<std::shared_ptr<ASTNode>>;
   }

// The following definitions is missing when %locations isn't used
# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif
}

%parse-param {Scanner &scanner}
%parse-param {Context &context}

%code {
   /* include for all driver functions */
   #include "ast.h"
   #include "context.h"
   #include "scanner.h"

#undef yylex
#define yylex scanner.yylex
}

%define api.value.type variant
%define parse.assert

%token <std::string> IDENTIFIER CMP
%token <double> CONSTANT
%token IF ELSE WHILE DEF
%token END

%type <double> run_unit
%type <std::shared_ptr<ASTNode>> stmt expr
%type <std::list<std::string>> identifier_list parameter_list
%type <ASTNodePtrList> stmt_list stmt_block expr_list argument_list

%locations

%nonassoc CMP
%right '='
%left '+' '-'
%left '*' '/'
%nonassoc '|' UMINUS

%%

run_unit:													{ $$ = 0; }
		| run_unit stmt                                     { $$ = $2->eval(&context); }
		| run_unit DEF IDENTIFIER '(' parameter_list ')'    { context.current_symtab->function_define($3, $5, new SymbolTable(), ASTNodePtrList()); }
		  stmt_block                                        { auto f = context.current_symtab->lookup($3); (*f)->fbody = $8; }
		| run_unit END										{ printf("%4.4f\n", $1); return 0; }
		| run_unit error									{ exit(EXIT_FAILURE); }
		;

stmt: IF expr stmt_block                        { $$ = std::make_shared<ControlFlow>(ControlFlowType::IF_THEN, $2, $3, ASTNodePtrList()); }
    | IF expr stmt_block ELSE stmt_block        { $$ = std::make_shared<ControlFlow>(ControlFlowType::IF_THEN_ELSE, $2, $3, $5); }
    | WHILE expr stmt_block                     { $$ = std::make_shared<ControlFlow>(ControlFlowType::WHILE_DO, $2, $3, ASTNodePtrList()); }
    | expr ';'                                  { $$ = $1; }
    ;

stmt_block: '{' stmt_list '}'   				{ $$ = std::move($2); }

stmt_list:                  					{ $$.clear(); }
         | stmt stmt_list   					{ $$ = std::move($2); $$.push_front($1); }
         ;

expr: expr '+' expr                  { $$ = std::make_shared<Expression>(ExpressionType::BOP_ADD, $1, $3); }
    | expr '-' expr                  { $$ = std::make_shared<Expression>(ExpressionType::BOP_SUB, $1, $3); }
    | expr '*' expr                  { $$ = std::make_shared<Expression>(ExpressionType::BOP_MUL, $1, $3); }
    | expr '/' expr                  { $$ = std::make_shared<Expression>(ExpressionType::BOP_DIV, $1, $3); }
    | expr CMP expr                  {
                                        if ($2 == "<") {
                                            $$ = std::make_shared<Expression>(ExpressionType::BOP_LT, $1, $3);
                                        } else if ($2 == "<=") {
                                            $$ = std::make_shared<Expression>(ExpressionType::BOP_LE, $1, $3);
                                        } else if ($2 == ">") {
                                            $$ = std::make_shared<Expression>(ExpressionType::BOP_GT, $1, $3);
                                        } else if ($2 == ">=") {
                                            $$ = std::make_shared<Expression>(ExpressionType::BOP_GE, $1, $3);
                                        } else if ($2 == "<>") {
                                            $$ = std::make_shared<Expression>(ExpressionType::BOP_NE, $1, $3);
                                        } else if ($2 == "==") {
                                            $$ = std::make_shared<Expression>(ExpressionType::BOP_EQ, $1, $3);
                                        } else {
                                        }
                                     }
    | IDENTIFIER '=' expr            {
                                        $$ = std::make_shared<Expression>(ExpressionType::BOP_ASSIGN, std::make_shared<SymbolReference>($1), $3);
                                     }
    | '|' expr                           { $$ = std::make_shared<Expression>(ExpressionType::UOP_ABS, $2, nullptr); }
    | '-' %prec UMINUS expr              { $$ = std::make_shared<Expression>(ExpressionType::UOP_MINUS, $2, nullptr); }
    | '(' expr ')'                       { $$ = $2; }
    | CONSTANT                           { $$ = std::make_shared<Constant>($1); }
    | IDENTIFIER                         { $$ = std::make_shared<SymbolReference>($1); }
    | IDENTIFIER '(' argument_list ')'   { $$ = std::make_shared<FunctionCall>($1, $3); }
    ;
 
parameter_list:                  		{ $$.clear(); }
			 | identifier_list   		{ $$ = std::move($1); } 
 
argument_list:                  		{ $$.clear(); }
			 | expr_list        		{ $$ = std::move($1); }

expr_list: expr                 		{ $$.clear(); $$.push_front($1); }
         | expr ',' expr_list   		{ $$ = std::move($3); $$.push_front($1); }
         ;

identifier_list: IDENTIFIER                       { $$.clear(); $$.push_front($1); }
               | IDENTIFIER ',' identifier_list   { $$ = std::move($3); $$.push_front($1); }
               ;

%%

void ssg::Parser::error(const location_type &l, const std::string &err_message)
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}
