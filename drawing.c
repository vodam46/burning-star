
#include <ncurses.h>

#include "drawing.h"
#include "tile.h"

void draw_wmap(struct tile** wmap, int height, int width) {
	// rendering
	// screem output y| x-
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
	refresh();
}



