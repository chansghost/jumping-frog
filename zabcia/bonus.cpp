#include "bonus.h"

void initialize_bonus(Bonus* bonus) {
	bonus->x = -1;
	bonus->y = -1;
	bonus->collected = false;
	bonus->symbol = BONUS;

}

void generate_bonuses(Bonus** bonuses, char** map,int max_bonuses) {
	int x_pos, y_pos;
	bool empty = false;
	srand(time(NULL));
	for (int i = 0; i < max_bonuses; i++) {
		while (!empty) {
			x_pos = rand() % (MAP_WIDTH - 1) + 1;
			y_pos = rand() % (MAP_HEIGHT - 1) + 1;
			if (map[y_pos][x_pos] == EMPTY) {
				empty = true;
			}
		}
		bonuses[i]->x = x_pos;
		bonuses[i]->y = y_pos;
		bonuses[i]->bonus_id = i;
		update_map(map, x_pos, y_pos, BONUS);
		empty = false;
	}
}


void collect_bonus(Bonus** bonuses, int x, int y,int max_bonus,char**map) {
	for (int i = 0; i < max_bonus; i++) {
		if (bonuses[i]->x == x && bonuses[i]->y == y) {
			bonuses[i]->collected = true;
			bonuses[i]->x = -1;
			update_map(map, x, y, EMPTY);
			return;
		}
	}
}