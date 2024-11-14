#pragma once
#include <stdbool.h>
#include "defines.h"


void print_stats(int level, int points);

void print_map(char** map);


void base_map(char** map, int street_numbers[]);

void update_map(char** map, int x, int y, char symbol);