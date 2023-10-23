#include <stdlib.h>
#include <math.h>

#include "tile.h"
#include "entity.h"
#include "map.h"
#include "vector.h"

void rect_empty(tile** wmap, vector start, vector end, tile_type type) {
	for (int y = start.y; y < end.y; y++) {
		wmap[y][start.x].type = type;
		wmap[y][end.x].type = type;
	}
	for (int x = start.x; x < end.x; x++) {
		wmap[start.y][x].type = type;
		wmap[end.y][x].type = type;
	}
}
void rect_filled(tile** wmap, vector start, vector end, tile_type type) {
	for (int y = start.y; y <= end.y; y++)
		for (int x = start.x; x <= end.x; x++)
			wmap[y][x].type = type;
}

void circle_empty(tile** wmap, vector center, float radius, tile_type type) {
	for (int r = 0; r <= floor(radius * sqrt(0.5)); r++) {
		int d = floor(sqrt(radius*radius - r*r));
		wmap[center.x+d][center.x+r].type = type;
		wmap[center.x+d][center.x-r].type = type;
		wmap[center.x-d][center.x+r].type = type;
		wmap[center.x-d][center.x-r].type = type;
		wmap[center.x+r][center.x+d].type = type;
		wmap[center.x+r][center.x-d].type = type;
		wmap[center.x-r][center.x+d].type = type;
		wmap[center.x-r][center.x-d].type = type;
	}
}
void circle_filled(tile** wmap, vector center, float radius, tile_type type) {
		for (int y = 0; y <= radius; y++) {
			for (int x = 0; x <= sqrt(radius*radius - y*y); x++) {
			if (x*x + y*y <= radius*radius) {
				wmap[center.x + x][center.y + y].type = type;
				wmap[center.x + x][center.y - y].type = type;
				wmap[center.x - x][center.y + y].type = type;
				wmap[center.x - x][center.y - y].type = type;
			}
		}
	}
}

// world generation
// map_size.y is the height
// map_size.x is the width
tile** wmap_gen_tile(vector map_size, tile_type type) {

	tile** wmap = malloc(map_size.y * sizeof(tile));	// allocate the 2d array

	for (int y=0; y<map_size.y; y++) {
		wmap[y] = malloc(map_size.x * sizeof(tile));	// allocate each array of the 2d array
		for (int x=0; x<map_size.x; x++) {
			// set the variables for each tile
			wmap[y][x] = tile_init(
				vect_init(y, x),
				type,
				ent_init(vect_init(y,x), none, 0, 0, 0)
			);
		}
	}
	return wmap;
}

tile** wmap_gen_maze_base(vector map_size) {

	tile** wmap = wmap_gen_tile(map_size, wall);

	for (int y=0; y<(int)(map_size.y+1)/2; y++) {
		for (int x=0; x<(int)(map_size.x+1)/2; x++) {
			wmap[y*2][x*2].type = empty;
		}
	}
	return wmap;
}

tile** wmap_gen_bin_tree_maze(vector map_size) {

	tile** wmap = wmap_gen_maze_base(map_size);

	for (int y=0; y<(int)(map_size.y+1)/2; y++) {
		for (int x=0; x<(int)(map_size.x+1)/2; x++) {
			if (y > 0 && x > 0) {
				if (rand() % 2) {
					wmap[y*2-1][x*2].type = empty;
				}
				else {
					wmap[y*2][x*2-1].type = empty;
				}
			} else if (y > 0) {
				wmap[y*2-1][x*2].type = empty;
			} else if (x > 0) {
				wmap[y*2][x*2-1].type = empty;
			}
		}
	}
	return wmap;
}

tile** wmap_gen_directional_cave(vector map_size) {
	int length = map_size.y - 4;
	int roughness = 100;
	int windyness = 60;
	int start_width = 10;
	vector start = vect_init(1, (int)map_size.x / 2);
	tile** wmap = wmap_gen_tile(map_size, wall);

	int y = start.y, x = start.x, width = start_width;
	rect_filled(wmap, vect_init(y, x-(int)width/2), vect_init(y, x+(int)width/2), empty);

	while (y - start.y <= length) {
		y++;
		if (rand()%100 <= roughness) {
			width += (rand()%2+1) * (rand()%2 ? 1 : -1);
			if (width < 3)
				width = 3;
			else if (width > map_size.x)
				width = map_size.x;
		}
		if (rand()%100 <= windyness) {
			x += (rand()%2+1) * (rand()%2 ? 1 : -1);
			if (x < 0)
				x = 0;
			else if (x > map_size.x-3)
				x = map_size.x-3;
		}
		rect_filled(wmap, vect_init(y, x-(int)width/2), vect_init(y, x+(int)width/2), empty);
	}


	return wmap;
}
