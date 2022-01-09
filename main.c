
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

	printf("works\n");

	// map init
	struct tile** wmap = wmap_gen(height, width);

	while (ch != 10) {
		draw_wmap(wmap, height, width);
		ch = getch();
		
	};

	endwin();
	return 0;	
};
