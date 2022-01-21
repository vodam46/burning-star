
// custom libraries
#include "vector.h"

struct vector vect_init(int y, int x) {
	struct vector ret_vect;
	ret_vect.y = y;
	ret_vect.x = x;
	return ret_vect;
};

struct vector vect_add(struct vector left, struct vector right) {
	struct vector ret_vect;
	ret_vect.y = left.y + right.y;
	ret_vect.x = left.x + right.x;
	return ret_vect;
};
