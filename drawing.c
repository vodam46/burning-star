// system libraries
#include <ncurses.h>

// custom libraries
#include "drawing.h"
#include "tile.h"

void draw_main_scr(WINDOW* main_scr, tile** wmap, vector scr_size) {
	// rendering
	// y |	height
	// x -	width
	wclear(main_scr);
	for (int y = 0; y < scr_size.y; y++) {
		for (int x = 0; x < scr_size.x; x++) {
			// if entity - use entity char, else use tile char
			if (wmap[y][x].ent.type != none) {
				mvwaddch(main_scr, y, x, entity_char[wmap[y][x].ent.type]);
			}
			else if (wmap[y][x].type != empty) {
				mvwaddch(main_scr, y, x, tile_char[wmap[y][x].type]);
			}
		}
	}
	wrefresh(main_scr);
}

void draw_border(WINDOW* stdscr, vector scr_size) {
	for (int y = 0; y < scr_size.y; y++) {
		mvwaddch(stdscr, y, 0, '#');
		mvwaddch(stdscr, y, scr_size.x-1, '#');
	}
	for (int x = 0; x < scr_size.x; x++) {
		mvwaddch(stdscr, 0, x, '#');
		mvwaddch(stdscr, 2, x, '#');
		mvwaddch(stdscr, scr_size.y-1, x, '#');
	}
}

void draw(WINDOW* stdscr, WINDOW* main_scr, tile** wmap, vector scr_size, vector main_scr_size, char* msg) {
	clear();
	mvwaddstr(stdscr, 1,2,msg);
	draw_border(stdscr,scr_size);
	wrefresh(stdscr);
	draw_main_scr(main_scr, wmap, main_scr_size);
}
