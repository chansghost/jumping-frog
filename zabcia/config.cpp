#include "config.h"

void read_lvl_config(FILE* file, int level, LevelConfig* config) {
    int current_level = -1;
    char first_char[6]; 
    while (!feof(file)) {
        if (fscanf_s(file, " level %d", &current_level) == 1) {
            if (current_level == level) {
                fscanf_s(file, " max_friend %d", &config->max_friend);
                fscanf_s(file, " max_enemy %d", &config->max_enemy);
                fscanf_s(file, " minimum_cars %d", &config->minimum_cars);
                fscanf_s(file, " max_speed %d", &config->max_speed);
                fscanf_s(file, " max_obstacles %d", &config->max_obstacles);
                fscanf_s(file, " frog_jump %d", &config->frog_jump);
                fscanf_s(file, " frog_time %d", &config->frog_time);

                fscanf_s(file, " stork %5s", first_char, sizeof(first_char)); 

                if (first_char[0] == 't' && first_char[1] == 'r' &&
                    first_char[2] == 'u' && first_char[3] == 'e' && first_char[4] == '\0') {
                    config->stork = true;
                }
                else {
                    config->stork = false;
                }
                return; 
            }
        }
        while (fgetc(file) != '\n' && !feof(file));
    }
}

void printLevel(LevelConfig config, int currentlevel) {
    printf("Level Configuration: ");
    printf("%d\n",currentlevel);
    printf("Max Friends: %d\n", config.max_friend);
    printf("Max Enemies: %d\n", config.max_enemy);
    printf("Minimum Cars: %d\n", config.minimum_cars);
    printf("Max Speed: %d\n", config.max_speed);
    printf("Max Obstacles: %d\n", config.max_obstacles);
    printf("Frog Jump: %d\n", config.frog_jump);
    printf("Frog Time: %d\n", config.frog_time);
    printf("Stork: %s\n", config.stork ? "true" : "false");
   
}

int writeLevelConfig(FILE* file, int level, LevelConfig* config) {//only for tests
    return fprintf(file,
        "%d:\n"
        "level %d\n"
        "max_friend %d\n"
        "max_enemy %d\n"
        "minimum_cars %d\n"
        "max_speed %d\n"
        "max_obstacles %d\n"
        "stork %s\n"
        "frog_jump %d\n"
        "frog_time %d\n\n",
        level, level, config->max_friend, config->max_enemy, config->minimum_cars,
        config->max_speed, config->max_obstacles,
        config->stork ? "true" : "false", config->frog_jump, config->frog_time);
}