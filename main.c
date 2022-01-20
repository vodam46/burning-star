
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
		
	};

	endwin();
	free(wmap);
	return 0;	
};
