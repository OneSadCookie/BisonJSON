%{
    #include "json.h"
    #include "json.y.h"

    char *j_escape(char *text)
    {
        // TODO FIXME actually escape
        char *buf = strdup(text + 1);
        buf[strlen(text) - 2] = 0;
        return buf;
    }

    // this magic is C&P from SO
    #define YY_USER_ACTION \
        yylloc->first_line = yylloc->last_line; \
        yylloc->first_column = yylloc->last_column; \
        for(int i = 0; yytext[i] != '\0'; i++) { \
            if(yytext[i] == '\n') { \
                yylloc->last_line++; \
                yylloc->last_column = 0; \
            } \
            else { \
                yylloc->last_column++; \
            } \
        }
%}

%option bison-bridge
%option bison-locations
%option noyywrap
%option reentrant
%option yylineno

%%

[-]?(0|[1-9][0-9]*)(\.[0-9]+)?([eE][+-]?[0-9]+)? {
    yylval->number = atof(yytext);
    return NUMBER;
}
\"([^\\"]|\\(["\\/bfnrt]|u[0-9a-fA-F]{4}))*\" {
    yylval->string = j_escape(yytext);
    return STRING;
}
"["     { return LBRACKET; }
"]"     { return RBRACKET; }
"{"     { return LBRACE;   }
"}"     { return RBRACE;   }
":"     { return COLON;    }
","     { return COMMA;    }
"true"  { return TRUE_;    }
"false" { return FALSE_;   }
"null"  { return NULL_;    }

[ \t\r\n] /* ignore whitespace */
