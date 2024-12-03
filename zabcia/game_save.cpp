#include "game_save.h"

void save_game_state(Car** cars,Obstacle** obstacles,Bonus** bonuses, Frog* frog, Stork* stork, Player* player, LevelConfig config) {
    const char* filename = "save.txt";
    FILE* file = NULL;
    fopen_s(&file, filename, "wb");
    if (!file) {
        perror("Cannot open file for writing");
        return;
    }

    // Zapis gracza (Player)
    fwrite(player, sizeof(Player), 1, file);

    // Zapis konfiguracji poziomu
    int max_cars = config.max_enemy + config.max_friend;

    // Zapis samochodów
    fwrite(&max_cars, sizeof(int), 1, file);
    for (int i = 0; i < max_cars; i++) {
        fwrite(cars[i], sizeof(Car), 1, file);
    }

    // Zapis przeszkód
    fwrite(&(config.max_obstacles), sizeof(int), 1, file);
    for (int i = 0; i < config.max_obstacles; i++) {
        fwrite(obstacles[i], sizeof(Obstacle), 1, file);
    }

    // Zapis bonusów
    fwrite(&(config.bonuses), sizeof(int), 1, file);
    for (int i = 0; i < config.bonuses; i++) {
        fwrite(bonuses[i], sizeof(Bonus), 1, file);
    }

    // Zapis ¿aby i bociana
    fwrite(frog, sizeof(Frog), 1, file);
    fwrite(stork, sizeof(Stork), 1, file);

    fclose(file);
}

void load_game_state(Car*** cars, Obstacle*** obstacles, Bonus*** bonuses, Frog** frog, Stork** stork, Player* player, LevelConfig* config) {
    const char* filename = "save.txt";
    FILE* file = NULL;
    fopen_s(&file, filename, "rb");
    if (!file) {
        perror("Cannot open file for reading");
        return;
    }

    // Odczyt gracza (Player)
    fread(player, sizeof(Player), 1, file);
    int level = player->level;

    manage_config(config, level);
    // Odczyt konfiguracji poziomu
    initialize_memory(cars, obstacles, bonuses, frog, stork, *config);
    // Odczyt samochodów
    int max_cars = config->max_enemy + config->max_friend;
    fread(&max_cars, sizeof(int), 1, file);
    for (int i = 0; i < max_cars; i++) {
        //(*cars)[i] = (Car*)malloc(sizeof(Car));
        fread((*cars)[i], sizeof(Car), 1, file);
    }

    // Odczyt przeszkód
    fread(&(config->max_obstacles), sizeof(int), 1, file);
    for (int i = 0; i < config->max_obstacles; i++) {
        //(*obstacles)[i] = (Obstacle*)malloc(sizeof(Obstacle));
        fread((*obstacles)[i], sizeof(Obstacle), 1, file);
    }

    // Odczyt bonusów
    fread(&(config->bonuses), sizeof(int), 1, file);
    for (int i = 0; i < config->bonuses; i++) {
      //  (*bonuses)[i] = (Bonus*)malloc(sizeof(Bonus));
        fread((*bonuses)[i], sizeof(Bonus), 1, file);
    }

    // Odczyt ¿aby i bociana
    fread(*frog, sizeof(Frog), 1, file);

    fread(*stork, sizeof(Stork), 1, file);

    fclose(file);
}

