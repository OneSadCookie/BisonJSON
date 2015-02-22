%{
    #include "jparse.h"
%}

%pure-parser

%union {
    double  number;
    char   *string;

    JSON   *json;
    J_Pair  pair;
}

%lex-param { void *JP_SCANNER }
%parse-param { JP_Parse_Context *ctx }

%error-verbose
%locations
%start start

%token <number> NUMBER
%token <string> STRING
%token TRUE_ FALSE_ NULL_ LBRACE RBRACE LBRACKET RBRACKET COLON COMMA

%type <json> value object array elements members
%type <pair> pair

%%

start: value { ctx->out_json = $1; }

value: STRING { $$ = j_new_string($1); }
     | NUMBER { $$ = j_new_number($1); }
     | object { $$ = $1; }
     | array  { $$ = $1; }
     | TRUE_  { $$ = j_new_boolean(true); }
     | FALSE_ { $$ = j_new_boolean(false); }
     | NULL_  { $$ = j_new_null(); }
     ;

object: LBRACE RBRACE         { $$ = j_new_object(); }
      | LBRACE members RBRACE { $$ = $2; }
      ;

members: pair               { $$ = j_new_object(); j_object_add($$, $1); }
       | pair COMMA members { $$ = $3;             j_object_add($$, $1); }
       ;

pair: STRING COLON value { $$.key = $1; $$.value = $3; }
    ;

array: LBRACKET RBRACKET          { $$ = j_new_array(); }
     | LBRACKET elements RBRACKET { $$ = $2; }
     ;

elements: value                { $$ = j_new_array(); j_array_prepend($$, $1); }
        | value COMMA elements { $$ = $3;            j_array_prepend($$, $1); }
        ;
