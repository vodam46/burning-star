
// header guards
#ifndef WMAP_H
#define WMAP_H

// custom libraries
#include "tile.h"

// initialize the empty map
struct tile** wmap_gen(int rows, int cols);

// create a map with all tiles of type _type
struct tile** wmap_gen_tile(int rows, int cols, enum tile_type _type);

// create a maze base (walls every other tile)
struct tile** wmap_gen_maze_base(int rows, int cols);

// generate a binary tree maze
struct tile** wmap_gen_bin_tree_maze(int rows, int cols);

#endif
