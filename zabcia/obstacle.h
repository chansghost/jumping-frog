#pragma once
#include "includes.h"
#include "map.h"

typedef struct {
	int x, y;
	int obstacle_id;
	char symbol;
}Obstacle;

void initialize_obstacle(Obstacle* obstacle);

void generate_obstacles(Obstacle** obstacles, int sidewalks[], char** map, int max_obstacles);