#pragma once
#include "includes.h"

void map_tests(char** map);
void print_stats(int level, int points);

void print_map(char** map,char**pastmap,char**basemap);

void update_past_map(char** pastmap, char** map);

void base_map(char** map, int street_numbers[], char**basemap);

void update_map(char** map, int x, int y, char symbol);