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
#include "memory_handling.h"

void save_game_state(Car** cars, Obstacle** obstacles, Bonus** bonuses, Frog* frog, Stork* stork, Player* player, LevelConfig config);
//void save_map(char** map,FILE*file);

void save_cars(Car** cars, FILE* file,LevelConfig config);

void save_obstacles(Obstacle** obstacles, FILE* file,LevelConfig config);

void save_frog(Frog* frog, FILE* file);

void save_stork(Stork* stork, FILE* file);

void save_bonuses(Bonus** bonuses, FILE* file,LevelConfig config);

void load_game_state(Car*** cars, Obstacle*** obstacles, Bonus*** bonuses, Frog** frog, Stork** stork, Player* player, LevelConfig* config);

void load_cars(Car*** cars, FILE* file, LevelConfig config);

void load_frog(Frog* frog, FILE* file);

void load_stork(Stork* stork, FILE* file);

void load_obstacles(Obstacle*** obstacles, FILE* file, LevelConfig config);

void load_bonuses(Bonus*** bonuses, FILE* file, LevelConfig config);