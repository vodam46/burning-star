
// header guards
#ifndef TILE_H
#define TILE_H

// custom libraries
#include "entity.h"
#include "tile_type.h"

// tile structure
// x y position
// type of tile
// entity on tile
struct tile {
	struct vector pos;
	enum tile_type type;
	struct entity ent;
};

struct tile tile_init(struct vector _pos, enum tile_type _type, struct entity _ent);

#endif
