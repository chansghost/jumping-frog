#include "map.h"
#include "cars.h"
#include "frog.h"
//s#include "gameplayy.h"
#include "includes.h"



void gameplay(char** map,char**basemap,char**pastmap, Car** cars, int max_cars, Frog*frog) {
    int key;
    bool quit = false;
    while (!quit) {//koniec lvl pozniej tu trzeba wsadzic
        for (int i = 0; i < max_cars; i++) {
            move_car(map, cars, i, max_cars,frog);
        }
        print_map(map, pastmap, basemap);
        if (kbhit()) {
            key = getch();
            switch (key) {
                case 'd':
                    jump(map, frog, RIGHT);
                    print_map(map, pastmap, basemap);
                    break;
                case 'q':
                    quit = true;
                    break;
            }
        }
        
    }
    

}
void start_game(char** map,char**basemap,char**pastmap, Car** cars, int street_numbers[], int max_friend, int max_enemy, int min, int level, int points, int max_speed) {
    // print_stats(level, points);
    base_map(map, street_numbers,basemap);
    print_map(map,pastmap,basemap);
    generate_all_cars(cars, map, max_friend, max_enemy, min, street_numbers, max_speed);
    print_map(map, pastmap, basemap);
    // clrscr();
}


int main() {
    srand(time(NULL));
    //robocze
    int level = 5;
    int points = 15;
    int max_friend = 20;
    int max_enemy = 20;
    int max_cars = max_friend + max_enemy;
    int min = 3;
    int max_speed = 3;
    //robocze

    int street_numbers[STREETS];//0 & even numbers move down, odd numbers move up

    
    
    
    Car** cars = (Car**)malloc(max_cars * sizeof(Car*));
    for (int i = 0; i < max_cars; i++) {
        cars[i] = (Car*)malloc(sizeof(Car));
        reset_car(cars[i], NEW);
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
    //allocate(&map, &pastmap, max_cars);

    start_game(map,basemap,pastmap, cars, street_numbers, max_friend, max_enemy, min, level, points, max_speed);
    int ch;

    Frog* frog = (Frog*)malloc(sizeof(Frog));
    initialize_frog(map, frog);

    gameplay(map,basemap,pastmap, cars, max_cars,frog);


    while ((ch = getch()) != 'q') {

        switch (ch) {
        case 'a':
            //czekamy na ten przycisk
            

            break;

        }
    }

    free_memory(map, pastmap, max_cars);
    for (int i = 0; i < max_cars; i++) {
        free(cars[i]);
    }
    free(cars);
    return 0;
}
