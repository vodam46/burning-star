#if defined(__CYGWIN__)
#include <ncurses/ncurses.h>
#elif defined(unix)
#include <ncurses.h>
#else
#error "Unknown platform"
#endif

#include "drawing.h"
#include "map.h"
#include "tile.h"

int scrolling_map(int player_pos, int half_screen, int map_width) {
	if (player_pos < half_screen) {
		return 0;
	} else if (player_pos  >= map_width - half_screen) {
		return map_width - half_screen*2;
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
		scrolling_map(wmap.ent_arr[0]->pos.y, half.y, wmap.size.y),
		scrolling_map(wmap.ent_arr[0]->pos.x, half.x, wmap.size.x)
	);
	for (int y = camera.y; y < scr_size.y+camera.y; y++) {
		for (int x = camera.x; x < scr_size.x+camera.x; x++) {
			if (y < wmap.size.y && x < wmap.size.x) {
				// if entity - use entity char, else use tile char

				wmove(main_scr,y-camera.y,x-camera.x);
				if (wmap.map[y][x].ent.type != none_entity) {
					wattron(
						main_scr,
						COLOR_PAIR(ent_data[wmap.map[y][x].ent.type].entity_color)
					);
					waddstr(
						main_scr, ent_data[wmap.map[y][x].ent.type].entity_char
					);
					wattroff(
						main_scr,
						COLOR_PAIR(ent_data[wmap.map[y][x].ent.type].entity_color)
					);
				} else if (wmap.map[y][x].items.num_items > 0) {
					wattron(
						main_scr,
						COLOR_PAIR(item_data[wmap.map[y][x].items.items[0].type].item_color)
					);
					waddstr(main_scr, item_data[wmap.map[y][x].items.items[0].type].item_char);
					wattroff(
						main_scr,
						COLOR_PAIR(item_data[wmap.map[y][x].items.items[0].type].item_color)
					);
				} else if (wmap.map[y][x].type != empty) {
					wattron(
						main_scr,
						COLOR_PAIR(tile_data[wmap.map[y][x].type].tile_color)
					);
					waddstr(main_scr, tile_data[wmap.map[y][x].type].tile_char);
					waddstr(main_scr, "\n");
					wattroff(
						main_scr,
						COLOR_PAIR(tile_data[wmap.map[y][x].type].tile_color)
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
	WINDOW* stdscr,
	WINDOW* main_scr,
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
	WINDOW* stdscr,
	char* prompt,
	char** options,
	int num_options,
	int cur_option
) {
	werase(stdscr);
	wprintw(stdscr, "%s", prompt);
	for (int i = 0; i < num_options; i++) {
		mvwprintw(stdscr, i+1, 0, "[ ] %s", options[i]);
	}
	mvwaddch(stdscr,cur_option+1,1,'#');
	wmove(stdscr, cur_option+1, 1);
	wrefresh(stdscr);
}
