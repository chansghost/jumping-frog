#pragma once

#include "map.h"


void allocate(char*** map, char*** pastmap, int max_cars);

void free_memory(char** map, char** pastmap,int max_cars);