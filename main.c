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
int ch = 0;					// user input
vector scr_size;
tile** wmap;				// world map - array of arrays
entity** ent_arr;			// entity array - array of pointers
int ent_num = 0;


// move entity from old_pos to new_pos, ent_arr_id is the position in ent_arr
void ent_action(int ent_arr_id, vector pos_change) {

	vector old = ent_arr[ent_arr_id]->pos;
	vector new = vect_add(ent_arr[ent_arr_id]->pos, pos_change);

        // move only if new_pos is within the bounds of the screen
		// and if the new tile isnt a wall
        if (in_bounds(vect_init(new.y, new.x),
					vect_init(0, 0),
					vect_init(scr_size.y, scr_size.x))
				&& !vect_comp(old,new)) {
			if (wmap[new.y][new.x].ent.type != none) { 
				wmap[new.y][new.x].ent.health -= wmap[old.y][old.x].ent.strength;
			}
			else if (wmap[new.y][new.x].type != wall) {
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

void create_entity(vector pos, entity_type _type, int _strength, int _health) {

	wmap[pos.y][pos.x].ent = ent_init(pos,_type,_strength,_health);
	ent_arr[ent_num] = &wmap[pos.y][pos.x].ent;
	ent_num++;
}

int main() {
	
	srand(time(NULL));
	
	// screen init
	initscr();
	keypad(stdscr, TRUE);
	getmaxyx(stdscr, scr_size.y, scr_size.x);

	int player_y = (int)scr_size.y/2 + (scr_size.y%2==0 ? 0 : 1);
	int player_x = (int)scr_size.x/2 + (scr_size.x%2==0 ? 0 : 1);

	wmap = wmap_gen_bin_tree_maze(scr_size.y, scr_size.x);
	ent_arr = malloc(scr_size.y * scr_size.x + 1 * sizeof(entity));

	create_entity(vect_init(player_y, player_x), player, 5, 20);
	create_entity(vect_init(1, 1), enemy, 1, 5);

	// main game loop
	// exits only once input is 10 (ENTER key)
	while (ch != 'q') {
		draw_wmap(wmap, scr_size);	// draws the map
		move(scr_size.y-1, scr_size.x-1);
		ch = getch();					// updates the user input

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
				break;
		}
		if (ch == 10) break;
		ent_action(0, move_dir);
		if (ent_arr[0]->health <= 0)
			break;

		for (int ent_i = 1; ent_i < ent_num; ent_i++) {
			ent_action(ent_i, basic_dir(ent_arr[ent_i]->pos, ent_arr[0]->pos));
			if (ent_arr[ent_i]->health <= 0) {
				// delete
				ent_arr[ent_i]->type = none;
				for (int i = ent_i; i < ent_num-1; i++) {
					ent_arr[i] = ent_arr[i+1];
				}
				ent_i--;
				ent_num--;
			}
		}
	}

	endwin();		// end ncurses mode
	free(wmap);		// free the memory for the world map
	free(ent_arr);	// free the memory for the entity array
	return 0;
}
