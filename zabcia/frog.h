#pragma once
#include "includes.h"
#include "map.h"
#include "cars.h"

typedef struct {
	int x, y;
	int jump_distance;
	int lives;
	char symbol;
	char map_piece;
	int car_index;
	bool dead;
	bool jumping;//checking if the frog is currently making a jump (needed for
	//checking the collision)

}Frog;

bool frog_within_bounds(int x, int y);



void initialize_frog(char**map,Frog* frog);

void move_frog(char** map, Frog* frog,int x,int y);


//void frog_on_car(char** map, Frog* frog, Car* car);


