
// header guards
#ifndef ENTITY_TYPE_H
#define ENTITY_TYPE_H

// entity types
enum entity_type {
	none,
	player,
	enemy,
};

// for rendering entities
static char entity_char[] = {
	' ',
	'@',
	'0',
};

#endif
