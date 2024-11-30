#include "map.h"
#include "cars.h"
#include "frog.h"
#include "gameplayy.h"
#include "obstacle.h"
#include "config.h"
#include "includes.h"
#define _CRT_SECURE_NO_WARNINGS

int main() {
    srand(time(NULL));
    int level;//poczatkowy
    int points = 15;//do zmiany pozniej
    //robocze
    //0 & even numbers move down, odd numbers move up
    //level config
    level = chooseLevel();

    const char* filename = "config.txt";
    LevelConfig config;
    FILE* file = NULL;
    fopen_s(&file, filename, "r");
    read_lvl_config(file, level, &config);
    fclose(file);

    int max_cars = config.max_friend + config.max_enemy;


    printLevel(config, level);
    //wybierz level
    //start gry, na beginner level
    
    
    Car** cars = (Car**)malloc(max_cars * sizeof(Car*));
    for (int i = 0; i < max_cars; i++) {
        cars[i] = (Car*)malloc(sizeof(Car));
        reset_car(cars[i], NEW);
    }
    Obstacle** obstacles = (Obstacle**)malloc(config.max_obstacles * sizeof(Obstacle*));
    for (int i = 0; i < config.max_obstacles; i++) {
        obstacles[i] = (Obstacle*)malloc(sizeof(Obstacle));
        initialize_obstacle(obstacles[i]);
    }
    char** basemap = (char**)malloc(MAP_HEIGHT * sizeof(char*));
    for (int i = 0; i < MAP_HEIGHT; i++) {
        basemap[i] = (char*)malloc((MAP_WIDTH * sizeof(char)));

    }
    char** map = (char**)malloc(MAP_HEIGHT * sizeof(char*));
    for (int i = 0; i < MAP_HEIGHT; i++) {
        map[i] = (char*)malloc((MAP_WIDTH * sizeof(char)));

    }
    char** pastmap = (char**)malloc(MAP_HEIGHT * sizeof(char*));
    for (int i = 0; i < MAP_HEIGHT; i++) {
        pastmap[i] = (char*)malloc((MAP_WIDTH * sizeof(char)));

    }

   
    Frog* frog = (Frog*)malloc(sizeof(Frog));
    initialize_frog(map, frog);

    game(map, basemap, pastmap, max_cars, cars, &config, frog, obstacles);

    
    

    free_memory(map, pastmap, max_cars);
    for (int i = 0; i < max_cars; i++) {
        free(cars[i]);
    }
    free(cars);
    return 0;
}
