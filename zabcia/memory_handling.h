#pragma once
#include "map.h"
#include "cars.h"
#include "frog.h"
#include "gameplayy.h"
#include "obstacle.h"
#include "config.h"
#include "includes.h"
#include "bonus.h"
#include "player.h"
#include "stork.h"
#include "game_save.h"

void initialize_map(char*** basemap, char*** map, char*** pastmap);

void initialize_memory(
    Car*** cars,
    Obstacle*** obstacles,
    Bonus*** bonuses,Frog**frog, Stork** stork, LevelConfig config);

void free_memo(Car** cars,
    Obstacle** obstacles,
    Bonus** bonuses, Frog* frog, Stork* stork, LevelConfig config);

void free_map(char** map, char** basemap, char** pastmap);