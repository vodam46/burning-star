
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
struct tile** wmap_gen(int rows, int cols) {

	struct tile** wmap = malloc(rows, sizeof(struct tile));	// allocate the 2d array

	for (int y=0; y<rows; y++) {
		wmap[y] = calloc(cols, sizeof(struct tile));		// allocate each array of the 2d array
		for (int x=0; x<cols; x++) {

			// set the variables for each tile
			wmap[y][x].y = y;								// y position
			wmap[y][x].x = x;								// x position
			wmap[y][x].type = empty;						// type of tile
		}
	}

	return wmap;
};

