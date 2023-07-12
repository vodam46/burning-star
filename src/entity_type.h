
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
extern const char entity_char[];

extern const int entity_color[];

#endif
