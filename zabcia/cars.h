#pragma once
#include "map.h"
#include "includes.h"

typedef struct {
    int x, y, street_number;
    int car_id;
    int speed;
    bool friendly;
    char symbol;
}Car;

void reset_car(Car* car, bool friendly);

void collision(char** map, Car* car, Car* other);

void render_car(char** map, Car* car, bool clear);

void generate_random_car_position(Car* car, char** map, int streets[]);

void generate_car(Car* car, char** map, bool friendly, int streets[], int max_speed);

bool car_bounds(char** map, int x, int y);

void move_car(char** map, Car** cars, int index, int max_cars);

bool check_for_cars(char** map, Car** cars, int max_cars, int y, int index);

void generate_all_cars(Car** cars, char** map, int max_friendly, int max_enemy, int min_cars, int streets[], int max_speed);