
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
int width;					// width of the screen - x
int height;					// height of the screen - y
tile** wmap;			// world map - array of arrays
entity** ent_arr;	// entity array - array of pointers
int ent_num = 0;


// move entity from old_pos to new_pos, ent_arr_id is the position in ent_arr
void ent_move(int ent_arr_id, vector pos_change) {

	vector old = ent_arr[ent_arr_id]->pos;
	vector new = vect_add(ent_arr[ent_arr_id]->pos, pos_change); 

	// move only if new_pos is within the bounds of the screen and if the new tile isnt a wall
	if (in_bounds(vect_init(new.y, new.x), vect_init(0, 0), vect_init(height, width)) && wmap[new.y][new.x].type != wall && wmap[new.y][new.x].ent.type == none) {
		
		// copy the entity from old position to new position
		wmap[new.y][new.x].ent = wmap[old.y][old.x].ent;					// copy to the new position
		wmap[new.y][new.x].ent.pos.y = new.y;								// update the y position
		wmap[new.y][new.x].ent.pos.x = new.x;								// update the x position
		wmap[old.y][old.x].ent = ent_init(vect_init(old.y, old.x), none);	// the entity from the old_position to the new positon

		// update the entity array
		ent_arr[ent_arr_id] = &wmap[new.y][new.x].ent;
	}
}

void create_entity(vector pos, entity_type _type) {

	wmap[pos.y][pos.x].ent.type = _type;
	wmap[pos.y][pos.x].ent.pos = pos;
	ent_arr[ent_num] = &wmap[pos.y][pos.x].ent;
	ent_num++;
}

int main() {
	
	srand(time(NULL));
	
	// screen init
	initscr();							// put screen into ncurses mode
	keypad(stdscr, TRUE);				// expand the user input keys ( F keys, arrow keys)
	getmaxyx(stdscr, height, width);	// set height and width to the height and width of the screen

	int player_y = 10;
	int player_x = 10;

	// map init
	wmap = wmap_gen(height, width);									// generate the map
	ent_arr = malloc(height * width + 1 * sizeof(entity));	// dynamic allocation of the entity array

	create_entity(vect_init(player_y, player_x), player);
	create_entity(vect_init(1, 1), enemy);

	// main game loop
	// exits only once input is 10 (ENTER key)
	while (ch != 'q') {
		draw_wmap(wmap, height, width);	// draws the map
		move(height-1, width-1);
		ch = getch();					// updates the user input

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
				ent_move(0, vect_init(-1, 0));
				break;
			// right arrow or 6
			case(KEY_RIGHT): case(54):			// x +
				ent_move(0, vect_init(0, +1));
				break;
			// down arrow or 2
			case(KEY_DOWN):	case(50):			// y +
				ent_move(0, vect_init(+1, 0));
				break;
			// left arrow or 4
			case(KEY_LEFT):	case(52):			// x -
				ent_move(0, vect_init(0, -1));
				break;

			default:
				break;
		}

		if (ch == 10) break;

		for (int ent_i = 1; ent_i < ent_num; ent_i++) {
			ent_move(ent_i, basic_dir(ent_arr[ent_i]->pos, ent_arr[0]->pos));
		}
	}

	endwin();		// end ncurses mode
	free(wmap);		// free the memory for the world map
	free(ent_arr);	// free the memory for the entity array
	return 0;
}
