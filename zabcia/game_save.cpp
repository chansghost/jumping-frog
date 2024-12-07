#include "game_save.h"

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

    
    fprintf(file, "Player\n");
    fprintf(file, "%.*s %d %d\n", player->name_length, player->name, player->points, player->level);


    
    int max_cars = config.max_enemy + config.max_friend;

    
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


    
    fprintf(file, "Obstacles\n");
    for (int i = 0; i < config.max_obstacles; i++) {
        fprintf(file, "%d %d %d\n", obstacles[i]->x, obstacles[i]->y, obstacles[i]->obstacle_id);
    }

    
    fprintf(file, "Bonuses\n");
    for (int i = 0; i < config.bonuses; i++) {
        fprintf(file, "%d %d %d %d %d\n", bonuses[i]->x, bonuses[i]->y, bonuses[i]->collected,
            bonuses[i]->disappeared, bonuses[i]->bonus_id);
    }

    
    fprintf(file, "Frog\n");
    fprintf(file, "%d %d %d %d %c\n", frog->x, frog->y, frog->jump_distance, frog->car_index,frog->map_piece);

    
    fprintf(file, "Stork\n");
    fprintf(file, "%d %d %lf %lf %d ", stork->x, stork->y, stork->speed, stork->time_spawn, stork->exists);
    int counter=0;
    for (int i = 0; i < STORK_SIZE; i++) {//x
        for (int j = 0; j < STORK_SIZE; j++) {//y
            fprintf(file, "%c", stork->map_piece[counter]);
            counter++;
        }
    }
    fprintf(file, " %lf\n", stork->gained_speed);


    fclose(file);

    
    FILE* ranking_file = NULL;
    fopen_s(&ranking_file, "ranking.txt", "a");
    if (!ranking_file) {
        perror("Cannot open ranking file");
        return;
    }
    fprintf(ranking_file, "%s %d\n", player->name, player->points);
    fclose(ranking_file);
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
    

    
    fscanf_s(file, "%19s", section, (unsigned)_countof(section)); 
    fscanf_s(file, "%s %d %d", player->name, (unsigned)_countof(player->name), &player->points, &player->level);

    
    manage_config(config, player->level);
    initialize_memory(cars, obstacles, bonuses, frog, stork, *config);
    int max_cars=config->max_enemy+config->max_friend;

    

    
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


    
    fscanf_s(file, "%19s", section, (unsigned)_countof(section));
    for (int i = 0; i < config->max_obstacles; i++) {
        fscanf_s(file, "%d %d %d", &(*obstacles)[i]->x, &(*obstacles)[i]->y, &(*obstacles)[i]->obstacle_id);
    }

   
    fscanf_s(file, "%19s", section, (unsigned)_countof(section));
    for (int i = 0; i < config->bonuses; i++) {
        fscanf_s(file, "%d %d %d %d %d",
            &(*bonuses)[i]->x, &(*bonuses)[i]->y, &(*bonuses)[i]->collected,
            &(*bonuses)[i]->disappeared, &(*bonuses)[i]->bonus_id);
    }

    
    fscanf_s(file, "%19s", section, (unsigned)_countof(section));
    fscanf_s(file, "%d %d %d %d %*c%c", 
        &(*frog)->x, 
        &(*frog)->y, 
        &(*frog)->jump_distance, 
        &(*frog)->car_index, 
        &(*frog)->map_piece, 0);

    
    fscanf_s(file, "%19s", section, (unsigned)_countof(section));  

    fscanf_s(file, "%d %d %lf %lf %d", &(*stork)->x, &(*stork)->y, &(*stork)->speed,
        &(*stork)->time_spawn, &(*stork)->exists);


    int counter=3;
    for (int i = 0; i < STORK_SIZE; i++) {//x
        for (int j = 0; j < STORK_SIZE; j++) {//y
            fscanf_s(file, "%c", &(*stork)->map_piece[counter]);
            counter--;
        }
    }

    fscanf_s(file, " %lf", &(*stork)->gained_speed);



    fclose(file);
}


