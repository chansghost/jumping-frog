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



void read_game_state(Car*** cars, Obstacle*** obstacles, Bonus*** bonuses, Frog** frog, Stork** stork, Player* player, LevelConfig* config);

