#include <stdio.h>
#include <stdlib.h>

#include "vector.h"
#include "ai.h"
#include "entity.h"
#include "tile.h"

#define assert(test) tests_run++; if(!(test)) { tests_failed++; printf("%s\n",#test); };

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
	assert(ent_comp(
				ent_init(vect_init(0,0),player,1,1),
				(entity){player,(vector){0,0},1,1,1}));

	// tile
	assert(tile_comp(
				tile_init(vect_init(0,0),empty,ent_init(vect_init(0,0),player,1,1)),
				(tile){(vector){0,0},empty,(entity){player,(vector){0,0},1,1,1}}));

	printf("tests run: %d\ntests passed: %d\n",tests_run, tests_run-tests_failed);
}
