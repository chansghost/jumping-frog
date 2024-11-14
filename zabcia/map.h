#pragma once
#include "includes.h"

void map_tests(char** map);
void print_stats(int level, int points);

void print_map(char** map);


void base_map(char** map, int street_numbers[]);

void update_map(char** map, int x, int y, char symbol);