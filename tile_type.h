
// header guards
#ifndef TILE_TYPE_H
#define TILE_TYPE_H

// type of tiles
typedef enum {
	empty,
	wall,
} tile_type ;

// array for rendering tiles
static const char tile_char[] = {
	' ',
	'#',
};

#endif
