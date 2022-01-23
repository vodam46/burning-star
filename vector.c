
// custom libraries
#include "vector.h"

struct vector vect_init(int y, int x) {
	struct vector ret_vect;
	ret_vect.y = y;
	ret_vect.x = x;
	return ret_vect;
};

// adding 2 vectors together
struct vector vect_add(struct vector left, struct vector right) {
	struct vector ret_vect;
	ret_vect.y = left.y + right.y;
	ret_vect.x = left.x + right.x;
	return ret_vect;
};

// function to check if position is within boundaries
int in_bounds(struct vector pos, struct vector min, struct vector max) {
	return pos.y >= min.y && pos.y < max.y && pos.x >= min.x && pos.x < max.x;
};
