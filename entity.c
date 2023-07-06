
// global libraries
#include <stdio.h>

// custom libraries
#include "entity.h"
#include "entity_type.h"
#include "vector.h"

// entity init function
entity ent_init(vector _pos, entity_type _type, int _strength, int _health) {
	entity ret_ent;
	ret_ent.pos = _pos;
	ret_ent.type = _type;
	ret_ent.strength = _strength;
	ret_ent.maxhealth = _health;
	ret_ent.health = _health;
	return ret_ent;
}

int ent_comp(entity left, entity right) {
	return (vect_comp(left.pos,right.pos) && 
		left.type == right.type && 
		left.strength == right.strength && 
		left.maxhealth == right.maxhealth && 
		left.health == right.health);
}
