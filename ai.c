
// global libraries
#include <stdlib.h>
#include <stdio.h>

// custom libraries
#include "ai.h"
#include "vector.h"
#include "math.h"


vector random_movement() {
	int direction = rand() % 4;

	vector vect_dir;

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
	return vect_dir;
}

vector basic_dir(vector start, vector end) {
	vector direction = vect_init(start.y - end.y, start.x - end.x);
	if (abs(direction.y) > abs(direction.x)) {
		if (direction.y > 0) {
			return (vector) {-1, 0 };
		} else if (direction.y < 0) {
			return (vector) { 1, 0 };
		}
	} else {
		if (direction.x > 0) {
			return (vector) { 0,-1 };
		} else if (direction.x < 0) {
			return (vector) { 0, 1 };
		}
	}
	return (vector) { 0, 0 };
}
