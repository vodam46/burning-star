#ifndef WMAP_H
#define WMAP_H

#include "tile.h"

void rect_empty(tile** wmap, vector start, vector end, tile_type type);
void rect_filled(tile** wmap, vector start, vector end, tile_type type);

void circle_empty(tile** wmap, vector center, float radius, tile_type type);
void circle_filled(tile** wmap, vector center, float radius, tile_type type);

// create a map with all tiles of type type
tile** wmap_gen_tile(vector scr_size, tile_type type);

// create a maze base (walls every other tile)
tile** wmap_gen_maze_base(vector scr_size);

// generate a binary tree maze
tile** wmap_gen_bin_tree_maze(vector scr_size);

tile** wmap_gen_directional_cave(vector scr_size);

#endif
