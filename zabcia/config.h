#pragma once
#include "includes.h"

typedef struct {
    int max_friend;
    int max_enemy;
    int minimum_cars;
    int max_speed;
    int max_obstacles;
    bool stork;
    int frog_jump;
    int frog_time;
}LevelConfig;

void read_lvl_config(FILE* file, int level, LevelConfig* config);

void printLevel(LevelConfig config,int level);

int writeLevelConfig(FILE* file, int level,LevelConfig* config);