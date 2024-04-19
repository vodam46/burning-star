#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "key_val_reader.h"

/*
 * sort of like INI files
 * arbitrary spacing (they all get ignored)
 * # comments
 */

pairs_arr parse_file(char* filename) {
	FILE* file = fopen(filename, "r");
	pair* pairs;
	int num_lines = 0;
	int ch;
	while (!feof(file)) {
		ch = fgetc(file);
		if (ch == '\n')
			num_lines++;
	}
	rewind(file);
	pairs = calloc(num_lines+1, sizeof(pair));

	int cur_line_len = 0;
	int cur_line = 0;
	while (!feof(file)) {
		ch = fgetc(file);
		if (ch == '\n') {
			pairs[cur_line].key = calloc((cur_line_len+1), sizeof(char));
			pairs[cur_line].value.string = calloc((cur_line_len+1), sizeof(char));
			cur_line_len = 0;
			cur_line++;
		} else if (ch != ' ' || ch != '\t') {
			cur_line_len++;
		}
	}
	rewind(file);

	for (int i = 0; i < num_lines; i++) {

		int write = 1;
		int array = 0;
		int num_elements = 1;
		int cur_element = 0;
		int value = 0;

		while (!feof(file)) {
			ch = fgetc(file);

			if (ch == '#') {
				write = 0;
			} else if (ch == '\n') {
				array = 0;
				break;
			} else if (ch == '=') {
				value = 1;
				continue;
			} else if (ch == '[') {

				array = 1;

				fpos_t cur_point;
				fgetpos(file, &cur_point);

				int line_len = 0;
				while (!feof(file) && ch != ']' && ch != '\n') {
					ch = fgetc(file);
					if (ch == ']' || ch == ' ') continue;
					if (ch == ',') {
						num_elements++;
					} else {
						line_len++;
					}
				}

				pairs[i].value.type = 1;
				pairs[i].value.array = malloc(num_elements * sizeof(char*));
				pairs[i].value.num_elements = num_elements;
				for (int j = 0; j < num_elements; j++) {
					pairs[i].value.array[j] = calloc(line_len+1, sizeof(char));
				}

				fsetpos(file, &cur_point);
			} else if (ch != ' ' && write && ch != '\t' && !(ch == ']' && array)) {
				if (value) {

					if (array) {
						if (ch != ',') {
							strncat(pairs[i].value.array[cur_element], (char*)&ch, 1);
						} else if (ch == ',') {
							cur_element++;
						}


					} else {
						strncat(pairs[i].value.string, (char*)&ch, 1);
					}

				} else {
					strncat(pairs[i].key, (char*)&ch, 1);
				}
			}
		}
	}

	fclose(file);
	return (pairs_arr){ pairs, num_lines };
}

value get_value(char* key, pairs_arr pairs) {
	for (int i = 0; i < pairs.num_pairs; i++) {
		if (strcmp(key, pairs.pairs[i].key) == 0) {
			return pairs.pairs[i].value;
		}
	}
	return (value){0};
}

void delete_pairs(pairs_arr pairs) {
	for (int i = 0; i < pairs.num_pairs; i++) {
		free(pairs.pairs[i].key);
		free(pairs.pairs[i].value.string);
	}
	free(pairs.pairs);
}
