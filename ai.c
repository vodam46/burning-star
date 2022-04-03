
// global libraries
#include <stdlib.h>
#include <stdio.h>

// custom libraries
#include "ai.h"
#include "vector.h"


struct vector random_movement() {
	int direction = rand() % 4;

	struct vector vect_dir;

	switch(direction) {		
		case(0):
			vect_dir = vect_init(-1, 0);
			break;
		case(1):
			vect_dir = vect_init(0, +1);
			break;
		case(2):
			vect_dir = vect_init(+1, 0);
			break;
		case(3):
			vect_dir =  vect_init(0, -1);
			break;
		default:
			vect_dir = vect_init(0, 0);
			break;

	}
#ifdef DEBUG
	printf("random movement y: %d, x: %d / ", vect_dir.y, vect_dir.x);
#endif
	return vect_dir;
}

