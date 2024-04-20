#include <stdlib.h>
#include <string.h>

#include "item.h"
#include "key_val_reader.h"

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

		pairs_arr pairs = parse_file(file_name);

		item_data[i].item.type = i;

		char* item_name = get_value("name", pairs).string;
		item_data[i].item_name = malloc((strlen(item_name)+1)*sizeof(char));
		strcpy(item_data[i].item_name, item_name);

		char* ite_char = get_value("char", pairs).string;
		item_data[i].item_char = malloc((strlen(ite_char)+1) * sizeof(char));
		strcpy(item_data[i].item_char, ite_char);

		value stats = get_value("stats", pairs);
		item_data[i].item.stats = malloc((stats.num_elements+1) * sizeof(int));
		for (int j = 0; j <= item_data[i].item.num_stats; j++) {
			item_data[i].item.stats[j] = atoi(stats.array[j]);
		}

		delete_pairs(pairs);
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
