
// global libraries
#include <stdlib.h>

// custom libraries
#include "tile.h"
#include "entity.h"
#include "map.h"
#include "tile_type.h"

// world generation
// rows is the height
// cols is the width
tile** wmap_gen(int rows, int cols) {

	tile** wmap = malloc(rows * sizeof(tile));	// allocate the 2d array

	for (int y=0; y<rows; y++) {
		wmap[y] = malloc(cols * sizeof(tile));		// allocate each array of the 2d array
		for (int x=0; x<cols; x++) {
			// set the variables for each tile
			wmap[y][x].pos.y = y;								// y position
			wmap[y][x].pos.x = x;								// x position
			wmap[y][x].type = empty;						// type of tile
		}
	}
	return wmap;
}

tile** wmap_gen_tile(int rows, int cols, tile_type _type) {

	tile** wmap = malloc(rows * sizeof(tile));	// allocate the 2d array

	for (int y=0; y<rows; y++) {
		wmap[y] = malloc(cols * sizeof(tile));		// allocate each array of the 2d array
		for (int x=0; x<cols; x++) {
			// set the variables for each tile
			wmap[y][x].pos.y = y;								// y position
			wmap[y][x].pos.x = x;								// x position
			wmap[y][x].type = _type;								// type of tile
		}
	}
	return wmap;
}

tile** wmap_gen_maze_base(int rows, int cols) {

	tile** wmap = wmap_gen_tile(rows, cols, wall);

	for (int y=0; y<(int)(rows+1)/2; y++) {
		for (int x=0; x<(int)(cols+1)/2; x++) {
			wmap[y*2][x*2].type = empty;
		}
	}
	return wmap;
}

tile** wmap_gen_bin_tree_maze(int rows, int cols) {

	tile** wmap = wmap_gen_maze_base(rows, cols);

	for (int y=0; y<(int)(rows+1)/2; y++) {
		for (int x=0; x<(int)(cols+1)/2; x++) {
			if (y > 0 && x > 0) {
				if (rand() % 2) {
					wmap[y*2-1][x*2].type = empty;
				}
				else {
					wmap[y*2][x*2-1].type = empty;
				}
			} else if (y > 0) {
				wmap[y*2-1][x*2].type = empty;
			} else if (x > 0) {
				wmap[y*2][x*2-1].type = empty;
			}
		}
	}
	return wmap;
}
