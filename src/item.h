#ifndef ITEM_H
#define ITEM_H

typedef enum {
	none_item,
	health_potion,
	last_item
} item_type;

extern const char* item_name[];

typedef struct {
	item_type type;
	int num_stats;
	int* stats;
} item;
typedef struct {
	item* items;
	int num_items;
} inventory;
typedef struct {
	item item;
	int item_color;
	char* item_char;
	char* item_name;
} ite_data;
extern ite_data item_data[last_item];

void items_init(void);
item item_init(item_type type, int num_stats, int* stats);
inventory add_to_inventory(inventory inv, item ite);
inventory remove_from_inventory(inventory inv, int i);

#endif
