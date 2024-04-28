#include "config.h"
#ifdef USE_CURSES

#include "curses.h"

#include <sys/param.h>
#include <string.h>

#include "drawing.h"
#include "map.h"
#include "tile.h"

vector scr_size, main_scr_size;
WINDOW* main_scr;
void drawing_init(void) {
	// screen init
	initscr();
	start_color();
	keypad(stdscr, TRUE);
	getmaxyx(stdscr, scr_size.y, scr_size.x);
	main_scr_size = vect_init(scr_size.y-4, scr_size.x-2);

	// colors
	init_pair(0,COLOR_WHITE,COLOR_BLACK);
	init_pair(1,COLOR_GREEN,COLOR_BLACK);
	init_pair(2,COLOR_RED,COLOR_YELLOW);
	init_pair(3,COLOR_BLUE,COLOR_BLACK);
	init_pair(4,COLOR_BLUE,COLOR_BLACK);

	main_scr = newwin(main_scr_size.y,main_scr_size.x, 3,1);
}
void drawing_end(void) {
	endwin();
}
void resize_screen(void) {
	delwin(main_scr);
	getmaxyx(stdscr, scr_size.y, scr_size.x);
	main_scr_size = vect_init(scr_size.y-4, scr_size.x-2);
	main_scr = newwin(main_scr_size.y,main_scr_size.x, 3,1);
}
void final_message(char* msg) {
	clear();
	mvprintw((int)scr_size.y/2,(int)scr_size.x/2-(int)strlen(msg)/2,"%s",msg);
	refresh();
	getch();
}



int scrolling_map(int player_pos, int half_screen, int map_width) {
	if (player_pos < half_screen) {
		return 0;
	} else if (player_pos  >= map_width - half_screen) {
		return map_width - half_screen*2 - 1;
	} else {
		return player_pos - half_screen;
	}
}
void draw_main_scr(WINDOW* main_scr, world_map wmap, vector scr_size) {
	// rendering
	// y |	height
	// x -	width
	vector half = vect_init((int)scr_size.y/2, (int)scr_size.x/2);
	vector camera = vect_init(
		(wmap.size.y >= scr_size.y ? scrolling_map(wmap.ent_arr[0]->pos.y, half.y, wmap.size.y+1) : 0),
		(wmap.size.x >= scr_size.x ? scrolling_map(wmap.ent_arr[0]->pos.x, half.x, wmap.size.x) : 0)
	);
	for (int y = MAX(camera.y, 0); y < scr_size.y+camera.y && y < wmap.size.y; y++) {
		for (int x = MAX(camera.x, 0); x < scr_size.x+camera.x && x < wmap.size.x; x++) {
			// if entity - use entity char, else use tile char

			wmove(main_scr,y-camera.y,x-camera.x);
			if (wmap.map[y][x].visible || wmap.map[y][x].seen) {
				if (wmap.map[y][x].ent.type != none_entity && wmap.map[y][x].visible) {
					wattron(
						main_scr,
						COLOR_PAIR(wmap.map[y][x].visible ? ent_data[wmap.map[y][x].ent.type].entity_color : 4)
					);
					waddstr(main_scr, ent_data[wmap.map[y][x].ent.type].entity_char);
					wattroff(
						main_scr,
						COLOR_PAIR(wmap.map[y][x].visible ? ent_data[wmap.map[y][x].ent.type].entity_color : 4)
					);
				} else if (wmap.map[y][x].items.num_items > 0) {
					wattron(
						main_scr,
						COLOR_PAIR(wmap.map[y][x].visible ? item_data[wmap.map[y][x].items.items[0].type].item_color : 4)
				   );
					waddstr(main_scr, item_data[wmap.map[y][x].items.items[0].type].item_char);
					wattroff(
						main_scr,
						COLOR_PAIR(wmap.map[y][x].visible ? item_data[wmap.map[y][x].items.items[0].type].item_color : 4)
					);
				} else if (wmap.map[y][x].type != empty) {
					wattron(
						main_scr,
						COLOR_PAIR(wmap.map[y][x].visible ? tile_data[wmap.map[y][x].type].tile_color : 4)
				   );
					waddstr(main_scr, tile_data[wmap.map[y][x].type].tile_char);
					waddstr(main_scr, "\n");
					wattroff(
						main_scr,
						COLOR_PAIR(wmap.map[y][x].visible ? tile_data[wmap.map[y][x].type].tile_color : 4)
					);
				}
			}
		}
	}
	wmove(
		main_scr,
		wmap.ent_arr[0]->pos.y-camera.y,
		wmap.ent_arr[0]->pos.x-camera.x
	);
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

void draw(
	world_map wmap,
	vector scr_size,
	vector main_scr_size,
	char* msg
) {
	werase(stdscr);
	draw_border(stdscr,scr_size);
	mvwaddstr(stdscr, 1,2,msg);
	wrefresh(stdscr);
	draw_main_scr(main_scr, wmap, main_scr_size);
}

void menu_draw(
	char* prompt,
	char** options,
	int num_options,
	int cur_option,
	int max_len
) {
	vector offset = vect_init(
		(int)(scr_size.y/2-num_options/2),
		(int)(scr_size.x/2-max_len/2)
	);
	werase(stdscr);
	mvwprintw(stdscr,offset.y,offset.x, "%s", prompt);
	for (int i = 0; i < num_options; i++) {
		mvwprintw(stdscr, offset.y+i+1, offset.x, "[ ] %s", options[i]);
	}
	mvwaddch(stdscr,offset.y+cur_option+1,offset.x+1,'#');
	wmove(stdscr, offset.y+cur_option+1, offset.x+1);
	wrefresh(stdscr);
}
#else
#error "please use curses, there is not yet another rendering system"
#endif
