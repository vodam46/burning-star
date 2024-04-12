#ifndef KEY_VAL_READER_H
#define KEY_VAL_READER_H

typedef struct {
	int type;

	char* string;

	int num_elements;
	char** array;
} value;

typedef struct {
	char* key;
	value value;
} pair;

typedef struct {
	pair* pairs;
	int num_pairs;
} pairs_arr;

pairs_arr parse_file(char* filename);
value get_value(char* key, pairs_arr pairs);
void delete_pairs(pairs_arr pairs);

#endif
