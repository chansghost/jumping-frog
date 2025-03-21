#include "frog.h"


void initialize_frog( Frog* frog) {
	frog->x = 0;///chang
	frog->y = (MAP_HEIGHT / 2);
	//frog->y = 18;
	frog->jump_distance = 0;
	frog->symbol = '@';
	frog->map_piece = ' ';//pocz�tkowy slot �aby
	frog->car_index = -1;
	frog->dead = false;
	frog->jumping = false;
	
}


bool frog_within_bounds(int x,int y) {
	if (x >= MAP_WIDTH || x < 0 || y >= MAP_HEIGHT || y < 0) {
		return false;
	}
	return true;
}

void move_frog(char** map, Frog* frog, int x, int y) {
	if (frog->car_index == -1) {//prevent leaving "car trace"
		update_map(map, frog->x, frog->y, frog->map_piece);
	}
	
	frog->x = x;
	frog->y = y;

	frog->map_piece = map[y][x];
	
	update_map(map, x, y, frog->symbol);
	
}



