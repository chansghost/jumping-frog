#pragma once
#include "map.h"
#include <stdbool.h>
#include "defines.h"
#include <time.h>

typedef struct {
    int x, y, speed, street_number;
    bool friendly;
    char symbol;
}Car;

void draw_car(char** map, Car* car);

void generate_random_car_position(Car* car, char** map, int streets[]);

void generate_car(Car* car, char** map, bool friendly, int streets[]);

void generate_all_cars(Car** cars, char** map, int max_friendly, int max_enemy, int min_cars, int streets[]);