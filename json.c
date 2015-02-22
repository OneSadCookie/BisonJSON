#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "json.h"

JSON *j_new_object(void)
{
	JSON *j = malloc(sizeof(JSON));
	j->type = J_OBJECT;
	j->guts.object.count = 0;
	j->guts.object.members = NULL;
	return j;
}

void j_object_add(JSON *j, J_Pair member)
{
	assert(j->type == J_OBJECT);
	j->guts.object.members = realloc(j->guts.object.members, (j->guts.object.count + 1) * sizeof(J_Pair));
	j->guts.object.members[j->guts.object.count++] = member;
}

JSON *j_new_array(void)
{
	JSON *j = malloc(sizeof(JSON));
	j->type = J_ARRAY;
	j->guts.array.count = 0;
	j->guts.array.elements = NULL;
	return j;
}

void j_array_prepend(JSON *j, JSON *value)
{
	assert(j->type == J_ARRAY);
	JSON **elements = malloc((j->guts.array.count + 1) * sizeof(JSON *));
	memcpy(elements + 1, j->guts.array.elements, j->guts.array.count * sizeof(JSON *));
	elements[0] = value;
	free(j->guts.array.elements);
	j->guts.array.elements = elements;
}

JSON *j_new_string(char *string)
{
	JSON *j = malloc(sizeof(JSON));
	j->type = J_STRING;
	j->guts.string = string;
	return j;
}

JSON *j_new_number(double number)
{
	JSON *j = malloc(sizeof(JSON));
	j->type = J_NUMBER;
	j->guts.number = number;
	return j;
}

JSON *j_new_boolean(bool b)
{
	JSON *j = malloc(sizeof(JSON));
	j->type = J_BOOLEAN;
	j->guts.boolean = b;
	return j;
}

JSON *j_new_null(void)
{
	JSON *j = malloc(sizeof(JSON));
	j->type = J_NULL;
	return j;
}

void j_write_to_file(FILE *file, JSON *json)
{
	abort();
}
