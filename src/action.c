#include "action.h"
#include "entity.h"
#include "tile.h"

// move entity from old_pos to new_pos, ent_arr_id is the position in ent_arr
int ent_action(tile** wmap, entity** ent_arr, int ent_arr_id, vector pos_change, vector scr_size) {
	vector old = ent_arr[ent_arr_id]->pos;
	vector new = vect_add(ent_arr[ent_arr_id]->pos, pos_change);

	// move only if new_pos is within the bounds of the screen
	// and if the new tile isnt a wall
	int user_moved = 0;
	if (in_bounds(vect_init(new.y, new.x), vect_init(0, 0), scr_size) && !vect_comp(old,new)) {
		if (wmap[new.y][new.x].ent.type != none) { 
			wmap[new.y][new.x].ent.health -= wmap[old.y][old.x].ent.strength;
			user_moved = 1;
		}
		if (wmap[new.y][new.x].type != wall && wmap[new.y][new.x].ent.type == none) {

			// copy the entity from old position to new position
			wmap[new.y][new.x].ent = wmap[old.y][old.x].ent;
			wmap[new.y][new.x].ent.pos.y = new.y;
			wmap[new.y][new.x].ent.pos.x = new.x;

			// the entity from the old_position to the new positon
			wmap[old.y][old.x].ent = ent_init(vect_init(old.y, old.x), none, 0, 0);

			// update the entity array
			ent_arr[ent_arr_id] = &wmap[new.y][new.x].ent;
			user_moved = 1;
		}
	}
	return user_moved;
}

int create_entity(tile** wmap, entity** ent_arr, int ent_num, vector pos, entity_type _type, int _strength, int _health) {
	wmap[pos.y][pos.x].ent = ent_init(pos,_type,_strength,_health);
	ent_arr[ent_num] = &wmap[pos.y][pos.x].ent;
	ent_num++;
	return ent_num;
}

