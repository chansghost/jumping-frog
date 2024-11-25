#pragma once
#include "includes.h"
#include "frog.h"
#include "cars.h"
#include "map.h"


void frog_on_car(char** map, Frog* frog, Car* car);

bool check_collision(char** map, Frog* frog, Car** cars, int max_cars,int x, int y,int index=-1);

void move_car(char** map, Car** cars, int index, int max_cars, Frog* frog, int streets[], int max_speed);

void jump(char** map, Frog* frog, int direction, Car** cars, int max_cars);

bool check_for_frog(Car* car,Frog*frog);