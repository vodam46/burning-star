#include <stdlib.h>
#include <stdio.h>

#include "ai.h"
#include "vector.h"


vector basic_dir(vector start, vector end) {
	vector direction = vect_init(start.y - end.y, start.x - end.x);
	if (abs(direction.y) > abs(direction.x)) {
		if (direction.y > 0) {
			return vect_init(-1, 0);
		} else if (direction.y < 0) {
			return vect_init( 1, 0);
		}
	} else {
		if (direction.x > 0) {
			return vect_init( 0,-1);
		} else if (direction.x < 0) {
			return vect_init( 0, 1);
		}
	}
	return vect_init(0, 0);
}
