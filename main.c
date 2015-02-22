#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "jparse.h"
#include "json.y.h"
#include "json.l.h"

void jperror(struct YYLTYPE *yylloc, JP_Parse_Context *ctx, char const *s)
{
	fprintf(stderr, "%d:%d-%d:%d: error: %s\n", yylloc->first_line, yylloc->first_column, yylloc->last_line, yylloc->last_column, s);
}
// no way to get bison to provide a prototype?
extern void jpparse(yyscan_t scanner);

int main(int argc, char **argv)
{
	assert(argc >= 2);
	FILE *infile = fopen(argv[1], "rb");
	assert(infile);
	fseek(infile, SEEK_END, 0);
	size_t size = (size_t)ftell(infile);
	void *text = malloc(size);
	fseek(infile, SEEK_SET, 0);
	size_t read = fread(text, 1, size, infile);
	assert(read == size);

	JP_Parse_Context ctx;
	jplex_init(&ctx.scanner);
	YY_BUFFER_STATE buffer = jp_scan_bytes(text, size, ctx.scanner);
	jpparse(&ctx);
	jp_delete_buffer(buffer, ctx.scanner);

	return 0;
}
