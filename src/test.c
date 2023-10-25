#include <stdio.h>
#include <stdlib.h>

#include "vector.h"
#include "ai.h"
#include "entity.h"
#include "tile.h"
#include "map.h"
#include "action.h"

#define assert(test) tests_run++; if(!(test)) { tests_failed++; printf("\033[0;31mX\033[0m %s:%d %s\n",__FILE__,__LINE__,#test); };

int main() {
	int tests_run = 0;
	int tests_failed = 0;

	// vectors
	assert(vect_comp(vect_init(0,0),(vector){0,0}))
	assert(vect_comp(vect_add(vect_init(1,1),vect_init(1,1)),vect_init(2,2)))

	// ai
	assert(vect_comp(basic_dir(vect_init(0,0),vect_init(1,0)),vect_init(1,0)))
	assert(vect_comp(basic_dir(vect_init(0,0),vect_init(1,1)),vect_init(0,1)))
	assert(vect_comp(basic_dir(vect_init(0,0),vect_init(0,1)),vect_init(0,1)))

	// entity
	assert(ent_comp(ent_init(vect_init(0,0),player,1,1,1),(entity){player,(vector){0,0},1,1,1}));

	// entity creation
	world_map wmap;
	entities_init();
	wmap = wmap_gen_tile((vector){1,1}, empty);
	assert(wmap.ent_num==1);
	assert(ent_comp(wmap.map[0][0].ent,ent_init(vect_init(0,0),player,5,20,20)));

	// tile
	tiles_init();
	assert(tile_data[1].tile.type == wall);
	assert(tile_comp(
				tile_init(vect_init(0,0),empty,ent_init(vect_init(0,0),player,1,1,1)),
				(tile){(vector){0,0},empty,(entity){player,(vector){0,0},1,1,1}}));

	// map
	wmap = wmap_gen_tile((vector){10,10}, wall);
	int num_not_wall = 0;
	for (int y = 0; y < 10; y++)
		for (int x = 0; x < 10; x++)
			if (wmap.map[y][x].type != wall)
				num_not_wall += 1;
	assert(num_not_wall==0);

	if (tests_failed == 0)
		printf("✅ ");
	else
		printf("\033[0;31mX\033[0m ");
	printf("tests run: %d\ntests passed: %d\n",tests_run, tests_run-tests_failed);
}
