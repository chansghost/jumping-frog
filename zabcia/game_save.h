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


void save_player_to_ranking(Player player);
int compare_names(char* name1, char* name2);

void save_player(FILE* file, Player* player);
void save_cars(FILE* file, Car** cars, int max_cars);
void save_obstacles(FILE* file, Obstacle** obstacles, int max_obstacles);
void save_bonuses(FILE* file, Bonus** bonuses, int max_bonuses);
void save_frog(FILE* file, Frog* frog);
void save_stork(FILE* file, Stork* stork);

void save_game_state(Car** cars, Obstacle** obstacles, Bonus** bonuses, Frog* frog, Stork* stork, Player* player, LevelConfig config);
//void save_map(char** map,FILE*file);


void read_player(FILE* file, Player* player);
void read_cars(FILE* file, Car*** cars, int max_cars);
void read_obstacles(FILE* file, Obstacle*** obstacles, int max_obstacles);
void read_bonuses(FILE* file, Bonus*** bonuses, int max_bonuses);
void read_frog(FILE* file, Frog** frog);
void read_stork(FILE* file, Stork** stork);
void read_game_state(Car*** cars, Obstacle*** obstacles, Bonus*** bonuses, Frog** frog, Stork** stork, Player* player, LevelConfig* config);

