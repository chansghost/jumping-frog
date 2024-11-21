#include "frog.h"



void initialize_frog(char**map,Frog* frog) {
	frog->x = 0;
	frog->y = (MAP_HEIGHT / 2);
	frog->jump_distance = 1;
	frog->lives = 1;
	frog->symbol = '$';
	frog->map_piece=' ';//pocz¹tkowy slot ¿aby
}

bool frog_within_bounds(int x,int y) {
	if (x >= MAP_WIDTH || x < 0 || y >= MAP_HEIGHT || y < 0) {
		return false;
	}
	return true;
}


void jump(char**map,Frog* frog, int direction)
{	
	int y = frog->y;
	int x = frog->x;
	if (direction == RIGHT) {
		//++y
		x += frog->jump_distance;
	}
	else if (direction == LEFT) {
		x -= frog->jump_distance;
	}
	else if (direction == UP) {
		y -= frog->jump_distance;
	}
	else if (direction == DOWN) {
		y += frog->jump_distance;
	}
	if (frog_within_bounds(x, y)) {
		update_map(map, frog->x, frog->y, frog->map_piece);
		frog->x = x;
		frog->y = y;
		frog->map_piece = map[y][x];
		update_map(map, x, y, frog->symbol);
	}
	else {
		cputs("nie wolno!!!!!!!!");
	}
}