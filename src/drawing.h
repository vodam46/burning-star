#ifndef DRAWING_H
#define DRAWING_H

#include "config.h"

#ifdef USE_CURSES
#include "curses.h"

extern WINDOW* main_scr;

#define clearinp() flushinp()
#define getinp() wgetch(stdscr)

#else
#error "please use curses, there is not yet another rendering system"
#endif


#include "map.h"

extern vector scr_size, main_scr_size;
void drawing_init(void);
void drawing_end(void);
void resize_screen(void);
void final_message(char* msg);

void draw(
	world_map wmap,
	vector scr_size,
	vector main_scr_size,
	char* msg
);

void menu_draw(
	char* prompt,
	char** options,
	int num_options,
	int cur_option,
	int max_len
);

#endif
