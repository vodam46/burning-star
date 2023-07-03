
// header guards
#ifndef DRAWING_H
#define DRAWING_H

// global libraries
#include <ncurses.h>

// custom libraries
#include "tile.h"

void draw_wmap(tile** wmap, vector scr_size);

#endif
