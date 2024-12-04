#include "game_save.h"

void save_game_state(Car** cars,Obstacle** obstacles,Bonus** bonuses, Frog* frog, Stork* stork, Player* player, LevelConfig config) {
    const char* filename = "save.txt";
    FILE* file = NULL;
    fopen_s(&file, filename, "wb");
    if (!file) {
        perror("Cannot open file for writing");
        return;
    }

   
    fwrite(player, sizeof(Player), 1, file);

  
    int max_cars = config.max_enemy + config.max_friend;


    fwrite(&max_cars, sizeof(int), 1, file);
    for (int i = 0; i < max_cars; i++) {
        fwrite(cars[i], sizeof(Car), 1, file);
    }

    fwrite(&(config.max_obstacles), sizeof(int), 1, file);
    for (int i = 0; i < config.max_obstacles; i++) {
        fwrite(obstacles[i], sizeof(Obstacle), 1, file);
    }


    fwrite(&(config.bonuses), sizeof(int), 1, file);
    for (int i = 0; i < config.bonuses; i++) {
        fwrite(bonuses[i], sizeof(Bonus), 1, file);
    }


    fwrite(frog, sizeof(Frog), 1, file);
    fwrite(stork, sizeof(Stork), 1, file);

    fclose(file);
}

void read_game_state(Car*** cars, Obstacle*** obstacles, Bonus*** bonuses, Frog** frog, Stork** stork, Player* player, LevelConfig* config) {
    const char* filename = "save.txt";
    FILE* file = NULL;
    fopen_s(&file, filename, "rb");
    if (!file) {
        perror("Cannot open file for reading");
        return;
    }

    fread(player, sizeof(Player), 1, file);
    int level = player->level;

    manage_config(config, level);

    initialize_memory(cars, obstacles, bonuses, frog, stork, *config);

    int max_cars = config->max_enemy + config->max_friend;
    fread(&max_cars, sizeof(int), 1, file);
    for (int i = 0; i < max_cars; i++) {

        fread((*cars)[i], sizeof(Car), 1, file);
    }


    fread(&(config->max_obstacles), sizeof(int), 1, file);
    for (int i = 0; i < config->max_obstacles; i++) {

        fread((*obstacles)[i], sizeof(Obstacle), 1, file);
    }


    fread(&(config->bonuses), sizeof(int), 1, file);
    for (int i = 0; i < config->bonuses; i++) {

        fread((*bonuses)[i], sizeof(Bonus), 1, file);
    }


    fread(*frog, sizeof(Frog), 1, file);

    fread(*stork, sizeof(Stork), 1, file);

    fclose(file);
}

