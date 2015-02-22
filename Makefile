SOURCES := main.c json.c out/json.l.c out/json.y.c
OBJECTS := $(patsubst %.c,out/%.c.o,$(SOURCES))

all: json

clean:
	rm -rf obj json json.dSYM

json: $(OBJECTS) Makefile
	@mkdir -p $(@D)
	cc -g -o $@ $(OBJECTS)

out/json.l.c out/json.l.h: json.l out/json.y.h Makefile
	@mkdir -p $(@D)
	flex --outfile=out/json.l.c --header-file=out/json.l.h --prefix=jp --yylineno $<

out/json.y.c out/json.y.h: json.y Makefile
	@mkdir -p $(@D)
	bison --output-file=out/json.y.c --name-prefix=jp -d $<

out/main.c.o: out/json.l.h out/json.y.h

out/%.c.o: %.c Makefile
	@mkdir -p $(@D)
	cc -I. -Iout -Weverything -g -O0 -MMD -MF $(@:.o=.d) -MP -MT '$@ $(@:.o=.d)' -c $< -o $@

ifneq ($(MAKECMDGOALS),clean)
-include $(OBJECTS:.o=.d)
endif
