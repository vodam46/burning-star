
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "tile.h"
#include "entity.h"
#include "map.h"
#include "entity_type.h"
#include "drawing.h"


// global variables
int ch = 0;
int width;	// x
int height;	// y
struct tile** wmap;			// world map - array of arrays
struct entity** ent_arr;	// entity array - array of pointers

int in_bounds(int pos_y, int pos_x, int min_y, int min_x, int max_y, int max_x) {
	return pos_y >= min_y && pos_y < max_y && pos_x >= min_x && pos_x < max_x;
};

void entity_move(int old_y, int old_x, int new_y, int new_x, int ent_arr_id) {

//	printf("old_y: %d, old_x: %d, new_y: %d, new_x: %d in_bounds: %d / ", old_y, old_x, new_y, new_x, in_bounds(new_y, new_x, 0, 0, height, width));

	if (in_bounds(new_y, new_x, 0, 0, height, width)) {
		
		// copy the entity from old position to new position
		wmap[new_y][new_x].ent = wmap[old_y][old_x].ent;
		wmap[new_y][new_x].ent.y = new_y;
		wmap[new_y][new_x].ent.x = new_x;
		wmap[old_y][old_x].ent = ent_init(old_y, old_x, none);

		// update the entity array
		ent_arr[ent_arr_id] = &wmap[new_y][new_x].ent;
	}
};

int main() {
	
	
	// screen init
	initscr();
	keypad(stdscr, TRUE);
	getmaxyx(stdscr, height, width);

	// map init
	wmap = wmap_gen(height, width);
	ent_arr = malloc(height * width + 1 * sizeof(struct entity));	// +1 in case someone figures out how to make a 0*0 terminal

	wmap[0][0].ent.type = player;
	ent_arr[0] = &wmap[0][0].ent;


	while (ch != 10) {
		draw_wmap(wmap, height, width);
		ch = getch();

		switch(ch) {

			case(KEY_UP):		// y -
				entity_move(ent_arr[0]->y, ent_arr[0]->x, ent_arr[0]->y-1, ent_arr[0]->x, 0);
				break;
			case(KEY_RIGHT):	// x +
				entity_move(ent_arr[0]->y, ent_arr[0]->x, ent_arr[0]->y, ent_arr[0]->x+1, 0);
				break;
			case(KEY_DOWN):		// y +
				entity_move(ent_arr[0]->y, ent_arr[0]->x, ent_arr[0]->y+1, ent_arr[0]->x, 0);
				break;
			case(KEY_LEFT):		// x -
				entity_move(ent_arr[0]->y, ent_arr[0]->x, ent_arr[0]->y, ent_arr[0]->x-1, 0);
				break;
			default:
				break;

		};
		
//		printf("ent_arr x: %d, ent_arr y: %d / ", ent_arr[0]->y, ent_arr[0]->x);
	};

	endwin();
	free(wmap);
	return 0;	
};
