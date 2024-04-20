#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#ifdef MEASURE_TIME
#include <time.h>
#endif

#include "item.h"
#include "tile.h"
#include "entity.h"
#include "map.h"
#include "vector.h"
#include "noise.h"

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


void save_map(world_map wmap, char* file_name) {
#ifdef MEASURE_TIME
	clock_t begin = clock();
#endif

	FILE* file = fopen(file_name, "w");
	file = freopen(file_name, "ab", file);

	fwrite(&SEED, sizeof(int), 1, file);
	fwrite(hash, sizeof(int), 256, file);
	fwrite(&wmap.size, sizeof(vector), 1, file);
	fwrite(&wmap.ent_num, sizeof(int), 1, file);
	fwrite(&wmap.turn_count, sizeof(int), 1, file);
	fwrite(&wmap.ent_killed, sizeof(int), 1, file);
	fwrite(&wmap.enemy_spawn_num, sizeof(int), 1, file);

	for (int y = 0; y < wmap.size.y; y++) {
		for (int x = 0; x < wmap.size.x; x++) {
			fwrite(&wmap.map[y][x].type, sizeof(vector), 1, file);
			fwrite(&wmap.map[y][x].items.num_items, sizeof(int), 1, file);
			for (int i = 0; i < wmap.map[y][x].items.num_items; i++) {
				fwrite(&wmap.map[y][x].items.items[i].type, sizeof(int), 1, file);
			}

			fwrite(&wmap.map[y][x].ent.type, sizeof(entity_type), 1, file);
			if (wmap.map[y][x].ent.type != none_entity) {
				fwrite(&wmap.map[y][x].ent.health, sizeof(int), 1, file);
				fwrite(&wmap.map[y][x].ent.strength, sizeof(int), 1, file);
				fwrite(&wmap.map[y][x].ent.inventory.num_items, sizeof(int), 1, file);
				for (int i = 0; i < wmap.map[y][x].ent.inventory.num_items; i++) {
					fwrite(&wmap.map[y][x].ent.inventory.items[i].type, sizeof(int), 1, file);
				}
			}
		}
	}

	for (int i = 0; i < wmap.ent_num; i++) {
		fwrite(&wmap.ent_arr[i]->pos, sizeof(vector), 1, file);
	}

	fclose(file);

#ifdef MEASURE_TIME
	clock_t end = clock();
	FILE* time = fopen("time", "a");
	fprintf(time, "save: %f\n", (double)(end-begin)/CLOCKS_PER_SEC);
	fclose(time);
#endif
}

