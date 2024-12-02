#include "stork.h"

void initialize_stork(Stork* stork) {
	stork->x = -1;
	stork->y = -1;
	stork->time_spawn = 0;
	stork->symbol = STORK;
	stork->exists = false;
	for (int i = 0; i < STORK_SIZE*2; i++) {
		stork->map_piece[i] = EMPTY;
	}
}

void spawn_stork(Stork* stork, double time,char**map) {
	if (time >= stork->time_spawn) {
		stork->x = 1;//stork always spawns on the top right corner
		stork->y = 1;
		
		stork->time_spawn = 0;//precaution
		update_map_piece(stork, map);
		render_stork(map, stork, ADD);
		stork->exists = true;
	}
	
}

bool frog_caught(Stork* stork, char** map) {
	int x = (stork->x) - 1;//minus one, since stork begins higher
	int y = (stork->y) - 1;
	for (int i = 0; i < STORK_SIZE; i++) {//x
		for (int j = 0; j < STORK_SIZE; j++) {//y
			if ((y + i) < MAP_HEIGHT && (y) > 0) {//precaution
				if (map[y+i][x+j] == FROG) {
					return true;
				}
			}

		}
	}
	return false;
	
}

void move_stork(Stork* stork, int directionUPDOWN, int directionLEFTRIGHT) {

	if (directionUPDOWN == DOWN) {
		stork->y += 1;
	}
	else if(directionUPDOWN == UP){
		stork->y -= 1;
	}
	if (directionLEFTRIGHT == RIGHT) {
		stork->x += 1;
	}
	else if(directionLEFTRIGHT ==LEFT) {
		stork->x -= 1;
	}
	
}

void update_map_piece(Stork* stork, char** map) {
	int x = stork->x - 1;
	int y = stork->y - 1;
	int counter = 0;
	for (int i = 0; i < STORK_SIZE; i++) {//x
		for (int j = 0; j < STORK_SIZE; j++) {//y
			if (map[y + i][x + j] == FRIENDLY || map[y + i][x + j] == ENEMY) {
				stork->map_piece[counter] = EMPTY;
			}
			else stork->map_piece[counter] = map[y + i][x + j];
			
			counter++;
		}
	}
}

void render_stork(char** map, Stork* stork, bool clear) {
	int x = (stork->x) - 1;//minus one, since stork begins higher
	int y = (stork->y) - 1;
	int counter = 0;
	for (int i = 0; i < STORK_SIZE; i++) {//x
		for (int j = 0; j < STORK_SIZE; j++) {//y
			if ((y + i) < MAP_HEIGHT && (y) > 0) {//precaution
				if (clear) {
					update_map(map, x + j, y + i, stork->map_piece[counter]);
					counter++;
				}
				else {
					update_map(map, x + j, y + i, STORK);
				}
				
			}

		}
	}
}

