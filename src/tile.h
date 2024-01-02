#ifndef TILE_H
#define TILE_H

#include "entity.h"
#include "item.h"

// type of tiles
typedef enum {
	empty,
	wall,
	last_tile,
} tile_type;

// array for rendering tiles
extern const char* tile_name[];
typedef struct {
	vector pos;
	tile_type type;
	entity ent;
	inventory items;
} tile;
typedef struct {
	tile tile;
	char* tile_char;
	int tile_color;
} til_data;
extern til_data tile_data[last_tile];

void tiles_init(void);

tile tile_init(vector pos, tile_type type, entity ent, inventory items);

int tile_comp(tile left, tile right);

#endif
