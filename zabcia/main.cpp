#include "map.h"
#include "cars.h"
#include "defines.h"



// initscr();              // Startuje tryb ncurses
// cputs("Hello, ncurses!"); // Wyœwietla tekst
// refresh();              // Odœwie¿a ekran
// getch();                // Czeka na naciœniêcie klawisza
// endwin();               // Koñczy tryb ncurses
// return 0;

//cars need to be 4 fields tall, 3 fields wide


int main() {
    srand(time(NULL));
    //robocze
    int level = 5;
    int points = 15;
    int max_friend = 15;
    int max_enemy = 15;
    int max_cars = max_friend + max_enemy;
    int min = 3;
    //robocze

    int street_numbers[STREETS];//0 & even numbers move down, odd numbers move up
    Car** cars = (Car**)malloc(max_cars * sizeof(Car*));
    for (int i = 0; i < max_cars; i++) {
        cars[i] = (Car*)malloc(sizeof(Car));
    }
    //struct Car*enemy_cars= malloc(max_enemy*sizeof(Car*));
     char**map=(char**)malloc(MAP_WIDTH*sizeof(char*));
     for (int i = 0; i < MAP_WIDTH; i++) {
         map[i] = (char*)malloc((MAP_HEIGHT * sizeof(char)));

     }


    
   /*/ for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            printf("%p\n", (void*)&map[i][j]);
        }
    }*/
    // initscr();
    // start_color();
    // keypad(stdscr, TRUE); 
    // noecho();   
    print_stats(level,points);
    base_map(map, street_numbers);
    print_map(map);
    generate_all_cars(cars,map,max_friend,max_enemy,min,street_numbers);

    int ch;

    while ((ch = getch()) != 'q') {
        switch (ch) {
        case 'a':
            print_map(map);
            break;

        }
    }

    

    
    for (int i = 0; i < MAP_WIDTH; i++) {
        free(map[i]);
    }
    free(map);
    for (int i = 0; i < max_cars; i++) {
        free(cars[i]);
    }
    free(cars);
    return 0;
}
