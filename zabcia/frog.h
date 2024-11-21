#pragma once
#include "includes.h"
#include "map.h"

typedef struct {
	int x, y;
	int jump_distance;
	int lives;
	char symbol;
	char map_piece;

}Frog;

bool frog_within_bounds(int x, int y);

void jump(char**map,Frog* frog, int direction);

void initialize_frog(char**map,Frog* frog);


