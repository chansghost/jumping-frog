#pragma once
#include "includes.h"
#include "defines.h"
#include "obstacle.h"
#include "map.h"
#include "frog.h"
#include "cars.h"
#include "stork.h"
#include "player.h"
#include "bonus.h"
#include "config.h"

void save_game(char**map,char**pastmap,Obstacle**obstacles,Car**cars,Stork*stork,Frog*frog,Bonus**bonuses,Player*player,LevelConfig config);

void save_map(char** map,FILE*file);

void save_cars(Car** cars, FILE* file,LevelConfig config);

void save_obstacles(Obstacle** obstacles, FILE* file,LevelConfig config);

void save_frog(Frog* frog, FILE* file);

void save_stork(Stork* stork, FILE* file);

void save_bonuses(Bonus** bonuses, FILE* file,LevelConfig config);

