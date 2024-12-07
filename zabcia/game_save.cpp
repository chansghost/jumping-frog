#include "game_save.h"


void save_player(FILE* file, Player* player) {
    fprintf(file, "Player\n");
    fprintf(file, "%.*s %d %d\n", player->name_length, player->name, player->points, player->level);
}


void save_cars(FILE* file, Car** cars, int max_cars) {
    fprintf(file, "Cars\n");
    for (int i = 0; i < max_cars; i++) {
        fprintf(file, "%d %d %d %d %d %d %d %d %d %c\n",
            cars[i]->x,
            cars[i]->y,
            cars[i]->street_number,
            cars[i]->car_id,
            cars[i]->speed,
            cars[i]->friendly,
            cars[i]->respawn,
            cars[i]->direction,
            cars[i]->stops,
            cars[i]->symbol);
    }
}


void save_obstacles(FILE* file, Obstacle** obstacles, int max_obstacles) {
    fprintf(file, "Obstacles\n");
    for (int i = 0; i < max_obstacles; i++) {
        fprintf(file, "%d %d %d\n", obstacles[i]->x, obstacles[i]->y, obstacles[i]->obstacle_id);
    }
}


void save_bonuses(FILE* file, Bonus** bonuses, int max_bonuses) {
    fprintf(file, "Bonuses\n");
    for (int i = 0; i < max_bonuses; i++) {
        fprintf(file, "%d %d %d %d %d\n", bonuses[i]->x, bonuses[i]->y, bonuses[i]->collected,
            bonuses[i]->disappeared, bonuses[i]->bonus_id);
    }
}


void save_frog(FILE* file, Frog* frog) {
    fprintf(file, "Frog\n");
    fprintf(file, "%d %d %d %d %c\n", frog->x, frog->y, frog->jump_distance, frog->car_index, frog->map_piece);
}


void save_stork(FILE* file, Stork* stork) {
    fprintf(file, "Stork\n");
    fprintf(file, "%d %d %lf %lf %d ", stork->x, stork->y, stork->speed, stork->time_spawn, stork->exists);
    int counter = 0;
    for (int i = 0; i < STORK_SIZE; i++) {  // x
        for (int j = 0; j < STORK_SIZE; j++) {  // y
            fprintf(file, "%c", stork->map_piece[counter]);
            counter++;
        }
    }
    fprintf(file, " %lf\n", stork->gained_speed);
}






void save_game_state(Car** cars, Obstacle** obstacles, Bonus** bonuses, Frog* frog, Stork* stork, Player* player, LevelConfig config) {
    char c;
    char filename[MAX_NAME];
    printf("Enter the filename (max %d characters): ", MAX_NAME);

    for (int i = 0; i < MAX_NAME; i++) {
        c = getch();
        if (c == '\r' || c == '\n') {
            filename[i] = '\0';
            break;
        }
        else {
            filename[i] = c;
            putch(c);
        }
    }
    FILE* file = NULL;
    fopen_s(&file, filename, "w");
    if (!file) {
        perror("Cannot open file for writing");
        return;
    }

    
    save_player(file, player);


    
    int max_cars = config.max_enemy + config.max_friend;

    
    save_cars(file, cars, config.max_enemy + config.max_friend);
    save_obstacles(file, obstacles, config.max_obstacles);
    save_bonuses(file, bonuses, config.bonuses);
    save_frog(file, frog);
    save_stork(file, stork);


    fclose(file);

}



void read_player(FILE* file, Player* player) {
    char section[20];
    fscanf_s(file, "%19s", section, (unsigned)_countof(section));
    fscanf_s(file, "%s %d %d", player->name, (unsigned)_countof(player->name), &player->points, &player->level);
}


void read_cars(FILE* file, Car*** cars, int max_cars) {
    char section[20];
    fscanf_s(file, "%19s", section, (unsigned)_countof(section));

    for (int i = 0; i < max_cars; i++) {
        fscanf_s(file, "%d %d %d %d %d %d %d %d %d %c",
            &(*cars)[i]->x,
            &(*cars)[i]->y,
            &(*cars)[i]->street_number,
            &(*cars)[i]->car_id,
            &(*cars)[i]->speed,
            &(*cars)[i]->friendly,
            &(*cars)[i]->respawn,
            &(*cars)[i]->direction,
            &(*cars)[i]->stops,
            &(*cars)[i]->symbol);
    }
}


void read_obstacles(FILE* file, Obstacle*** obstacles, int max_obstacles) {
    char section[20];
    fscanf_s(file, "%19s", section, (unsigned)_countof(section));

    for (int i = 0; i < max_obstacles; i++) {
        fscanf_s(file, "%d %d %d", &(*obstacles)[i]->x, &(*obstacles)[i]->y, &(*obstacles)[i]->obstacle_id);
    }
}


void read_bonuses(FILE* file, Bonus*** bonuses, int max_bonuses) {
    char section[20];
    fscanf_s(file, "%19s", section, (unsigned)_countof(section));

    for (int i = 0; i < max_bonuses; i++) {
        fscanf_s(file, "%d %d %d %d %d",
            &(*bonuses)[i]->x, &(*bonuses)[i]->y, &(*bonuses)[i]->collected,
            &(*bonuses)[i]->disappeared, &(*bonuses)[i]->bonus_id);
    }
}


void read_frog(FILE* file, Frog** frog) {
    char section[20];
    fscanf_s(file, "%19s", section, (unsigned)_countof(section));

    fscanf_s(file, "%d %d %d %d %*c%c",
        &(*frog)->x,
        &(*frog)->y,
        &(*frog)->jump_distance,
        &(*frog)->car_index,
        &(*frog)->map_piece, 0);
}


void read_stork(FILE* file, Stork** stork) {
    char section[20];
    fscanf_s(file, "%19s", section, (unsigned)_countof(section));

    fscanf_s(file, "%d %d %lf %lf %d", &(*stork)->x, &(*stork)->y, &(*stork)->speed,
        &(*stork)->time_spawn, &(*stork)->exists);

    int counter = 3;
    for (int i = 0; i < STORK_SIZE; i++) {  // x
        for (int j = 0; j < STORK_SIZE; j++) {  // y
            fscanf_s(file, "%c", &(*stork)->map_piece[counter]);
            counter--;
        }
    }

    fscanf_s(file, " %lf", &(*stork)->gained_speed);
}


void read_game_state(Car*** cars, Obstacle*** obstacles, Bonus*** bonuses, Frog** frog, Stork** stork, Player* player, LevelConfig* config) {
    char c;
    char filename[MAX_NAME];
    printf("Enter the filename (max %d characters): ", MAX_NAME);

 
    for (int i = 0; i < MAX_NAME; i++) {
        c = getch(); 
        if (c == '\r' || c == '\n') {  
            filename[i] = '\0';   
            break;               
        }
        else {
            filename[i] = c;       
            putch(c);               
        }
    }

    FILE* file = NULL;
    fopen_s(&file, filename, "r");
    if (!file) {
        perror("Cannot open file for reading");
        return;
    }

    char section[20];
    

    
    read_player(file, player);

    
    manage_config(config, player->level);
    initialize_memory(cars, obstacles, bonuses, frog, stork, *config);

    int max_cars = config->max_enemy + config->max_friend;
    read_cars(file, cars, max_cars);
    read_obstacles(file, obstacles, config->max_obstacles);
    read_bonuses(file, bonuses, config->bonuses);
    read_frog(file, frog);
    read_stork(file, stork);



    fclose(file);
}


