// system libraries
#include <ncurses.h>

// custom libraries
#include "drawing.h"
#include "tile.h"

void draw_wmap(tile** wmap, vector scr_size) {
	clear();
	// rendering
	// y |	height
	// x -	width
	for (int y = 0; y < scr_size.y; y++) {
		for (int x = 0; x < scr_size.x; x++) {
			// if entity - use entity char, else use tile char
			if (wmap[y][x].ent.type != none) {
				mvaddch(y, x, entity_char[wmap[y][x].ent.type]);
			}
			else if (wmap[y][x].type != empty) {
				mvaddch(y, x, tile_char[wmap[y][x].type]);
			}
		}
	}
	// update the screen output
	refresh();
}

