
// header guards
#ifndef WMAP_H
#define WMAP_H

// custom libraries
#include "tile.h"

// initialize the empty map
tile** wmap_gen(int rows, int cols);

// create a map with all tiles of type _type
tile** wmap_gen_tile(int rows, int cols, tile_type _type);

// create a maze base (walls every other tile)
tile** wmap_gen_maze_base(int rows, int cols);

// generate a binary tree maze
tile** wmap_gen_bin_tree_maze(int rows, int cols);

#endif
