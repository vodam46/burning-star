
// header guards
#ifndef ENTITY_H
#define ENTITY_H

// custom libraries
#include "entity_type.h"
#include "vector.h"

// entity struct
typedef struct {
	// position
	vector pos;

	// type
	entity_type type;
} entity ;

entity ent_init(vector _pos, entity_type _type);

#endif
