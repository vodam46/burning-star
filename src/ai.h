#ifndef AI_H
#define AI_H

#include "vector.h"
#include "map.h"

typedef struct {
	vector pos;
	vector dir;
	int dist;
	int visited;
} dijkstra_map_node;
extern dijkstra_map_node** dijkstra_map;

extern int map_allocated;
vector basic_dir(vector start, vector end);
void update_dijkstra_map(world_map wmap);

#endif
