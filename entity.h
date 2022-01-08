#ifndef ENTITY_H
#define ENTITY_H

#include "entity_type.h"

struct entity {
	// position
	int x;
	int y;

	// type
	// TODO: set parameters depending on the type (hp...)
	enum entity_type type;
};

struct entity ent_init(int _x, int _y, enum entity_type _type);


#endif
