#include <stdlib.h>
#include <string.h>

#include "action.h"
#include "entity.h"
#include "tile.h"
#include "map.h"
#include "item.h"
#include "menu.h"

// move entity from old_pos to new_pos, ent_arr_id is the position in ent_arr
int ent_action(
	world_map wmap,
	int ent_arr_id,
	vector pos_change,
	vector scr_size
) {
	vector old = wmap.ent_arr[ent_arr_id]->pos;
	vector new = vect_add(old, pos_change);

	// move only if new_pos is within the bounds of the screen
	// and if the new tile isnt a wall
	int user_moved = 0;
	if (
		in_bounds(vect_init(new.y, new.x), vect_init(0, 0), scr_size)
		&& !vect_comp(old,new)
	) {
		if (wmap.map[new.y][new.x].ent.type != none_entity) {
			wmap.map[new.y][new.x].ent.health -= wmap.map[old.y][old.x].ent.strength;
			user_moved = 1;
		}
		if (
			tile_data[wmap.map[new.y][new.x].type].walkable
			&& wmap.map[new.y][new.x].ent.type == none_entity
		) {

			// copy the entity from old position to new position
			wmap.map[new.y][new.x].ent = wmap.map[old.y][old.x].ent;
			wmap.map[new.y][new.x].ent.pos.y = new.y;
			wmap.map[new.y][new.x].ent.pos.x = new.x;

			// the entity from the old_position to the new positon
			wmap.map[old.y][old.x].ent = ent_init(
				vect_init(old.y, old.x),
				none_entity,
				0,
				0,
				0,
				(inventory){0}
			);

			// update the entity array
			wmap.ent_arr[ent_arr_id] = &wmap.map[new.y][new.x].ent;
			user_moved = 1;
		} else if (ent_arr_id != 0) {
			user_moved = dig(wmap, old, pos_change);
		}
	}
	return user_moved;
}

int dig(world_map wmap, vector pos, vector dir) {
	vector new_pos = vect_add(pos, dir);
	if (
		in_bounds(new_pos, vect_init(0, 0), wmap.size) &&
		wmap.map[new_pos.y][new_pos.x].type == wall
	) {
		wmap.map[new_pos.y][new_pos.x].type = empty;
	} else {
		return 0;
	}
	return 1;
}

int create_entity(world_map wmap, vector pos, entity_type type) {
	wmap.map[pos.y][pos.x].ent = ent_data[type].ent;
	wmap.map[pos.y][pos.x].ent.pos = pos;
	wmap.ent_arr[wmap.ent_num] = &wmap.map[pos.y][pos.x].ent;
	wmap.ent_num++;
	return wmap.ent_num;
}

int pick_up_item(world_map map, int ent_i) {
	vector pos = map.ent_arr[ent_i]->pos;
	if (map.map[pos.y][pos.x].items.num_items != 0) {
		map.ent_arr[ent_i]->inventory = add_to_inventory(
			map.ent_arr[ent_i]->inventory,
			map.map[pos.y][pos.x].items.items[0]
		);
		map.map[pos.y][pos.x].items = remove_from_inventory(
			map.map[pos.y][pos.x].items,
			0
		);
		return 1;
	}

	return 0;
}

int use_item_from_inventory(world_map wmap, int ent_i) {
	char** item_names = malloc(wmap.ent_arr[0]->inventory.num_items);
	for (int i = 0; i < wmap.ent_arr[ent_i]->inventory.num_items; i++) {
		item_names[0] = calloc((strlen(item_data[wmap.ent_arr[ent_i]->inventory.items[i].type].item_name)+1),sizeof(char));
		strcpy(item_names[i], item_data[wmap.ent_arr[ent_i]->inventory.items[i].type].item_name);
	}
	int choice = menu("Choose item to use", item_names, wmap.ent_arr[0]->inventory.num_items);
	if (choice > 0)
		return use_item(wmap, ent_i, choice);
	else
		return -1;
}

int use_item(world_map wmap, int ent_i, int inv_i) {
	item ite = wmap.ent_arr[ent_i]->inventory.items[inv_i];
	wmap.ent_arr[ent_i]->inventory = remove_from_inventory(wmap.ent_arr[ent_i]->inventory, inv_i);
	int new_health;
	switch(ite.type) {
		case(health_potion):
			new_health = wmap.ent_arr[ent_i]->health + ite.stats[0];
			wmap.ent_arr[ent_i]->health = new_health <= wmap.ent_arr[ent_i]->maxhealth ? new_health : wmap.ent_arr[ent_i]->maxhealth;
			return 1;
			break;
		default:
			return 0;
			break;
	}
}
