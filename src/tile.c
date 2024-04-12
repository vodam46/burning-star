#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// custom libraries
#include "tile.h"
#include "entity.h"
#include "key_val_reader.h"

const char* tile_name[] = {
	"empty",
	"wall",
	"water"
};

til_data tile_data[last_tile] = {0};
void tiles_init(void) {
	char data_dir[100] = PROJECT_DIR;
	strcat(data_dir,"/data/tile/");
	for (int i = 0; i < last_tile; i++) {
		char file_name[100] = {0};
		strcpy(file_name, data_dir);
		strcat(file_name, tile_name[i]);

		pairs_arr pairs = parse_file(file_name);

		tile_data[i].tile.type = i;

		char* tile_char = get_value("char", pairs).string;
		tile_data[i].tile_char = malloc((strlen(tile_char)+1) * sizeof(char));
		strcpy(tile_data[i].tile_char, tile_char);

		tile_data[i].tile_color = atoi(get_value("color", pairs).string);

		delete_pairs(pairs);
	}
}

tile tile_init(vector pos, tile_type type, entity ent, inventory items) {
	tile ret_tile;
	ret_tile.pos = pos;
	ret_tile.type = type;
	ret_tile.ent = ent;
	ret_tile.items = items;
	return ret_tile;
}

int tile_comp(tile left, tile right) {
	return vect_comp(left.pos, right.pos) && left.type == right.type && ent_comp(left.ent, right.ent);
}
