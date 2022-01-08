
#include <ncurses.h>
#include <stdio.h>

#include "tile.h"
#include "entity.h"
#include "map.h"

// global variables
int width;	// x
int height;	// y

// rendering
// for row in map
// for tile in row


int main() {
	
	initscr();
	getmaxyx(stdscr, height, width);
	
	struct tile** wmap = wmap_gen(20, 20);

	// rendering
	
	getch();
	
	endwin();
	
};
