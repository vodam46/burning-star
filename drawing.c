// system libraries
#include <ncurses.h>

// custom libraries
#include "drawing.h"
#include "tile.h"

void draw_wmap(struct tile** wmap, int height, int width) {
	// rendering
	// y |	height
	// x -	width
	for (int y=0; y<height; y++) {
		for (int x=0; x<width; x++) {
			// if entity - use entity char, else use tile char
			if (wmap[y][x].ent.type == player) {
				mvaddch(y, x, entity_char[wmap[y][x].ent.type]);
			}
			else {
				mvaddch(y, x, tile_char[wmap[y][x].type]);
			}
		}
	}
	// update the screen output
	refresh();
}



