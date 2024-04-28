#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>

#include "action.h"
#include "ai.h"
#include "drawing.h"
#include "entity.h"
#include "item.h"
#include "map.h"
#include "menu.h"
#include "noise.h"
#include "tile.h"
#include "vector.h"

int main(void) {
	srand(time(NULL));
	setlocale(LC_ALL, "");

	entities_init();
	tiles_init();
	items_init();
	noise_init();

	drawing_init();

	char* map_options[] = {
		"Empty map",
		"Maze",
		"Cave",
		"Noise",
		"Load previous"
	};
	int map_choice = menu(
		"Choose world gen options",
		map_options,
		sizeof(map_options)/sizeof(*map_options)
	);
	if (map_choice == -1) {
		drawing_end();
		return 1;
	}
	world_map wmap;
	wmap.size = vect_init(1000, 1000);
	switch (map_choice) {
		case 0:
			wmap = wmap_gen_tile(wmap.size, empty);
			break;
		case 1:
			wmap = wmap_gen_bin_tree_maze(wmap.size);
			break;
		case 2:
			wmap = wmap_gen_directional_cave(wmap.size);
			break;
		case 3:
			wmap = wmap_gen_noise(wmap.size);
			break;
		case 4:
			wmap = load_map("wmap");
			break;
		default:
			wmap = wmap_gen_tile(wmap.size, empty);
			break;
	}

	char msg[256] = "";
	char ent_num_msg[100] = "";

	int ch = 0;
	int run = 1;
	int died = 0;
	// main game loop
	while (run) {
		if (wmap.ent_num-1 == 0)
			sprintf(ent_num_msg, "no enemy alive");
		else if (wmap.ent_num-1 == 1)
			sprintf(ent_num_msg, "1 enemy alive");
		else
			sprintf(ent_num_msg, "%d enemies alive", wmap.ent_num-1);
		sprintf(
			msg,
			"%d/%d hp, %d str, %d killed, %s, %d turns, y: %d x: %d",
			wmap.ent_arr[0]->health,
			wmap.ent_arr[0]->maxhealth,
			wmap.ent_arr[0]->strength,
			wmap.ent_killed,
			ent_num_msg,
			wmap.turn_count,
			wmap.ent_arr[0]->pos.y,
			wmap.ent_arr[0]->pos.x
		);
		calculate_fov(wmap);
		draw(wmap, scr_size, main_scr_size, msg);

		clearinp();
		ch = getinp();					// updates the user input
		vector move_dir = vect_init(0,0);
		vector dig_dir = vect_init(0, 0);
		int user_moved = 1;
		// react to user input
		switch(ch) {
			/*

			   ^ = y -1 x 0

			   > = y 0 x +1

			   V = y +1 x 0

			   < = y 0 x -1

			*/
			// up arrow or 8
			case(KEY_UP): case(56):				// y -
				move_dir = vect_init(-1, 0);
				break;
			// right arrow or 6
			case(KEY_RIGHT): case(54):			// x +
				move_dir = vect_init(0, +1);
				break;
			// down arrow or 2
			case(KEY_DOWN):	case(50):			// y +
				move_dir = vect_init(+1, 0);
				break;
			// left arrow or 4
			case(KEY_LEFT):	case(52):			// x -
				move_dir = vect_init(0, -1);
				break;

			// picking up items
			case ('g'):
				user_moved = pick_up_item(wmap, 0);
				break;

			// activating items from inventory
			case ('a'):
				if (wmap.ent_arr[0]->inventory.num_items != 0)
					user_moved = use_item_from_inventory(wmap, 0);
				else user_moved = 0;
				break;

			// digging
			case ('d'):
				switch(getinp()) {
					case(KEY_UP): case(56):
						dig_dir = vect_init(-1, 0);
						break;
					case(KEY_RIGHT): case(54):
						dig_dir = vect_init(0, +1);
						break;
					case(KEY_DOWN):	case(50):
						dig_dir = vect_init(+1, 0);
						break;
					case(KEY_LEFT):	case(52):
						dig_dir = vect_init(0, -1);
						break;
					default:
						dig_dir = vect_init(0,0);
				}
				user_moved = dig(wmap, wmap.ent_arr[0]->pos, dig_dir);
				break;

			case KEY_RESIZE:
				resize_screen();
				user_moved = 0;
				break;

			case 'q':
				run = 0;
				user_moved = 0;
				break;
			case 's':
				// mvprintw(1, 1, "saving"); // not really needed? saving is so
				// fast its useless
				save_map(wmap, "wmap");
				user_moved = 0;
				break;

			case '.':
				break;

			default:
				user_moved = 0;
				// sprintf(msg, "%d, %c", ch, ch);
				break;
		}
		if (!vect_comp(vect_init(0, 0), move_dir))
			user_moved &= ent_action(wmap, 0, move_dir, wmap.size);

		if (user_moved) {
			update_dijkstra_map(wmap);
			for (int ent_i = 1; ent_i < wmap.ent_num; ent_i++) {
				vector ent_pos = wmap.ent_arr[ent_i]->pos;
				if (wmap.ent_arr[ent_i]->health <= 0) {
					if (rand() % 1 == 0) {
						wmap.map[ent_pos.y][ent_pos.x].items =
							add_to_inventory(
								wmap.map[ent_pos.y][ent_pos.x].items,
								item_data[health_potion].item
							);
					}
					// entity killed
					wmap.ent_killed++;
					wmap.ent_arr[ent_i]->type = none_entity;
					for (int i = ent_i; i < wmap.ent_num-1; i++) {
						wmap.ent_arr[i] = wmap.ent_arr[i+1];
					}
					ent_i--;
					wmap.ent_num--;
				}
				vector ent_dir = vect_init(0, 0);
				if (map_allocated && dijkstra_map[ent_pos.y][ent_pos.x].visited) {
					ent_dir = dijkstra_map[ent_pos.y][ent_pos.x].dir;
				} else {
					ent_dir = basic_dir(ent_pos, wmap.ent_arr[0]->pos);
				}
				ent_action(wmap, ent_i, ent_dir, wmap.size);
			}

			if (wmap.ent_arr[0]->health <= 0) {
				died = 1;
				break;
			}

			if (
				wmap.enemy_spawn_num >= 0 && (
					rand() % (20 - wmap.enemy_spawn_num + 1) + wmap.enemy_spawn_num
				) == wmap.enemy_spawn_num
			) {
				vector new_enemy_pos;
				if (map_choice) {
					new_enemy_pos = vect_init(
						(rand()%((int)wmap.size.y/2))*2,
						(rand()%((int)wmap.size.x/2)*2)
					);
				} else {
					new_enemy_pos = vect_init((rand()%wmap.size.y),(rand()%wmap.size.x));
				}
				if (vect_comp(new_enemy_pos, wmap.ent_arr[0]->pos))
					new_enemy_pos = vect_init(rand()%2*wmap.size.y,rand()%2*wmap.size.x);
				wmap.ent_num=create_entity(wmap,new_enemy_pos,enemy);
				wmap.enemy_spawn_num -= 10;
			}

			wmap.turn_count++;
			wmap.enemy_spawn_num++;
		}
	}
	if (died) {
		sprintf(msg,"You died, score: %d, turns played: %d", wmap.ent_killed, wmap.turn_count);
	}


	drawing_end();

	for (int y = 0; y < scr_size.y; y++) {
		free(wmap.map[y]);
		if (map_allocated)
			free(dijkstra_map[y]);
	}
	free(wmap.map);
	if (map_allocated)
		free(dijkstra_map);

	free(wmap.ent_arr);

	for (int i = 0; i < last_ent; i++) {
		free(ent_data[i].entity_char);
		free(ent_data[i].ent.inventory.items);
	}
	for (int i = 0; i < last_item; i++) {
		free(item_data[i].item_char);
		free(item_data[i].item.stats);
	}

	printf("%d enemies killed\n", wmap.ent_killed);
	return 0;
}
