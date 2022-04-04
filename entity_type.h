
// header guards
#ifndef ENTITY_TYPE_H
#define ENTITY_TYPE_H

// entity types
typedef enum {
	none,
	player,
	enemy,
} entity_type ;

// for rendering entities
static const char entity_char[] = {
	' ',
	'@',
	'0',
};

#endif
