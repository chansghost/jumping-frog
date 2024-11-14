#pragma once
#include "cars.h"


//      CCC
//      CFC <-- car image
//      CCC



void reset_car(Car* car,bool friendly) {
    car->x = -1;
    car->y = -1;
    car->symbol = ' ';
    car->friendly = friendly;
    car->street_number = -1;
    car->speed = 0.5;

}
void move_car(char** map, Car* car) {
    draw_car(map, car, REMOVE);
    int newy = car->y;
    

    if ((car->street_number) % 2 == 0) {
        newy += 2;
        car->y = newy;
    }
    else {
        newy -= 2;
        car->y=newy;
    }
    if (within_bounds(map, car->x, car->y)) {
        draw_car(map, car,ADD);
    }
    else {
        reset_car(car,car->friendly);
    }

}



void draw_car(char** map, Car* car,bool clear) {
    int x = (car->x) - 1;
    int y = (car->y) - 1;
    char symbol;
    if (clear) { 
        symbol = ' ';
    }
    else {
        symbol = car->symbol;

    }
    for(int i=0; i<CAR_SIZE; i++){//x
        for(int j=0;j<CAR_SIZE;j++){//y
            update_map(map, x+j, y+i, symbol);
           
        }
    }
}

bool within_bounds(char** map, int x, int y) {
    for (int i = 0; i < CAR_SIZE; i++) {
        if ((x + i) >= MAP_WIDTH || (x - i) < 0) {
            return false;
        }
        if ((y + i) >= MAP_HEIGHT || (y - i) < 0) {
            return false;
        }
    }
    return true;
}
bool check_for_cars(Car** cars,int max_cars,int y) {
    int y2=0;
    for (int i = 0; i < max_cars; i++) {
         y2 = cars[i]->y;
        if (y == y2 || (y - 1) == y2 || (y + 1) == y2) {
            return true;
        }
    }
    return false;
}
void generate_random_car_position(Car* car, char** map, int streets[]) {
    srand(time(NULL));
    int x_pos, y_pos, street_number;
    bool empty = false;
    while (!empty) {
        street_number = rand() % STREETS;
        x_pos = streets[street_number];
        y_pos = rand() % 37;//hardcoded because it doesn't work with a variable name for some reason?

        if (within_bounds(map, x_pos, y_pos)) {
            if (map[y_pos - 1][x_pos] == ' ' && map[y_pos + 1][x_pos] == ' ' && map[y_pos][x_pos] == ' ') {//if there is no car already 
                if (map[y_pos - 2][x_pos] == ' ' && map[y_pos + 2][x_pos] == ' ') {
                    empty = true;
                    map[y_pos][x_pos] = 'O';
                }

            }
        }

    }
    car->street_number = street_number;
    
    car->x = x_pos;
    car->y = y_pos;
}
void generate_car(Car* car, char** map, bool friendly, int streets[]) {
    generate_random_car_position(car, map, streets);
    int x_pos = car->x;
    int y_pos = car->y;
   // 
   // printf("\n");
   
    if (friendly) {
        car->friendly = true;
        car->symbol = 'F';
    }
    else {
        car->friendly = false;
        car->symbol = 'E';
    }

    draw_car(map, car,ADD);

}

void generate_all_cars(Car** cars, char** map, int max_friendly, int max_enemy, int min_cars, int streets[]) {
    int friendly_cars = (rand() % (max_friendly - min_cars)) + min_cars; //generates random amount of
    //friendly cars between max and min amount declared
    int enemy_cars = (rand() % (max_enemy - min_cars)) + min_cars;
    for(int i=0;i<friendly_cars;i++){
        generate_car(cars[i], map, true, streets);
    }
     for(int i=0;i<enemy_cars;i++){
        generate_car(cars[i+friendly_cars],map,false,streets);
    }


}

