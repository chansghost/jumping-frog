#include "frog.h"


void initialize_frog(char** map, Frog* frog) {
	frog->x = 0;
	frog->y = (MAP_HEIGHT / 2);
	frog->jump_distance = 2;
	frog->lives = 1;
	frog->symbol = '@';
	frog->map_piece = ' ';//pocz¹tkowy slot ¿aby
	frog->car_index = -1;
	frog->dead = false;
}


bool frog_within_bounds(int x,int y) {
	if (x >= MAP_WIDTH || x < 0 || y >= MAP_HEIGHT || y < 0) {
		return false;
	}
	return true;
}

void move_frog(char** map, Frog* frog, int x, int y) {
	
	update_map(map, frog->x, frog->y, frog->map_piece);
	frog->x = x;
	frog->y = y;
	frog->map_piece = map[y][x];
	
	update_map(map, x, y, frog->symbol);
	
}



