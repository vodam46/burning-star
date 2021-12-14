

#include "tile.h"
#include "entity.h"


struct tile tile_init(int _x, int _y, enum tileType _type, struct entity _ent_on_tile) {
	struct tile ret_tile;
	ret_tile.x = _x;
	ret_tile.y = _y;
	ret_tile.type = _type;
	ret_tile.ent_on_tile = _ent_on_tile;
	return ret_tile;
}