
// header guards
#ifndef ENTITY_H
#define ENTITY_H

// custom libraries
#include "entity_type.h"

// entity struct
struct entity {
	// position
	int x;
	int y;

	// type
	enum entity_type type;
};

struct entity ent_init(int _x, int _y, enum entity_type _type);


#endif
