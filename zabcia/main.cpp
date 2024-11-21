#include "map.h"
#include "cars.h"
#include "frog.h"
#include "includes.h"



void gameplay(char** map, Car** cars, int max_cars, Frog*frog) {
    int ch;
    while ((ch = getch()) != 'q') {
        for (int i = 0; i < max_cars; i++) {
            move_car(map, cars, i, max_cars);
        }
        print_map(map);
        switch (ch) {
        case 'd':
            jump(map, frog, RIGHT);
            print_map(map);
            break;

        }
    }
    

}
void start_game(char** map, Car** cars, int street_numbers[], int max_friend, int max_enemy, int min, int level, int points, int max_speed) {
    // print_stats(level, points);
    base_map(map, street_numbers);
    print_map(map);
    generate_all_cars(cars, map, max_friend, max_enemy, min, street_numbers, max_speed);
    print_map(map);
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
    char** map = (char**)malloc(MAP_HEIGHT * sizeof(char*));
    for (int i = 0; i < MAP_HEIGHT; i++) {
        map[i] = (char*)malloc((MAP_WIDTH * sizeof(char)));

    }
    start_game(map, cars, street_numbers, max_friend, max_enemy, min, level, points, max_speed);
    int ch;

    Frog* frog = (Frog*)malloc(sizeof(Frog));
    initialize_frog(map, frog);

    gameplay(map, cars, max_cars,frog);


    while ((ch = getch()) != 'q') {

        switch (ch) {
        case 'a':
            //czekamy na ten przycisk
            

            break;

        }
    }

    for (int i = 0; i < MAP_HEIGHT; i++) {
        free(map[i]);
    }
    free(map);
    for (int i = 0; i < max_cars; i++) {
        free(cars[i]);
    }
    free(cars);
    return 0;
}
