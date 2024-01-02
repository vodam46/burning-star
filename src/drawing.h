#ifndef DRAWING_H
#define DRAWING_H

#if defined(__CYGWIN__)
#include <ncurses/ncurses.h>
#elif defined(unix)
#include <ncurses.h>
#else
#error "Unknown platform"
#endif

#include "map.h"
#include "tile.h"

void draw(
	WINDOW* stdscr,
	WINDOW* main_scr,
	world_map wmap,
	vector scr_size,
	vector main_scr_size,
	char* msg
);

void menu_draw(
	WINDOW* stdscr,
	char* prompt,
	char** options,
	int num_options,
	int cur_option
);

#endif
