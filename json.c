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
    // TODO FIXME check it's not there, first
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
    // TODO FIXME oh god that asymptotic behavior
    memcpy(elements + 1, j->guts.array.elements, j->guts.array.count++ * sizeof(JSON *));
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
    switch (json->type)
    {
    case J_OBJECT:
        {
            fprintf(file, "{");
            for (size_t i = 0; i < json->guts.object.count; ++i)
            {
                if (i != 0) fprintf(file, ",");
                // TODO re-escape the string (fine since we didn't unescape in the first place!)
                fprintf(file, "\"%s\":", json->guts.object.members[i].key);
                j_write_to_file(file, json->guts.object.members[i].value);
            }
            fprintf(file, "}");
        }
        break;
    case J_ARRAY:
        {
            fprintf(file, "[");
            for (size_t i = 0; i < json->guts.array.count; ++i)
            {
                if (i != 0) fprintf(file, ",");
                j_write_to_file(file, json->guts.array.elements[i]);
            }
            fprintf(file, "]");
        }
        break;
    case J_STRING:
        {
            // TODO re-escape the string (fine since we didn't unescape in the first place!)
            fprintf(file, "\"%s\"", json->guts.string);
        }
        break;
    case J_NUMBER:
        {
            fprintf(file, "%f", json->guts.number);
        }
        break;
    case J_BOOLEAN:
        {
            fprintf(file, "%s", json->guts.boolean ? "true" : "false");
        }
        break;
    case J_NULL:
        {
            fprintf(file, "null");
        }
        break;
    }
}
