#ifndef ACTION_H
#define ACTION_H

#include "entity.h"
#include "tile.h"

int ent_action(tile** wmap, entity** ent_arr, int ent_arr_id, vector pos_change, vector scr_size);
int create_entity(tile** wmap, entity** ent_arr, int ent_num, vector pos, entity_type type);
#endif
