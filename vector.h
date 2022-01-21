
// header guards
#ifndef VECTOR_H
#define VECTOR_H

// vector struct
// y x position
struct vector {
	int y;
	int x;
};

// vector init function
struct vector vect_init(int y, int x);

struct vector vect_add(struct vector left, struct vector right);
#endif
