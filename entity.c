#include "entity.h"


struct entity ent_init(int _x, int _y, enum Type _type) {
	struct entity ret_ent;
	ret_ent.x = _x;
	ret_ent.y = _y;
	ret_ent.type = _type;
	return ret_ent;
}