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
    int level;
    int points = 15;
    level = chooseLevel();

    const char* filename = "config.txt";
    LevelConfig config;
    FILE* file = NULL;
    fopen_s(&file, filename, "r");
    read_lvl_config(file, level, &config);
    fclose(file);

    int max_cars = config.max_friend + config.max_enemy;

    
    
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
    frog->jump_distance = config.frog_jump;
    //game(map, basemap, pastmap, max_cars, cars, &config, frog, obstacles);
    int sidewalks[SIDEWALKS];
    int street_numbers[STREETS];
    base_map(map, street_numbers, basemap, sidewalks);
    print_map(map, pastmap, basemap);
    generate_all_cars(cars, map, config.max_friend, config.max_enemy, config.minimum_cars, street_numbers, config.max_speed);
    generate_obstacles(obstacles, sidewalks, map, config.max_obstacles);
    print_map(map, pastmap, basemap);
    gameplay(map, basemap, pastmap, cars, max_cars, frog, street_numbers, config.max_speed, config.frog_time);

    
    

    free_memory(map, pastmap, max_cars);
    for (int i = 0; i < max_cars; i++) {
        free(cars[i]);
    }
    free(cars);
    return 0;
}
