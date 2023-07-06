// global libraries
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// custom libraries
#include "tile.h"
#include "entity.h"
#include "map.h"
#include "entity_type.h"
#include "drawing.h"
#include "vector.h"
#include "ai.h"


// global variables
int ent_num = 0;


// move entity from old_pos to new_pos, ent_arr_id is the position in ent_arr
void ent_action(tile** wmap, entity** ent_arr, int ent_arr_id, vector pos_change, vector scr_size) {
	vector old = ent_arr[ent_arr_id]->pos;
	vector new = vect_add(ent_arr[ent_arr_id]->pos, pos_change);

	// move only if new_pos is within the bounds of the screen
	// and if the new tile isnt a wall
	if (in_bounds(vect_init(new.y, new.x), vect_init(0, 0), scr_size)
			&& !vect_comp(old,new)) {
		if (wmap[new.y][new.x].ent.type != none) { 
			wmap[new.y][new.x].ent.health -= wmap[old.y][old.x].ent.strength;
		}
		if (wmap[new.y][new.x].type != wall) {
			if (wmap[new.y][new.x].ent.type == none) {

				// copy the entity from old position to new position
				wmap[new.y][new.x].ent = wmap[old.y][old.x].ent;
				wmap[new.y][new.x].ent.pos.y = new.y;
				wmap[new.y][new.x].ent.pos.x = new.x;

				// the entity from the old_position to the new positon
				wmap[old.y][old.x].ent = ent_init(vect_init(old.y, old.x),
						none, 0, 0);

				// update the entity array
				ent_arr[ent_arr_id] = &wmap[new.y][new.x].ent;
			}
		}
	}
}

void create_entity(tile** wmap, entity** ent_arr, vector pos, entity_type _type, int _strength, int _health) {
	wmap[pos.y][pos.x].ent = ent_init(pos,_type,_strength,_health);
	ent_arr[ent_num] = &wmap[pos.y][pos.x].ent;
	ent_num++;
}

int main() {
	srand(time(NULL));

	// screen init
	initscr();
	keypad(stdscr, TRUE);
	vector scr_size;
	getmaxyx(stdscr, scr_size.y, scr_size.x);
	vector main_scr_size = vect_init(scr_size.y-4,scr_size.x-2);

	WINDOW* main_scr = newwin(main_scr_size.y,main_scr_size.x, 3,1);

	int player_y = (int)(main_scr_size.y/2) + (main_scr_size.y%2==0 ? 0 : 1);
	int player_x = (int)(main_scr_size.x/2) + (main_scr_size.x%2==0 ? 1 : 0);
	char msg[20] = "";

	tile** wmap = wmap_gen_bin_tree_maze(main_scr_size.y, main_scr_size.x);
	entity** ent_arr = malloc(main_scr_size.y * main_scr_size.x * sizeof(entity));

	create_entity(wmap, ent_arr, vect_init(player_y, player_x), player, 5, 20);
	create_entity(wmap, ent_arr, vect_init(0, 0), enemy, 1, 5);

	int ch = 0;
	// main game loop
	while (ch != 'q') {
		sprintf(msg, "%d/%d hp, %d str", ent_arr[0]->health, ent_arr[0]->maxhealth, ent_arr[0]->strength);
		draw(stdscr, main_scr, wmap, scr_size, main_scr_size, msg);
		move(ent_arr[0]->pos.y+3,ent_arr[0]->pos.x+1);



		ch = wgetch(stdscr);					// updates the user input
		vector move_dir = vect_init(0,0);
		// react to user input
		switch(ch) {
			/*

			   ^ = y -1 x 0

			   > = y 0 x +1

			   V = y +1 x 0

			   < = y 0 x -1

*/
			// up arrow or 8
			case(KEY_UP): case(56):				// y -
				move_dir = vect_init(-1, 0);
				break;
				// right arrow or 6
			case(KEY_RIGHT): case(54):			// x +
				move_dir = vect_init(0, +1);
				break;
				// down arrow or 2
			case(KEY_DOWN):	case(50):			// y +
				move_dir = vect_init(+1, 0);
				break;
				// left arrow or 4
			case(KEY_LEFT):	case(52):			// x -
				move_dir = vect_init(0, -1);
				break;

			default:
				// sprintf(msg, "%d, %c", ch, ch);
				break;
		}
		ent_action(wmap, ent_arr, 0, move_dir, main_scr_size);

		for (int ent_i = 1; ent_i < ent_num; ent_i++) {
			if (ent_arr[ent_i]->health <= 0) {
				// delete
				ent_arr[ent_i]->type = none;
				for (int i = ent_i; i < ent_num-1; i++) {
					ent_arr[i] = ent_arr[i+1];
				}
				ent_i--;
				ent_num--;
			}
			ent_action(wmap, ent_arr, ent_i, basic_dir(ent_arr[ent_i]->pos, ent_arr[0]->pos), main_scr_size);
		}
		if (ent_arr[0]->health <= 0)
			break;
	}

	endwin();		// end ncurses mode
	for (int y = 0; y < scr_size.y; y++)
		free(wmap[y]);
	free(wmap);		// free the memory for the world map
	free(ent_arr);	// free the memory for the entity array
	return 0;
}
