#include <stdlib.h>

#include "tile.h"
#include "entity.h"
#include "map.h"
#include "tile_type.h"

struct tile** wmap_gen(int rows, int cols) {

	struct tile** wmap = (struct tile**) malloc(sizeof(struct tile) * rows);

	for (int i=0; i<rows; i++) {
		wmap[i] = malloc(sizeof(struct tile) * cols);
	};

	for (int y=0; y<rows; y++) {
		for (int x=0; x<cols; x++) {
			wmap[y][x].y = y;
			wmap[y][x].x = x;
			wmap[y][x].type = empty;
		}
	}

	return wmap;
};

