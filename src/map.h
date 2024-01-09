#ifndef WMAP_H
#define WMAP_H

#include "tile.h"

typedef struct {
	tile** map;
	entity** ent_arr;
	int ent_num;
	vector size;
} world_map;

void rect_empty(tile** wmap, vector start, vector end, tile_type type);
void rect_filled(tile** wmap, vector start, vector end, tile_type type);

void circle_empty(tile** wmap, vector center, float radius, tile_type type);
void circle_filled(tile** wmap, vector center, float radius, tile_type type);

world_map wmap_gen_tile(vector map_size, tile_type type);
world_map wmap_gen_maze_base(vector map_size);
world_map wmap_gen_bin_tree_maze(vector map_size);
world_map wmap_gen_directional_cave(vector map_size);
world_map wmap_gen_noise(vector map_size);

#endif
