#include "memory_handling.h"

void initialize_map(char*** basemap, char*** map, char*** pastmap) {
    *basemap = (char**)malloc(MAP_HEIGHT * sizeof(char*));
    *map = (char**)malloc(MAP_HEIGHT * sizeof(char*));
    *pastmap = (char**)malloc(MAP_HEIGHT * sizeof(char*));
    for (int i = 0; i < MAP_HEIGHT; i++) {
        (*basemap)[i] = (char*)malloc(MAP_WIDTH * sizeof(char));
        (*map)[i] = (char*)malloc(MAP_WIDTH * sizeof(char));
        (*pastmap)[i] = (char*)malloc(MAP_WIDTH * sizeof(char));
    }

}

void initialize_memory(
    Car*** cars,
    Obstacle*** obstacles,
    Bonus*** bonuses, Frog** frog, Stork** stork, LevelConfig config) {

    int max_cars = config.max_enemy + config.max_friend;
    *cars = (Car**)malloc(max_cars * sizeof(Car*));
    for (int i = 0; i < max_cars; i++) {
        (*cars)[i] = (Car*)malloc(sizeof(Car));
        reset_car((*cars)[i], NEW);
        (*cars)[i]->car_id = i;
    }
    *obstacles = (Obstacle**)malloc(config.max_obstacles * sizeof(Obstacle*));
    for (int i = 0; i < config.max_obstacles; i++) {
        (*obstacles)[i] = (Obstacle*)malloc(sizeof(Obstacle));
        initialize_obstacle((*obstacles)[i]);
        (*obstacles)[i]->obstacle_id=i;
    }

    *bonuses = (Bonus**)malloc(config.bonuses * sizeof(Bonus*));
    for (int i = 0; i < config.bonuses; i++) {
        (*bonuses)[i] = (Bonus*)malloc(sizeof(Bonus));
        initialize_bonus((*bonuses)[i]);
        (*bonuses)[i]->bonus_id=i;
    }


    *stork = (Stork*)malloc(sizeof(Stork));
    initialize_stork(*stork);

    *frog = (Frog*)malloc(sizeof(Frog));
    initialize_frog(*frog);
}