world_map load_map(char* file_name) {
#ifdef MEASURE_TIME
	clock_t begin = clock();
#endif

	world_map wmap;
	FILE* file = fopen(file_name, "rb");
	fread(&SEED, sizeof(int), 1, file);
	fread(hash, sizeof(int), 256, file);
	fread(&wmap.size, sizeof(vector), 1, file);
	fread(&wmap.ent_num, sizeof(int), 1, file);
	fread(&wmap.turn_count, sizeof(int), 1, file);
	fread(&wmap.ent_killed, sizeof(int), 1, file);
	fread(&wmap.enemy_spawn_num, sizeof(int), 1, file);

	wmap.map = malloc(wmap.size.y * sizeof(tile*));
	for (int y = 0; y < wmap.size.y; y++) {
		wmap.map[y] = malloc(wmap.size.x * sizeof(tile));
		for (int x = 0; x < wmap.size.x; x++) {

			fread(&wmap.map[y][x].type, sizeof(vector), 1, file);
			wmap.map[y][x].pos = vect_init(y, x);
			int item_type;
			int num_items;
			fread(&num_items, sizeof(int), 1, file);
			for (int i = 0; i < num_items; i++) {
				fread(&item_type, sizeof(int), 1, file);
				wmap.map[y][x].items = add_to_inventory(
						wmap.map[y][x].items,
						item_data[item_type].item
						);
			}

			fread(&wmap.map[y][x].ent.type, sizeof(entity_type), 1, file);
			if (wmap.map[y][x].ent.type != none_entity) {
				fread(&wmap.map[y][x].ent.health, sizeof(int), 1, file);
				fread(&wmap.map[y][x].ent.strength, sizeof(int), 1, file);

				fread(&num_items, sizeof(int), 1, file);
				for (int i = 0; i < num_items; i++) {
					fread(&item_type, sizeof(int), 1, file);
					wmap.map[y][x].ent.inventory = add_to_inventory(
						wmap.map[y][x].ent.inventory,
						item_data[item_type].item
					);
				}
			} else {
				wmap.map[y][x].ent.health = 0;
				wmap.map[y][x].ent.strength = 0;
				wmap.map[y][x].ent.inventory.num_items = 0;
				wmap.map[y][x].ent.maxhealth = 0;
			}
			wmap.map[y][x].ent.pos = vect_init(y, x);

		}
	}

	wmap.ent_arr = malloc(wmap.size.y * wmap.size.x * sizeof(entity));
	vector vec;
	for (int i = 0; i < wmap.ent_num; i++) {
		fread(&vec, sizeof(vector), 1, file);
		wmap.ent_arr[i] = &wmap.map[vec.y][vec.x].ent;
	}

	fclose(file);

#ifdef MEASURE_TIME
	clock_t end = clock();
	FILE* time = fopen("time", "a");
	fprintf(time, "load: %f\n", (double)(end-begin)/CLOCKS_PER_SEC);
#endif

	return wmap;
}

int VIEW_RADIUS = 20;
void do_fov_line(world_map wmap, float x, float y) {
	int i;
	float ox,oy;
	ox = (float)wmap.ent_arr[0]->pos.x+0.5f;
	oy = (float)wmap.ent_arr[0]->pos.y+0.5f;
	for(i=0;i<VIEW_RADIUS;i++) {
		if (!in_bounds(vect_init((int)oy, (int)ox), vect_init(0,0), wmap.size))
			return;
		wmap.map[(int)oy][(int)ox].visible = 1; //Set the tile to visible.
		if (!tile_data[wmap.map[(int)oy][(int)ox].type].see_through) {
			return;
		}
		ox+=x;
		oy+=y;
	}
}
void calculate_fov(world_map wmap) {
	float dir_x, dir_y;
	int i;
	for (int x = 0; x < wmap.size.x; x++) {
		for (int y = 0; y < wmap.size.y; y++) {
			if (wmap.map[y][x].visible)
				wmap.map[y][x].seen = 1;
			wmap.map[y][x].visible = 0;
		}
	}
	for(i=0;i<360;i++) {
		dir_x=cos((float)i*0.01745f);
		dir_y=sin((float)i*0.01745f);
		do_fov_line(wmap, dir_x, dir_y);
	}
}

// world generation
// map_size.y is the height
// map_size.x is the width
world_map wmap_gen_tile(vector map_size, tile_type type) {

	world_map wmap;
	wmap.turn_count = 0;
	wmap.ent_killed = 0;
	wmap.enemy_spawn_num = 10;
	wmap.map = malloc(map_size.y * sizeof(tile));
	wmap.size = map_size;

	for (int y=0; y<map_size.y; y++) {
		wmap.map[y] = malloc(map_size.x * sizeof(tile));
		for (int x=0; x<map_size.x; x++) {
			wmap.map[y][x] = tile_init(
				vect_init(y, x),
				type,
				ent_init(vect_init(y,x), none_entity, 0, 0, 0, (inventory){0, 0}),
				(inventory){0}
			);
			wmap.map[y][x].visible = 0;
			wmap.map[y][x].seen = 0;
		}
	}
	wmap.ent_arr = malloc(wmap.size.y * wmap.size.x * sizeof(entity));
	vector middle = vect_init((int)(wmap.size.y/2), (int)(wmap.size.x/2));
	vector player_pos = vect_init(
		middle.y+(middle.y%2==0?0:1),
		middle.x+(middle.x%2==0?0:1)
	);
	wmap.map[player_pos.y][player_pos.x].ent = ent_data[player].ent;
	wmap.map[player_pos.y][player_pos.x].ent.pos = player_pos;
	wmap.ent_arr[0] = &wmap.map[player_pos.y][player_pos.x].ent;
	wmap.ent_num = 1;

	return wmap;
}

