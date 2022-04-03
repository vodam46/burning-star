
// header guards
#ifndef TILE_TYPE_H
#define TILE_TYPE_H

// type of tiles
enum tile_type {
	empty,
	wall,
};

// array for rendering tiles
static const char tile_char[] = {
	' ',
	'#',
};

#endif
