// global libraries
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>

// custom libraries
#include "tile.h"
#include "entity.h"
#include "map.h"
#include "entity_type.h"
#include "drawing.h"
#include "vector.h"
#include "ai.h"
#include "menu.h"
#include "action.h"

int main(void) {
	srand(time(NULL));
	setlocale(LC_ALL, "");

	// screen init
	initscr();
	start_color();
	keypad(stdscr, TRUE);
	vector scr_size;
	getmaxyx(stdscr, scr_size.y, scr_size.x);
	vector main_scr_size = vect_init(scr_size.y-4,scr_size.x-2);

	// colors
	init_pair(0,COLOR_WHITE,COLOR_BLACK);
	init_pair(1,COLOR_RED,COLOR_YELLOW);
	init_pair(2,COLOR_GREEN,COLOR_BLACK);

	char* map_options[] = {
		"Empty map",
		"Maze"
	};
	int map_choice = menu(stdscr, scr_size, "Test", map_options, sizeof(map_options)/sizeof(*map_options));

	WINDOW* main_scr = newwin(main_scr_size.y,main_scr_size.x, 3,1);

	tile** wmap;
	if (map_choice == 0) {
		wmap = wmap_gen(main_scr_size.y, main_scr_size.x);
	} else if (map_choice == 1) {
		wmap = wmap_gen_bin_tree_maze(main_scr_size.y, main_scr_size.x);
	} else {
		wmap = wmap_gen(main_scr_size.y, main_scr_size.x);
	}
	vector middle = vect_init((int)(main_scr_size.y/2), (int)(main_scr_size.x/2));
	char msg[256] = "";

	entity** ent_arr = malloc(main_scr_size.y * main_scr_size.x * sizeof(entity));
	int ent_num = 0;

	ent_num = create_entity(wmap, ent_arr, ent_num, vect_init(middle.y+(middle.y%2==0?0:1),middle.x+(middle.x%2==0?0:1)), player, 5, 20);

	int turn_count = 0;
	int ent_killed = 0;
	char ent_num_msg[100] = "";

	int ch = 0;
	// main game loop
	while (ch != 'q') {
		if (ent_num-1 == 0)
			sprintf(ent_num_msg, "no enemy on screen");
		else if (ent_num-1 == 1)
			sprintf(ent_num_msg, "1 enemy on screen");
		else
			sprintf(ent_num_msg, "%d enemies on screen", ent_num-1);
		sprintf(msg, "%d/%d hp, %d str, %d killed, %s, %d turns", ent_arr[0]->health, ent_arr[0]->maxhealth, ent_arr[0]->strength, ent_killed, ent_num_msg, turn_count);
		draw(stdscr, main_scr, wmap, scr_size, main_scr_size, msg);
		move(ent_arr[0]->pos.y+3,ent_arr[0]->pos.x+1);

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
		user_moved &= ent_action(wmap, ent_arr, 0, move_dir, main_scr_size);

		if (user_moved) {
			for (int ent_i = 1; ent_i < ent_num; ent_i++) {
				if (ent_arr[ent_i]->health <= 0) {
					// delete
					ent_killed++;
					ent_arr[ent_i]->type = none;
					for (int i = ent_i; i < ent_num-1; i++) {
						ent_arr[i] = ent_arr[i+1];
					}
					ent_i--;
					ent_num--;
				}
				ent_action(wmap, ent_arr, ent_i, basic_dir(ent_arr[ent_i]->pos, ent_arr[0]->pos), main_scr_size);
			}

			if (ent_arr[0]->health <= 0)
				break;

			if (turn_count%10 == 0) {
				if (map_choice) {
					ent_num=create_entity(wmap,ent_arr,ent_num,vect_init((rand()%main_scr_size.y),(rand()%main_scr_size.x)),enemy,1,5);
				} else {
					ent_num=create_entity(wmap,ent_arr,ent_num,vect_init((rand()%((int)main_scr_size.y/2))*2,(rand()%((int)main_scr_size.x/2)*2)),enemy,1,5);
				}
			}

			turn_count++;
		}
	}
	clear();
	sprintf(msg,"You died, score: %d, turns played: %d", ent_killed, turn_count);
	mvprintw((int)scr_size.y/2,(int)scr_size.x/2-(int)strlen(msg)/2,"%s",msg);
	refresh();
	// sleep(1);
	getch();


	endwin();		// end ncurses mode
	for (int y = 0; y < scr_size.y; y++)
		free(wmap[y]);
	free(wmap);		// free the memory for the world map
	free(ent_arr);	// free the memory for the entity array
	printf("%d enemies killed\n", ent_killed);
	return 0;
}
