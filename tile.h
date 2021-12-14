#ifndef TILE_H
#define TILE_H

#include "entity.h"

enum tileType {
	none
	// TODO: populate
};

struct tile {
	int x;
	int y;
	enum tileType type;
	struct entity ent_on_tile;
};

struct tile tile_init(int _x, int _y, enum tileType _type, struct entity _ent_on_tile);

#endif