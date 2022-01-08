#ifndef TILE_H
#define TILE_H

#include "entity.h"
#include "tile_type.h"


struct tile {
	int x;
	int y;
	enum tile_type type;
	struct entity ent_on_tile;
};

struct tile tile_init(int _x, int _y, enum tile_type _type, struct entity _ent_on_tile);

#endif
