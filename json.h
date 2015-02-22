#ifndef json_h
#define json_h

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef enum J_Type
{
	J_OBJECT,
	J_ARRAY,
	J_STRING,
	J_NUMBER,
	J_BOOLEAN,
	J_NULL,
}
J_Type;

typedef struct J_Pair
{
	char        *key;
	struct JSON *value;
}
J_Pair;

typedef struct J_Object
{
	size_t  count;
	J_Pair *members;
}
J_Object;

typedef struct J_Array
{
	size_t        count;
	struct JSON **elements;
}
J_Array;

typedef struct JSON
{
	union
	{
		J_Object object;
		J_Array  array;
		char    *string;
		double   number;
		bool     boolean;
	}
	guts;
	J_Type type;
}
JSON;

JSON *j_new_object(void);
void j_object_add(JSON *object, J_Pair member);

JSON *j_new_array(void);
void j_array_prepend(JSON *array, JSON *value); // inefficient, but this is toy

JSON *j_new_string(char *string);
JSON *j_new_number(double number);
JSON *j_new_boolean(bool b);
JSON *j_new_null(void);

void j_write_to_file(FILE *file, JSON *json);

#endif
