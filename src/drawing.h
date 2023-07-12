
// header guards
#ifndef DRAWING_H
#define DRAWING_H

// global libraries
#include <ncurses.h>

// custom libraries
#include "tile.h"

void draw(WINDOW* stdscr, WINDOW* main_scr, tile** wmap, vector scr_size, vector main_scr_size, char* msg);

void menu_draw(WINDOW* stdscr, char* prompt, char** options, int num_options, int cur_option);

#endif
