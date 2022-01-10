#include <stdlib.h>

#include "tile.h"
#include "entity.h"
#include "map.h"
#include "tile_type.h"

struct tile** wmap_gen(int rows, int cols) {

	struct tile** wmap = calloc(rows, sizeof(struct tile));

	for (int y=0; y<rows; y++) {
		wmap[y] = calloc(cols, sizeof(struct tile));
		for (int x=0; x<cols; x++) {
			wmap[y][x].y = y;
			wmap[y][x].x = x;
			wmap[y][x].type = empty;
		}
	}


	return wmap;
};

