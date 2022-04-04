
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
typedef struct {
	vector pos;
	tile_type type;
	entity ent;
} tile ;

tile tile_init(vector _pos, tile_type _type, entity _ent);

#endif
