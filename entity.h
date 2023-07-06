
// header guards
#ifndef ENTITY_H
#define ENTITY_H

// custom libraries
#include "entity_type.h"
#include "vector.h"

// entity struct
typedef struct {
	entity_type type;
	vector pos;
	int strength, maxhealth, health;
} entity ;

entity ent_init(vector _pos, entity_type _type, int _strength, int _health);

int ent_comp(entity left, entity right);

#endif
