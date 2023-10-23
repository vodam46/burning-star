#ifndef ENTITY_H
#define ENTITY_H

#include "vector.h"

// entity types
typedef enum {
	none,
	player,
	enemy,
	last_ent,
} entity_type ;

extern const char* ent_name[];

// entity struct
typedef struct {
	entity_type type;
	vector pos;
	int strength, maxhealth, health;
} entity;

typedef struct {
	entity ent;
	char* entity_char;
	int entity_color;
} entity_data;
extern entity_data ent_data[last_ent];

void entities_init();

entity ent_init(vector pos, entity_type type, int strength, int maxhealth, int health);

int ent_comp(entity left, entity right);

#endif
