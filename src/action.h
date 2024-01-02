#ifndef ACTION_H
#define ACTION_H

#include "map.h"
#include "entity.h"
#include "tile.h"

int ent_action(
	world_map wmap,
	int ent_arr_id,
	vector pos_change,
	vector scr_size
);
int create_entity(world_map map, vector pos, entity_type type);
int pick_up_item(world_map map, int ent_i);
int use_item(world_map map, int ent_i, int inv_i);
#endif
