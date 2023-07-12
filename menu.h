#ifndef MENU_H
#define MENU_H

#include <ncurses.h>

#include "vector.h"

int menu(WINDOW* stdscr, vector scr_size, char* prompt,  char** options, int num_options);

#endif
