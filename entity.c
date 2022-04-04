
// global libraries
#include <stdio.h>

// custom libraries
#include "entity.h"
#include "entity_type.h"
#include "vector.h"

// entity init function
entity ent_init(vector _pos, entity_type _type) {
	entity ret_ent;
	ret_ent.pos = _pos;
	ret_ent.type = _type;
	return ret_ent;
}
