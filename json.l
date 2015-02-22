%{
	#include "json.h"
	#include "json.y.h"

	char *j_escape(char *text)
	{
		// TODO FIXME :P
		return strdup(text);
	}
%}

%option bison-bridge
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
\[      { return LBRACKET; }
\]      { return RBRACKET; }
\{      { return LBRACE;   }
\}      { return RBRACE;   }
:       { return COLON;    }
,       { return COMMA;    }
"true"  { return TRUE_;    }
"false" { return FALSE_;   }
"null"  { return NULL_;    }
