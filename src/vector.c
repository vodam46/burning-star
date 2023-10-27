#include <math.h>

#include "vector.h"

vector vect_init(int y, int x) {
	vector ret_vect;
	ret_vect.y = y;
	ret_vect.x = x;
	return ret_vect;
}

vector vect_add(vector left, vector right) {
	vector ret_vect;
	ret_vect.y = left.y + right.y;
	ret_vect.x = left.x + right.x;
	return ret_vect;
}
vector vect_sub(vector left, vector right) {
	vector ret_vect;
	ret_vect.y = left.y - right.y;
	ret_vect.x = left.x - right.x;
	return ret_vect;
}

int vect_comp(vector left, vector right) {
	return left.y == right.y && left.x == right.x;
}

// function to check if position is within boundaries
int in_bounds(vector pos, vector min, vector max) {
	return pos.y >= min.y && pos.y < max.y && pos.x >= min.x && pos.x < max.x;
}

int vect_distance_squared(vector left, vector right) {
	return pow(left.y-right.y, 2) + pow(left.x-right.x, 2);
}
