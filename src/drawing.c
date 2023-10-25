#include <ncurses.h>

#include "drawing.h"
#include "map.h"
#include "tile.h"

int scrolling_map(int p, int hs, int m) {
	if (p < hs)
		return 0;
	else if (p  >= m - hs)
		return m - hs;
	else
		return p - hs;
}

void draw_main_scr(WINDOW* main_scr, world_map wmap, vector scr_size) {
	// rendering
	// y |	height
	// x -	width
	wclear(main_scr);
	vector half = vect_init((int)scr_size.y/2, (int)scr_size.x/2);
	vector camera = vect_init(
		scrolling_map(wmap.ent_arr[0]->pos.y, half.y, wmap.size.y),
		scrolling_map(wmap.ent_arr[0]->pos.x, half.x, wmap.size.x)
	);
	for (int y = 0; y < scr_size.y; y++) {
		for (int x = 0; x < scr_size.x; x++) {
			// if entity - use entity char, else use tile char

			wmove(main_scr,y,x);
			if (wmap.map[y+camera.y][x+camera.x].ent.type != none) {
				wattron(main_scr, COLOR_PAIR(wmap.map[y+camera.y][x+camera.x].ent.type));
				waddstr(main_scr, ent_data[wmap.map[y+camera.y][x+camera.x].ent.type].entity_char);
				wattroff(main_scr, COLOR_PAIR(wmap.map[y+camera.y][x+camera.x].ent.type));
			} else if (wmap.map[y+camera.y][x+camera.x].type != empty) {
				wattron(main_scr, COLOR_PAIR(tile_data[wmap.map[y+camera.y][x+camera.x].ent.type].tile_color));
				waddstr(main_scr, tile_data[wmap.map[y+camera.y][x+camera.x].type].tile_char);
				wattroff(main_scr, COLOR_PAIR(tile_data[wmap.map[y+camera.y][x+camera.x].ent.type].tile_color));
			}
		}
	}
	wrefresh(main_scr);
}

void draw_border(WINDOW* stdscr, vector scr_size) {
	for (int y = 0; y < scr_size.y; y++) {
		mvwaddstr(stdscr, y, 0, "█");
		mvwaddstr(stdscr, y, scr_size.x-1, "█");
	}
	for (int x = 0; x < scr_size.x; x++) {
		mvwaddstr(stdscr, 0, x, "█");
		mvwaddstr(stdscr, 2, x, "█");
		mvwaddstr(stdscr, scr_size.y-1, x, "█");
	}
}

void draw(WINDOW* stdscr, WINDOW* main_scr, world_map wmap, vector scr_size, vector main_scr_size, char* msg) {
	clear();
	draw_border(stdscr,scr_size);
	mvwaddstr(stdscr, 1,2,msg);
	wrefresh(stdscr);
	draw_main_scr(main_scr, wmap, main_scr_size);
}

void menu_draw(WINDOW* stdscr, char* prompt, char** options, int num_options, int cur_option) {
	wclear(stdscr);
	wprintw(stdscr, "%s", prompt);
	for (int i = 0; i < num_options; i++) {
		mvwprintw(stdscr, i+1, 0, "[ ] %s", options[i]);
	}
	mvwaddch(stdscr,cur_option+1,1,'#');
	wmove(stdscr, cur_option+1, 1);
	wrefresh(stdscr);
}
