#pragma once
#include "map.h"
#include "includes.h"

typedef struct {
    int x, y, speed, street_number;
    bool friendly;
    char symbol;
}Car;

void initialize_car(Car* car);

void draw_car(char** map, Car* car);

void generate_random_car_position(Car* car, char** map, int streets[]);

void generate_car(Car* car, char** map, bool friendly, int streets[]);

bool within_bounds(char** map, int x, int y);

void generate_all_cars(Car** cars, char** map, int max_friendly, int max_enemy, int min_cars, int streets[]);