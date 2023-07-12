#include <ncurses.h>

#include "menu.h"
#include "vector.h"
#include "string.h"

void menu_draw(WINDOW* stdscr, char* prompt, char** options, int num_options, int cur_option) {
	wclear(stdscr);
	wprintw(stdscr, "%s", prompt);
	for (int i = 0; i < num_options; i++) {
		mvwprintw(stdscr, i+1, 0, "[ ] %s", options[i]);
	}
	mvwaddch(stdscr,cur_option+1,1,'#');
	wmove(stdscr, cur_option+1, 1);
	wrefresh(stdscr);
}
int menu(WINDOW* stdscr, vector scr_size, char* prompt, char* options[], int num_options) {
	size_t max_len = strlen(prompt);
	for (int i = 0; i < num_options; i++)
		if (strlen(options[i])>max_len)
			max_len=strlen(options[i]);
	WINDOW* menu_win = newwin(num_options+1,max_len,(int)(scr_size.y/2-num_options/2),
			(int)(scr_size.x/2-max_len/2));
	int option = -1;
	int cur_option = 0;
	while (option == -1) {
		clear();
		wrefresh(stdscr);
		menu_draw(menu_win, prompt, options, num_options, cur_option);
		int ch = wgetch(stdscr);
		switch(ch) {
			case(KEY_UP):
				if (cur_option > 0)
					cur_option--;
				break;
			case(KEY_DOWN):
				if (cur_option < num_options-1)
					cur_option++;
				break;
			case(KEY_ENTER): case(10):
				return cur_option;
		}
	}
	return -1;
}
