#include "game_save.h"

void save_game(char** map, char** pastmap, Obstacle** obstacles, Car** cars, Stork* stork, Frog* frog, Bonus** bonuses, Player* player,LevelConfig config) {
    const char* filename = "save.txt";
    FILE* file = NULL;
    fopen_s(&file, filename, "w");
	fprintf(file, "Name:\n");
	for (int i = 0; i < MAX_NAME; i++) {
		fprintf(file, "%c", player->name[i]);
	}
	fprintf(file, "Points: %d\n",player->points);
	fprintf(file, "Won: %d\n", player->won ? 1 : 0);
	fprintf(file, "Level: %d\n", player->level);
	
    save_map(map, file);

    save_cars(cars, file,config);

    save_frog(frog, file);

    save_stork(stork, file);

    save_obstacles(obstacles, file, config);
	
    save_bonuses(bonuses, file, config);

}
void save_map(char** map,FILE*file) {
    fprintf(file, "Map:\n");
    for (int i = 0; i < MAP_HEIGHT; i++) { //y
        for (int j = 0; j < MAP_WIDTH; j++) {//x
            fprintf(file, "%c\n", map[i][j]);
        }
    }
}

void save_cars(Car** cars, FILE* file,LevelConfig config) {
    fprintf(file, "Cars:\n");
    int max_cars = config.max_enemy + config.max_friend;
    for (int i = 0; i < max_cars; i++) {
        fprintf(file, "Index: %d\n", cars[i]->car_id);
        fprintf(file, "X: %d\n", cars[i]->x);
        fprintf(file, "Y: %d\n", cars[i]->y);
        fprintf(file, "Speed: %d\n", cars[i]->speed);
        fprintf(file, "Street: %d\n", cars[i]->street_number);
        fprintf(file, "Respawn: %d\n", cars[i]->respawn);
        fprintf(file, "Direction: %d\n", cars[i]->direction);
        fprintf(file, "Stops: %d\n", cars[i]->stops ? 1 : 0);
        fprintf(file, "Friendly: %d\n", cars[i]->friendly ? 1 : 0);
    }
}

void save_frog(Frog* frog, FILE* file) {
    fprintf(file, "Frog:\n");
    fprintf(file, "X: %d\n", frog->x);
    fprintf(file, "Y: %d\n", frog->y);
    fprintf(file, "Jump: %d\n", frog->jump_distance);
    fprintf(file, "Car_index: %d\n", frog->car_index);
    fprintf(file, "Map_piece: %c\n", frog->map_piece);
    fprintf(file, "Dead: %d\n", frog->dead ? 1 : 0);
}

void save_stork(Stork* stork, FILE* file) {
    fprintf(file, "Stork:\n");
    fprintf(file, "X: %d\n", stork->x);
    fprintf(file, "Y: %d\n", stork->y);
    fprintf(file, "Speed: %lf\n", stork->speed);
    fprintf(file, "Exists: %d\n", stork->exists ? 1 : 0);
    fprintf(file, "Time_spawn: %lf\n", stork->time_spawn);
    fprintf(file, "Gained_speed: %lf\n", stork->gained_speed);
    fprintf(file, "Map_pieces:\n");
    for (int i = 0; i < STORK_SIZE * 2; i++) {
        fprintf(file, "%c\n", stork->map_piece[i]);
    }
}

void save_obstacles(Obstacle** obstacles, FILE* file, LevelConfig config) {
    fprintf(file, "Obstacles:\n");
    for (int i = 0; i < config.max_obstacles; i++) {
        fprintf(file, "Index: %d\n", obstacles[i]->obstacle_id);
        fprintf(file, "X: %d\n", obstacles[i]->x);
        fprintf(file, "Y: %d\n", obstacles[i]->y);
    }
}

void save_bonuses(Bonus** bonuses, FILE* file, LevelConfig config) {
    fprintf(file, "Bonuses:\n");
    for (int i = 0; i < config.bonuses; i++) {
        fprintf(file, "Index: %d\n", bonuses[i]->bonus_id);
        fprintf(file, "X: %d\n", bonuses[i]->x);
        fprintf(file, "Y: %d\n", bonuses[i]->y);
        fprintf(file, "Time: %d\n", bonuses[i]->time_to_collect);
        fprintf(file, "Collected: %d\n", bonuses[i]->collected ? 1 : 0);
        fprintf(file, "Disappeared: %d\n", bonuses[i]->disappeared ? 1 : 0);
    }
}