world_map wmap_gen_maze_base(vector map_size) {

	world_map wmap = wmap_gen_tile(map_size, wall);

	for (int y=0; y<(int)(map_size.y+1)/2; y++) {
		for (int x=0; x<(int)(map_size.x+1)/2; x++) {
			wmap.map[y*2][x*2].type = empty;
		}
	}
	return wmap;
}

world_map wmap_gen_bin_tree_maze(vector map_size) {

	world_map wmap = wmap_gen_maze_base(map_size);

	for (int y=0; y<(int)(map_size.y+1)/2; y++) {
		for (int x=0; x<(int)(map_size.x+1)/2; x++) {
			if (y > 0 && x > 0) {
				if (rand() % 2) {
					wmap.map[y*2-1][x*2].type = empty;
				}
				else {
					wmap.map[y*2][x*2-1].type = empty;
				}
			} else if (y > 0) {
				wmap.map[y*2-1][x*2].type = empty;
			} else if (x > 0) {
				wmap.map[y*2][x*2-1].type = empty;
			}
		}
	}
	return wmap;
}

world_map wmap_gen_directional_cave(vector map_size) {
	int length = map_size.y - 4;
	int roughness = 100;
	int windyness = 60;
	int start_width = 10;
	vector start = vect_init(1, (int)map_size.x / 2);
	world_map wmap = wmap_gen_tile(map_size, wall);

	int y = start.y, x = start.x, width = start_width;
	rect_filled(
		wmap.map,
		vect_init(y, x-(int)width/2),
		vect_init(y, x+(int)width/2),
		empty
	);

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
		rect_filled(
			wmap.map,
			vect_init(y, x-(int)width/2),
			vect_init(y, x+(int)width/2),
			empty
		);
		if (y - start.y == (int)length/2) {
			vector middle = vect_init((int)(wmap.size.y/2), (int)(wmap.size.x/2));
			vector player_pos = vect_init(
				middle.y+(middle.y%2==0?0:1),
				middle.x+(middle.x%2==0?0:1)
			);
			entity player = wmap.map[player_pos.y][player_pos.x].ent;
			wmap.map[player_pos.y][player_pos.x].ent = ent_data[none_entity].ent;
			player.pos = vect_init(y, x);
			wmap.map[player.pos.y][player.pos.x].ent = player;
			wmap.ent_arr[0] = &wmap.map[player.pos.y][player.pos.x].ent;
		}
	}


	return wmap;
}

world_map wmap_gen_noise(vector map_size) {
	world_map wmap = wmap_gen_tile(map_size, empty);

	for (int y = 0; y < map_size.y; y++) {
		for (int x = 0; x < map_size.x; x++) {
			int type = (int)(noise2d(x, y, 0.125, 2)*4);

			if (type == 0) {
				wmap.map[y][x].type = water;
			} else if (type == 1) {
				wmap.map[y][x].type = empty;
			} else  {
				wmap.map[y][x].type = wall;
			}
		}
	}

	for (int y = wmap.ent_arr[0]->pos.y - 5; y < wmap.ent_arr[0]->pos.y + 5; y++) {
		for (int x = wmap.ent_arr[0]->pos.x - 5; x < wmap.ent_arr[0]->pos.x + 5; x++) {
			wmap.map[y][x].type = empty;
		}
	}

	return wmap;
}
