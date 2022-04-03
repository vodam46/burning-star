
// global libraries
#include <stdio.h>

// custom libraries
#include "entity.h"
#include "entity_type.h"
#include "vector.h"

// entity init function
struct entity ent_init(struct vector _pos, enum entity_type _type) {
	struct entity ret_ent;
	ret_ent.pos = _pos;
	ret_ent.type = _type;
	return ret_ent;
}
