#pragma once
#include "map.h"
#include "includes.h"

typedef struct {
    int x, y,street_number;
    float speed;
    bool friendly;
    char symbol;
}Car;

void reset_car(Car* car,bool friendly);

void draw_car(char** map, Car* car,bool clear);

void generate_random_car_position(Car* car, char** map, int streets[]);

void generate_car(Car* car, char** map, bool friendly, int streets[]);

bool within_bounds(char** map, int x, int y);

void move_car(char** map, Car* car);

void generate_all_cars(Car** cars, char** map, int max_friendly, int max_enemy, int min_cars, int streets[]);