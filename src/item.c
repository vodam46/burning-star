#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "item.h"

const char* item_name[] = {
	"none",
	"health-potion",
};

ite_data item_data[last_item] = {0};
void items_init(void) {
	char data_dir[100] = PROJECT_DIR;
	strcat(data_dir,"/data/item/");
	for (int i = 0; i < last_item; i++) {
		char file_name[100] = {0};
		strcpy(file_name, data_dir);
		strcat(file_name, item_name[i]);

		item_data[i].item.type = i;

		FILE* file = fopen(file_name, "r");

		size_t len = 0;
		char* line = NULL;
		getline(&item_data[i].item_char, &len, file);
		getline(&line, &len, file);
		item_data[i].item_color = atoi(line);

		char c;
		item_data[i].item.num_stats = 0;
		while ((c = fgetc(file) != EOF)) {
			item_data[i].item.num_stats++;
		}
		item_data[i].item.num_stats--;

		item_data[i].item.stats = malloc(
				item_data[i].item.num_stats * sizeof(int)
				);
		rewind(file);
		getline(&line, &len, file);
		getline(&line, &len, file);
		for (int j = 0; j <= item_data[i].item.num_stats; j++) {
			getline(&line, &len, file);
			item_data[i].item.stats[j] = atoi(line);
		}

		fclose(file);
	}
}

item item_init(item_type type, int num_stats, int* stats) {
	item ret_item = {0};
	ret_item.type = type;
	ret_item.num_stats = num_stats;
	ret_item.stats = stats;
	return ret_item;
}

inventory add_to_inventory(inventory inv, item ite) {
	if (inv.num_items == 0) {
		inv.items = malloc(sizeof(item));
		inv.items[0] = ite;
	} else {
		inv.items = realloc(inv.items, (inv.num_items+1)*sizeof(item));
		inv.items[inv.num_items] = ite;
	}
	inv.num_items++;
	return inv;
}
inventory remove_from_inventory(inventory inv, int i) {
	if (i < inv.num_items) {
		for (int j = i; j < inv.num_items; j++) {
			inv.items[j] = inv.items[j+1];
		}
		inv.num_items--;
		inv.items = realloc(inv.items, inv.num_items * sizeof(item));
	}
	return inv;
}
