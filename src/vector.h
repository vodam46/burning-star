#ifndef VECTOR_H
#define VECTOR_H

// vector struct
// y x position
typedef struct {
	int y;
	int x;
} vector ;

// vector init function
vector vect_init(int y, int x);

vector vect_add(vector left, vector right);

int vect_comp(vector left, vector right);

int in_bounds(vector pos, vector min, vector max);

#endif
