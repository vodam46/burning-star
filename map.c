#include <stdlib.h>

#include "tile.h"
#include "entity.h"
#include "map.h"

struct tile** wmap_gen(int rows, int cols) {

	struct tile** wmap = (struct tile**) malloc(sizeof(struct tile) * rows);

	for (int i=0; i<rows; i++) {
		wmap[i] = malloc(sizeof(struct tile) * cols);
	};
	return wmap;
};

