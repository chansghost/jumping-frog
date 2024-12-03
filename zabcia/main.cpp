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
#include "game_save.h"

#include "memory_handling.h"
#define _CRT_SECURE_NO_WARNINGS

int main() {
   // Player* player = (Player*)malloc(sizeof(Player));
   // initialize_player(player);

   // srand(time(NULL));
   // int level;
   // int points = 15;

   //// new_player(player);

   // level = chooseLevel();
   // LevelConfig config;
   // manage_config(&config,level);

   // int max_cars = config.max_friend + config.max_enemy;
   // Car** cars;
   // Obstacle** obstacles;
   // Bonus** bonuses;
   // Stork* stork;
   // Frog* frog;
   // initialize_memory(&cars, &obstacles, &bonuses, &frog, &stork, config);

   // char** basemap;
   // char** map;
   // char** pastmap;
   // initialize_map(&basemap, &map, &pastmap);
   // 

   //
   // 


   // 
   // 
   // game(map, basemap, pastmap, cars, config, frog, obstacles,bonuses,player,stork);



    start();
    
    

    /*for (int i = 0; i < MAP_HEIGHT; i++) {
        free(map[i]);
    }
    free(map);
    for (int i = 0; i < MAP_HEIGHT; i++) {
        free(pastmap[i]);
    }
    free(pastmap);*/
    return 0;
}
