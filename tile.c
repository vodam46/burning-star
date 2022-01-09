

#include "tile.h"
#include "entity.h"


struct tile tile_init(int _x, int _y, enum tile_type _type, struct entity _ent) {
	struct tile ret_tile;
	ret_tile.x = _x;
	ret_tile.y = _y;
	ret_tile.type = _type;
	ret_tile.ent = _ent;
	return ret_tile;
}
