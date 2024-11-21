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

}Frog;

bool frog_within_bounds(int x, int y);

void jump(char**map,Frog* frog, int direction);

void initialize_frog(char**map,Frog* frog);

void move_frog(char** map, Frog* frog,int x,int y);

void check_collision(char** map, Frog* frog, Car** cars, int max_cars);

void frog_on_car(char** map, Frog* frog, Car* car);


