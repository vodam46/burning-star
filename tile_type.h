
// header guards
#ifndef TILE_TYPE_H
#define TILE_TYPE_H

// type of tiles
typedef enum {
	empty,
	wall,
} tile_type ;

// array for rendering tiles
extern const char* tile_char[];

extern const int tile_color[];

#endif
