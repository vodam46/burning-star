#include "config.h"
#include "menu.h"
#include "string.h"
#include "drawing.h"

#ifdef USE_CURSES
int menu(char* prompt, char* options[], int num_options) {
	size_t max_len = strlen(prompt);
	for (int i = 0; i < num_options; i++)
		if (strlen(options[i])>max_len)
			max_len=strlen(options[i]);
	int option = -1;
	int cur_option = 0;
	while (option == -1) {
		clear();
		wrefresh(stdscr);
		menu_draw(prompt, options, num_options, cur_option, max_len);
		int ch = wgetch(stdscr);
		switch(ch) {
			case(KEY_UP):
				if (cur_option > 0)
					cur_option--;
				else
					cur_option = num_options-1;
				break;
			case(KEY_DOWN):
				if (cur_option < num_options-1)
					cur_option++;
				else
					cur_option = 0;
				break;
			case(KEY_ENTER): case(10):
				return cur_option;
			case('q'):
				return -1;
		}
	}
	return -1;
}
#else
#error "please use curses, there is not yet another rendering system"
#endif
