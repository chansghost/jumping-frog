#pragma once
#include "map.h"
#include "includes.h"
#include "frog.h"
#include "config.h"

typedef struct {
    int x, y, street_number;
    int car_id;
    int speed;
    bool friendly;
    char symbol;
    int respawn;
    int direction;
    bool stops;
}Car;

void reset_car(Car* car, bool friendly,int x=-1,int direction=-1,int street_number=-1,bool stops=false);

void car_collision(char** map, Car* org_car, Car* other_car);

void render_car(char** map, Car* car, bool clear);

void generate_random_car_position(Car* car, char** map, int streets[]);

void generate_car(Car* car, char** map, bool friendly, int streets[], int max_speed,bool stop=false);

bool car_bounds(int x, int y);

int return_car(int x, int y, Car** cars,int max_cars);

bool check_for_cars(char** map, Car** cars, int max_cars, int index);

void generate_all_cars(Car** cars, char** map, int streets[], LevelConfig config);

void render_all_cars(char** map, Car** cars, LevelConfig config);