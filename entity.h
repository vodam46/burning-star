
// header guards
#ifndef ENTITY_H
#define ENTITY_H

// custom libraries
#include "entity_type.h"
#include "vector.h"

// entity struct
struct entity {
	// position
	struct vector pos;

	// type
	enum entity_type type;
};

struct entity ent_init(struct vector _pos, enum entity_type _type);

#endif
