
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#include "tile.h"
#include "entity.h"
#include "map.h"
#include "entity_type.h"
#include "drawing.h"


int main() {
	
	int ch = 0;

	// global variables
	int width;	// x
	int height;	// y
	
	// screen init
	initscr();
	keypad(stdscr, TRUE);
	getmaxyx(stdscr, height, width);

	// map init
	struct tile** wmap = wmap_gen(height, width);

	wmap[0][0].ent.type = player;		// this gives seg fault error, need to find a way to fix it
	// wmap[0][0] = tile_init(0, 0, empty, ent_init(0, 0, player));	// this gives seg fault too


	while (ch != 10) {
		draw_wmap(wmap, height, width);
		ch = getch();
		
	};

	endwin();
	free(wmap);
	return 0;	
};
