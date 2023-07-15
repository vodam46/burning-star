#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// custom libraries
#include "tile.h"
#include "entity.h"

const char* tile_name[] = {
	"empty",
	"wall",
};

til_data tile_data[last_tile] = {0};
void tiles_init() {
	char data_dir[100];
	strcpy(data_dir, PROJECT_DIR);
	strcat(data_dir,"/data/tile/");
	for (int i = 1; i < last_tile; i++) {
		char file_name[100];
		strcpy(file_name, data_dir);
		strcat(file_name, tile_name[i]);

		FILE* file = fopen(file_name, "r");

		tile_data[i].tile.type = i;
		char* line = NULL;
		size_t len = 0;
		getline(&line, &len, file); // name

		getline(&line, &len, file); // char
		tile_data[i].tile_char = malloc(len*sizeof(char));
		strcpy(tile_data[i].tile_char, line);

		getline(&line, &len, file); // color
		tile_data[i].tile_color = atoi(line);

		fclose(file);
	}
}

tile tile_init(vector pos, tile_type type, entity ent) {
	tile ret_tile;
	ret_tile.pos = pos;
	ret_tile.type = type;
	ret_tile.ent = ent;
	return ret_tile;
}

int tile_comp(tile left, tile right) {
	return vect_comp(left.pos, right.pos) && left.type == right.type && ent_comp(left.ent, right.ent);
}
