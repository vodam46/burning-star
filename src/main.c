#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>

#include "tile.h"
#include "entity.h"
#include "map.h"
#include "drawing.h"
#include "vector.h"
#include "ai.h"
#include "menu.h"
#include "action.h"

int main(void) {
	srand(time(NULL));
	setlocale(LC_ALL, "");

	entities_init();
	tiles_init();

	// screen init
	initscr();
	start_color();
	keypad(stdscr, TRUE);
	vector scr_size;
	getmaxyx(stdscr, scr_size.y, scr_size.x);
	vector main_scr_size = vect_init(scr_size.y-4, scr_size.x-2);

	// colors
	init_pair(0,COLOR_WHITE,COLOR_BLACK);
	init_pair(1,COLOR_GREEN,COLOR_BLACK);
	init_pair(2,COLOR_RED,COLOR_YELLOW);

	char* map_options[] = {
		"Empty map",
		"Maze",
		"Cave",
	};
	int map_choice = menu(
		stdscr,
		scr_size,
		"Choose world gen options",
		map_options,
		sizeof(map_options)/sizeof(*map_options)
	);
	if (map_choice == -1) {
		endwin();
		return 1;
	}

	WINDOW* main_scr = newwin(main_scr_size.y,main_scr_size.x, 3,1);

	world_map wmap;
	wmap.size = vect_init(1000,1000);
	if (map_choice == 0) {
		wmap = wmap_gen_tile(wmap.size, empty);
	} else if (map_choice == 1) {
		wmap = wmap_gen_bin_tree_maze(wmap.size);
	} else if (map_choice == 2) {
		wmap = wmap_gen_directional_cave(wmap.size);
	} else {
		wmap = wmap_gen_tile(wmap.size, empty);
	}

	char msg[256] = "";
	int turn_count = 0;
	int ent_killed = 0;
	char ent_num_msg[100] = "";

	int ch = 0;
	// main game loop
	while (ch != 'q') {
		if (wmap.ent_num-1 == 0)
			sprintf(ent_num_msg, "no enemy on screen");
		else if (wmap.ent_num-1 == 1)
			sprintf(ent_num_msg, "1 enemy on screen");
		else
			sprintf(ent_num_msg, "%d enemies on screen", wmap.ent_num-1);
		sprintf(msg, "%d/%d hp, %d str, %d killed, %s, %d turns", wmap.ent_arr[0]->health, wmap.ent_arr[0]->maxhealth, wmap.ent_arr[0]->strength, ent_killed, ent_num_msg, turn_count);
		draw(stdscr, main_scr, wmap, scr_size, main_scr_size, msg);
		move(wmap.ent_arr[0]->pos.y+3,wmap.ent_arr[0]->pos.x+1);

		ch = wgetch(stdscr);					// updates the user input
		vector move_dir = vect_init(0,0);
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

			default:
				user_moved = 0;
				// sprintf(msg, "%d, %c", ch, ch);
				break;
		}
		user_moved &= ent_action(wmap, 0, move_dir, wmap.size);

		if (user_moved) {
			for (int ent_i = 1; ent_i < wmap.ent_num; ent_i++) {
				if (wmap.ent_arr[ent_i]->health <= 0) {
					// delete
					ent_killed++;
					wmap.ent_arr[ent_i]->type = none;
					for (int i = ent_i; i < wmap.ent_num-1; i++) {
						wmap.ent_arr[i] = wmap.ent_arr[i+1];
					}
					ent_i--;
					wmap.ent_num--;
				}
				ent_action(wmap, ent_i, basic_dir(wmap.ent_arr[ent_i]->pos, wmap.ent_arr[0]->pos), wmap.size);
			}

			if (wmap.ent_arr[0]->health <= 0)
				break;

			if (turn_count%10 == 0) {
				vector new_enemy_pos;
				if (map_choice) {
					new_enemy_pos = vect_init((rand()%((int)wmap.size.y/2))*2,(rand()%((int)wmap.size.x/2)*2));
				} else {
					new_enemy_pos = vect_init((rand()%wmap.size.y),(rand()%wmap.size.x));
				}
				if (vect_comp(new_enemy_pos, wmap.ent_arr[0]->pos))
					new_enemy_pos = vect_init(rand()%2*wmap.size.y,rand()%2*wmap.size.x);
				wmap.ent_num=create_entity(wmap,new_enemy_pos,enemy);
			}

			turn_count++;
		}
	}
	clear();
	sprintf(msg,"You died, score: %d, turns played: %d", ent_killed, turn_count);
	mvprintw((int)scr_size.y/2,(int)scr_size.x/2-(int)strlen(msg)/2,"%s",msg);
	refresh();
	getch();


	endwin();		// end ncurses mode
	for (int y = 0; y < scr_size.y; y++)
		free(wmap.map[y]);
	free(wmap.map);		// free the memory for the world map
	free(wmap.ent_arr);	// free the memory for the entity array
	printf("%d enemies killed\n", ent_killed);
	return 0;
}
