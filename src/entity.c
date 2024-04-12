#include <stdlib.h>
#include <string.h>

#include "entity.h"
#include "vector.h"
#include "key_val_reader.h"

const char* ent_name[] = {
	"none",
	"player",
	"enemy",
};
entity_data ent_data[3] = {0};
void entities_init(void) {
	char data_dir[100] = PROJECT_DIR;
	strcat(data_dir,"/data/entity/");
	for (int i = 0; i < last_ent; i++) {
		char file_name[100] = {0};
		strcpy(file_name, data_dir);
		strcat(file_name, ent_name[i]);

		pairs_arr pairs = parse_file(file_name);

		ent_data[i].ent.type = i;

		char* ent_char = get_value("char", pairs).string;
		ent_data[i].entity_char = malloc((strlen(ent_char)+1) * sizeof(char));
		strcpy(ent_data[i].entity_char, ent_char);

		int hp = atoi(get_value("health", pairs).string);
		ent_data[i].ent.health = hp;
		ent_data[i].ent.maxhealth = hp;

		ent_data[i].ent.strength = atoi(get_value("strength", pairs).string);

		ent_data[i].entity_color = atoi(get_value("color", pairs).string);

		ent_data[i].ent.inventory = (inventory){0};
		delete_pairs(pairs);
	}
}

// entity init function
entity ent_init(
	vector pos,
	entity_type type,
	int strength,
	int maxhealth,
	int health,
	inventory inventory
) {
	entity ret_ent;
	ret_ent.pos = pos;
	ret_ent.type = type;
	ret_ent.strength = strength;
	ret_ent.maxhealth = maxhealth;
	ret_ent.health = health;

	// fix this probably?
	ret_ent.inventory = inventory;

	return ret_ent;
}

int ent_comp(entity left, entity right) {
	return (vect_comp(left.pos,right.pos) &&
		left.type == right.type &&
		left.strength == right.strength &&
		left.maxhealth == right.maxhealth &&
		left.health == right.health);
}
