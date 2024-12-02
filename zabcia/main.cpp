#include "map.h"
#include "cars.h"
#include "frog.h"
#include "gameplayy.h"
#include "obstacle.h"
#include "config.h"
#include "includes.h"
#include "bonus.h"
#include "player.h"
#include "stork.h"
#define _CRT_SECURE_NO_WARNINGS

int main() {
    Player* player = (Player*)malloc(sizeof(Player));
    initialize_player(player);

    srand(time(NULL));
    int level;
    int points = 15;

   // new_player(player);

    level = chooseLevel();
    LevelConfig config;
    manage_config(&config,level);

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
    Bonus** bonuses= (Bonus**)malloc(config.bonuses * sizeof(Bonus*));
    for (int i = 0; i < config.bonuses; i++) {
        bonuses[i] = (Bonus*)malloc(sizeof(Bonus));
        initialize_bonus(bonuses[i]);
    }

   
    Frog* frog = (Frog*)malloc(sizeof(Frog));
    initialize_frog(map, frog);

    Stork* stork = (Stork*)malloc(sizeof(stork));
    initialize_stork(stork);

    
    
    game(map, basemap, pastmap, cars, config, frog, obstacles,bonuses,player,stork);

    
    
    

    for (int i = 0; i < MAP_HEIGHT; i++) {
        free(map[i]);
    }
    free(map);
    for (int i = 0; i < MAP_HEIGHT; i++) {
        free(pastmap[i]);
    }
    free(pastmap);
    return 0;
}
