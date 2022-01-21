
// global libraries
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

// custom libraries
#include "tile.h"
#include "entity.h"
#include "map.h"
#include "entity_type.h"
#include "drawing.h"
#include "vector.h"


// global variables
int ch = 0;					// user input
int width;					// width of the screen - x
int height;					// height of the screen - y
struct tile** wmap;			// world map - array of arrays
struct entity** ent_arr;	// entity array - array of pointers

// function to check if position is within boundaries
int in_bounds(struct vector pos, struct vector min, struct vector max) {
	return pos.y >= min.y && pos.y < max.y && pos.x >= min.x && pos.x < max.x;
};

// move entity from old_pos to new_pos, ent_arr_id is the position in ent_arr
void ent_move(int ent_arr_id, struct vector pos_change) {

	// debug message
	// printf("old_y: %d, old_x: %d, new_y: %d, new_x: %d in_bounds: %d / ", old_y, old_x, new_y, new_x, in_bounds(new_y, new_x, 0, 0, height, width));

	struct vector old = ent_arr[ent_arr_id]->pos;
	struct vector new = vect_add(ent_arr[ent_arr_id]->pos, pos_change); 

	// move only if new_pos is within the bounds of the screen
	if (in_bounds(vect_init(new.y, new.x), vect_init(0, 0), vect_init(height, width))) {
		
		// copy the entity from old position to new position
		wmap[new.y][new.x].ent = wmap[old.y][old.x].ent;		// copy to the new position
		wmap[new.y][new.x].ent.pos.y = new.y;						// update the y position
		wmap[new.y][new.x].ent.pos.x = new.x;						// update the x position
		wmap[old.y][old.x].ent = ent_init(vect_init(old.y, old.x), none);	// delete the entity from the old_position

		// update the entity array
		ent_arr[ent_arr_id] = &wmap[new.y][new.x].ent;
	}
};

int main() {
	
	
	// screen init
	initscr();							// put screen into ncurses mode
	keypad(stdscr, TRUE);				// expand the user input keys ( F keys, arrow keys)
	getmaxyx(stdscr, height, width);	// set height and width to the height and width of the screen

	// map init
	wmap = wmap_gen(height, width);									// generate the map
	ent_arr = malloc(height * width + 1 * sizeof(struct entity));	// dynamic allocation of the entity array
																	// +1 in case someone figures out how to make a 0*0 terminal

	wmap[0][0].ent.type = player;	// set the 0 0 position to the player
	ent_arr[0] = &wmap[0][0].ent;	// set the array element 0 to the player

	
	// main game loop
	// exits only once input is 10 (ENTER key)
	while (ch != 10) {
		draw_wmap(wmap, height, width);	// draws the map
		ch = getch();					// updates the user input

		// react to user input
		switch(ch) {
			/*

			^ = y -1 x 0

			> = y 0 x +1

			V = y +1 x 0

			< = y 0 x -1

			*/
			case(KEY_UP):		// y -
				ent_move(0, vect_init(-1, 0));
				break;
			case(KEY_RIGHT):	// x +
				ent_move(0, vect_init(0, +1));
				break;
			case(KEY_DOWN):		// y +
				ent_move(0, vect_init(+1, 0));
				break;
			case(KEY_LEFT):		// x -
				ent_move(0, vect_init(0, -1));
				break;


			default:
				break;

		};
		
//		printf("ent_arr x: %d, ent_arr y: %d / ", ent_arr[0]->y, ent_arr[0]->x);
	};

	endwin();		// end ncurses mode
	free(wmap);		// free the memory for the world map
	free(ent_arr);	// free the memory for the entity array
	return 0;
};
