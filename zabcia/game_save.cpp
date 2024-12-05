#include "game_save.h"

void save_game_state(Car** cars,Obstacle** obstacles,Bonus** bonuses, Frog* frog, Stork* stork, Player* player, LevelConfig config) {
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

    FILE* ranking_file = NULL;
    fopen_s(&ranking_file, "ranking.txt", "a");
    if (!ranking_file) {
        perror("Cannot open ranking file");
        return;
    }

    // Zapisujemy nazwê gracza i jego punkty
    fprintf(ranking_file, "%s %d\n", player->name, player->points);

    fclose(ranking_file);
}

void read_game_state(Car*** cars, Obstacle*** obstacles, Bonus*** bonuses, Frog** frog, Stork** stork, Player* player, LevelConfig* config) {
    char c;
    char filename[MAX_NAME];
    printf("Enter the filename (max %d characters): ", MAX_NAME);

    // Wczytujemy nazwê pliku znak po znaku
    for (int i = 0; i < MAX_NAME; i++) {
        c = getch();  // Oczekujemy na wciœniêcie klawisza przez u¿ytkownika
        if (c == '\r' || c == '\n') {  // Je¿eli naciœniêto Enter (powrót karetki)
            filename[i] = '\0';    // Koñczymy ³añcuch znaków
            break;                 // Koñczymy wczytywanie
        }
        else {
            filename[i] = c;       // Zapisujemy wprowadzone znaki
            putch(c);               // Wyœwietlamy je na ekranie
        }
    }

    
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

