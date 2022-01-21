
// custom libraries
#include "tile.h"
#include "entity.h"

// tile initialization function
// x y position
// type of tile
// entity on the tile
struct tile tile_init(struct vector _pos, enum tile_type _type, struct entity _ent) {
	struct tile ret_tile;
	ret_tile.pos = _pos;
	ret_tile.type = _type;
	ret_tile.ent = _ent;
	return ret_tile;
}