void load_game(char** map, char** pastmap,Obstacle** obstacles, Car** cars, Stork* stork, Frog* frog,Bonus** bonuses, Player* player,LevelConfig config) {

    const char* filename = "save.txt";
    FILE* file = NULL;
    fopen_s(&file, filename, "r");
    if (!file) {
        printf("Nie mo¿na otworzyæ pliku do odczytu.\n");
        return;
    }

    
    fscanf_s(file, "Name:\n");
    for (int i = 0; i < MAX_NAME; i++) {
        fscanf_s(file, "%c", &player->name[i],sizeof(char));
    }
    fscanf_s(file, "Points: %d\n", &player->points);
    fscanf_s(file, "Won: %d\n", &player->won);
    fscanf_s(file, "Level: %d\n", &player->level);

    manage_config(&config, player->level);

    
    fscanf_s(file, "Map:\n");
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            fscanf_s(file, "%c\n", &map[i][j], sizeof(char));
        }
    }

    
    fscanf_s(file, "Cars:\n");
    int max_cars = config.max_enemy + config.max_friend;
    for (int i = 0; i < max_cars; i++) {
        fscanf_s(file, "Index: %d\n", &cars[i]->car_id);
        fscanf_s(file, "X: %d\n", &cars[i]->x);
        fscanf_s(file, "Y: %d\n", &cars[i]->y);
        fscanf_s(file, "Speed: %d\n", &cars[i]->speed);
        fscanf_s(file, "Street: %d\n", &cars[i]->street_number);
        fscanf_s(file, "Respawn: %d\n", &cars[i]->respawn);
        fscanf_s(file, "Direction: %d\n", &cars[i]->direction);
        fscanf_s(file, "Stops: %d\n", &cars[i]->stops);
        fscanf_s(file, "Friendly: %d\n", &cars[i]->friendly);
    }

    
    fscanf_s(file, "Frog:\n");
    fscanf_s(file, "X: %d\n", &frog->x);
    fscanf_s(file, "Y: %d\n", &frog->y);
    fscanf_s(file, "Jump: %d\n", &frog->jump_distance);
    fscanf_s(file, "Car_index: %d\n", &frog->car_index);
    fscanf_s(file, "Map_piece: %c\n", &frog->map_piece);
    fscanf_s(file, "Dead: %d\n", &frog->dead);

    
    fscanf_s(file, "Stork:\n");
    fscanf_s(file, "X: %d\n", &stork->x);
    fscanf_s(file, "Y: %d\n", &stork->y);
    fscanf_s(file, "Speed: %lf\n", &stork->speed);
    fscanf_s(file, "Exists: %d\n", &stork->exists);
    fscanf_s(file, "Time_spawn: %lf\n", &stork->time_spawn);
    fscanf_s(file, "Gained_speed: %lf\n", &stork->gained_speed);
    fscanf_s(file, "Map_pieces:\n");
    for (int i = 0; i < STORK_SIZE * 2; i++) {
        fscanf_s(file, "%c\n", &stork->map_piece[i], sizeof(char));
    }

    
    fscanf_s(file, "Obstacles:\n");
    for (int i = 0; i < config.max_obstacles; i++) {
        fscanf_s(file, "Index: %d\n", &obstacles[i]->obstacle_id);
        fscanf_s(file, "X: %d\n", &obstacles[i]->x);
        fscanf_s(file, "Y: %d\n", &obstacles[i]->y);
    }

    
    fscanf_s(file, "Bonuses:\n");
    for (int i = 0; i < config.bonuses; i++) {
        fscanf_s(file, "Index: %d\n", &bonuses[i]->bonus_id);
        fscanf_s(file, "X: %d\n", &bonuses[i]->x);
        fscanf_s(file, "Y: %d\n", &bonuses[i]->y);
        fscanf_s(file, "Time: %d\n", &bonuses[i]->time_to_collect);
        fscanf_s(file, "Collected: %d\n", &bonuses[i]->collected);
        fscanf_s(file, "Disappeared: %d\n", &bonuses[i]->disappeared);
    }

    fclose(file);
}



