#ifndef ENTITY_H
#define ENTITY_H

enum Type {
	// types of entities
	// TODO: fill with different types
	player
};

struct entity {
	// position
	int x;
	int y;

	// type
	// TODO: set parameters depending on the type (hp...)
	enum Type type;
};

struct entity ent_init(int _x, int _y, enum Type _type);


#endif