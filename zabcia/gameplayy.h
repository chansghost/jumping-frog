#pragma once
#include "includes.h"
#include "frog.h"
#include "cars.h"
#include "map.h"
#include "obstacle.h"
#include "config.h"


void frog_on_car(char** map, Frog* frog, Car* car);

bool check_collision(char** map, Frog* frog, Car** cars, int max_cars,int x, int y,int index=-1);

void move_car(char** map, Car** cars, int index, int max_cars, Frog* frog, int streets[], int max_speed);

void jump(char** map, Frog* frog, int direction, Car** cars, int max_cars);

void respawn_car(char** map, Car* car, int streets[], int max_speed);

bool check_for_frog(Car* car,Frog*frog);

bool obstacle_check(char** map, int x, int y);

int chooseLevel();

bool look_for_frog(Car*car,char**map);

void gameplay(char** map,char** pastmap, int max_cars,Car** cars, Frog* frog, int streets[],LevelConfig config);

void game(char** map, char**basemap,char** pastmap, Car** cars, LevelConfig config, Frog* frog,Obstacle**obstacles);