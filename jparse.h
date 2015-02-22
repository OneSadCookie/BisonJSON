#ifndef jparse_h
#define jparse_h

#include "json.h"

struct YYLTYPE;

typedef struct JP_Parse_Context
{
	void *scanner;
	JSON *out_json;
}
JP_Parse_Context;
#define JP_SCANNER ctx->scanner

void jperror(struct YYLTYPE *yylloc, JP_Parse_Context *ctx, char const *s);

#endif
