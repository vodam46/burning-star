#ifndef ACTION_H
#define ACTION_H

#include <ncurses.h>

#include "map.h"
#include "entity.h"
#include "tile.h"

int ent_action(
	world_map wmap,
	int ent_arr_id,
	vector pos_change,
	vector scr_size
);
int dig(world_map wmap, vector pos, vector dir);
int create_entity(world_map map, vector pos, entity_type type);
int pick_up_item(world_map map, int ent_i);
int use_item_from_inventory(WINDOW* stdscr, vector scr_size, world_map wmap, int ent_i);
int use_item(world_map map, int ent_i, int inv_i);
#endif
