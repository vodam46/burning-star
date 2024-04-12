#include <limits.h>
#include <stdlib.h>
#include <sys/param.h>

#include "ai.h"
#include "vector.h"
#include "map.h"


vector basic_dir(vector start, vector end) {
	vector direction = vect_init(start.y - end.y, start.x - end.x);
	if (abs(direction.y) > abs(direction.x)) {
		if (direction.y > 0) {
			return vect_init(-1, 0);
		} else if (direction.y < 0) {
			return vect_init( 1, 0);
		}
	} else {
		if (direction.x > 0) {
			return vect_init( 0,-1);
		} else if (direction.x < 0) {
			return vect_init( 0, 1);
		}
	}
	return vect_init(0, 0);
}

int map_allocated = 0;
dijkstra_map_node** dijkstra_map;
void update_dijstrka_map(world_map wmap) {
	// initialization
	if (map_allocated) {
		for (int y = 0; y < wmap.size.y; y++)
			free(dijkstra_map[y]);
		free(dijkstra_map);
	}
	dijkstra_map = malloc(wmap.size.y * sizeof(dijkstra_map_node*));
	map_allocated = 1;
	for (int y = 0; y < wmap.size.y; y++) {
		dijkstra_map[y] = malloc(wmap.size.x * sizeof(dijkstra_map_node));
		for (int x = 0; x < wmap.size.x; x++) {
			dijkstra_map[y][x] = (dijkstra_map_node){
				vect_init(y, x),
					vect_init(0, 0),
					INT_MAX,
					0,
			};
		}
	}
	vector current_node = vect_init(
		wmap.ent_arr[0]->pos.y,
		wmap.ent_arr[0]->pos.x
	);
	dijkstra_map[current_node.y][current_node.x].dist = 0;
	int finished = 0;
	vector neighbor;
	int cur_iter = 0;

	while (!finished && cur_iter < 1000) {
		dijkstra_map[current_node.y][current_node.x].visited = 1;

		for (int offset = -1; offset <= 1; offset += 2) {

			neighbor = vect_init(current_node.y + offset, current_node.x);
			if (
				in_bounds(neighbor, vect_init(0, 0), wmap.size)
			) {

				int new_dist = INT_MAX;
				if (wmap.map[neighbor.y][neighbor.x].type == wall) {
					new_dist = dijkstra_map[current_node.y][current_node.x].dist + 20;
				} else {
					new_dist = dijkstra_map[current_node.y][current_node.x].dist + 10;
				}

				if (dijkstra_map[neighbor.y][neighbor.x].dist >= new_dist) {
					dijkstra_map[neighbor.y][neighbor.x].dist = new_dist;
					dijkstra_map[neighbor.y][neighbor.x].dir = vect_sub(
							current_node,
							neighbor
					);
				}
			}

			neighbor = vect_init(current_node.y, current_node.x + offset);
			if (
				in_bounds(neighbor, vect_init(0, 0), wmap.size)
			) {

				int new_dist = INT_MAX;
				if (wmap.map[neighbor.y][neighbor.x].type == wall) {
					new_dist = dijkstra_map[current_node.y][current_node.x].dist + 20;
				} else {
					new_dist = dijkstra_map[current_node.y][current_node.x].dist + 10;
				}

				if (dijkstra_map[neighbor.y][neighbor.x].dist >= new_dist) {
					dijkstra_map[neighbor.y][neighbor.x].dist = new_dist;
					dijkstra_map[neighbor.y][neighbor.x].dir = vect_sub(
							current_node,
							neighbor
					);
				}
			}


		}

		finished = 1;
		int smallest_dist = INT_MAX;
		for (
				int y = MAX(wmap.ent_arr[0]->pos.y-50, 0);
				y < MIN(wmap.ent_arr[0]->pos.y+50, wmap.size.y);
				y++
			) {
			for (
					int x = MAX(wmap.ent_arr[0]->pos.x-50, 0);
					x < MIN(wmap.ent_arr[0]->pos.x+50, wmap.size.x);
					x++
				) {
				if (
						in_bounds(vect_init(y, x), vect_init(0, 0), wmap.size)
						&& dijkstra_map[y][x].dist < smallest_dist &&
						!dijkstra_map[y][x].visited
				   ) {
					finished = 0;
					smallest_dist = dijkstra_map[y][x].dist;
					current_node = vect_init(y, x);
				}
			}
		}

		cur_iter++;
	}
}
