#pragma once
#include "includes.h"
#include "frog.h"
#include "cars.h"
#include "map.h"
#include "obstacle.h"
#include "config.h"
#include "bonus.h"
#include "player.h"
#include "stork.h"

void frog_on_car(char** map, Frog* frog, Car* car);

bool check_collision(char** map, Frog* frog, Car** cars, int max_cars,int x, int y,int index=-1);

void try_on_car(char** map, Frog* frog, Car** cars, int max_cars);

void move_car(char** map, Car** cars, int index, int max_cars, Frog* frog, int streets[], int max_speed);

void jump(char** map, Frog* frog, int direction, Car** cars, int max_cars,int max_bonuses, Bonus** bonuses, Player* player);

void respawn_car(char** map, Car* car, int streets[], int max_speed);

bool check_for_frog(Car* car,Frog*frog);

bool obstacle_check(char** map, int x, int y);

bool bonus_collected(char** map, Bonus** bonuses,Frog* frog,int direction,int max_bonus);

int chooseLevel();

bool look_for_frog(Car*car,char**map,Frog*frog);



void fly_stork(Stork* stork, Frog* frog, char** map);

void gameplay(char** map,char** pastmap, int max_cars,Car** cars, Frog* frog, int streets[],LevelConfig config,Bonus**bonuses,Player*player,Stork*stork);

void game(char** map, char**basemap,char** pastmap, Car** cars, LevelConfig config, Frog* frog,Obstacle**obstacles,Bonus**bonuses,Player*player, Stork* stork);