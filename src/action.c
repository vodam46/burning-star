#include "action.h"
#include "entity.h"
#include "tile.h"
#include "map.h"

// move entity from old_pos to new_pos, ent_arr_id is the position in ent_arr
int ent_action(world_map wmap, int ent_arr_id, vector pos_change, vector scr_size) {
	vector old = wmap.ent_arr[ent_arr_id]->pos;
	vector new = vect_add(wmap.ent_arr[ent_arr_id]->pos, pos_change);

	// move only if new_pos is within the bounds of the screen
	// and if the new tile isnt a wall
	int user_moved = 0;
	if (in_bounds(vect_init(new.y, new.x), vect_init(0, 0), scr_size) && !vect_comp(old,new)) {
		if (wmap.map[new.y][new.x].ent.type != none) {
			wmap.map[new.y][new.x].ent.health -= wmap.map[old.y][old.x].ent.strength;
			user_moved = 1;
		}
		if (wmap.map[new.y][new.x].type != wall && wmap.map[new.y][new.x].ent.type == none) {

			// copy the entity from old position to new position
			wmap.map[new.y][new.x].ent = wmap.map[old.y][old.x].ent;
			wmap.map[new.y][new.x].ent.pos.y = new.y;
			wmap.map[new.y][new.x].ent.pos.x = new.x;

			// the entity from the old_position to the new positon
			wmap.map[old.y][old.x].ent = ent_init(vect_init(old.y, old.x), none, 0, 0, 0);

			// update the entity array
			wmap.ent_arr[ent_arr_id] = &wmap.map[new.y][new.x].ent;
			user_moved = 1;
		}
	}
	return user_moved;
}

int create_entity(world_map wmap, vector pos, entity_type type) {
	wmap.map[pos.y][pos.x].ent = ent_data[type].ent;
	wmap.map[pos.y][pos.x].ent.pos = pos;
	wmap.ent_arr[wmap.ent_num] = &wmap.map[pos.y][pos.x].ent;
	wmap.ent_num++;
	return wmap.ent_num;
}

