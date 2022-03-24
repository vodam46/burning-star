// system libraries
#include <ncurses.h>

// custom libraries
#include "drawing.h"
#include "tile.h"

void draw_wmap(struct tile** wmap, int height, int width) {
	clear();
	// rendering
	// y |	height
	// x -	width
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
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

