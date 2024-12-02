#pragma once
#include "includes.h"
#include "defines.h"
#include "map.h"

typedef struct {
	int x, y;
	double speed;//can only be the multiplicity of 1/2
	double time_spawn;//stork spawns after x seconds within starting the game
	char symbol;
	bool exists;
	char map_piece[STORK_SIZE*2];
	double gained_speed;//variable to control speed if it's below 1
}Stork;

void initialize_stork(Stork* stork);

void spawn_stork(Stork* stork, double time, char** map);

void move_stork(Stork* stork, int direction, int direction2);

bool frog_caught(Stork* stork, char** map);

void update_map_piece(Stork* stork, char** map);

void render_stork(char** map, Stork* stork, bool clear);