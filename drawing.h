#ifndef DRAWING_H
#define DRAWING_H

#include <ncurses.h>

#include "tile.h"

void draw_wmap(struct tile** wmap, int height, int width);

#endif
