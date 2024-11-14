#pragma once
#include "cars.h"


//      CCC
//      CFC <-- car image
//      CCC

void draw_car(char** map, Car* car) {
    int x = (car->x) - 1;
    int y = (car->y) - 1;
    for(int i=0; i<CAR_SIZE; i++){//x
        for(int j=0;j<CAR_SIZE;j++){//y
           update_map(map,x+i,y+j,car->symbol);
        }
    }
    update_map(map, x + 1, y + 1, car->symbol);
}


void generate_random_car_position(Car* car, char** map, int streets[]) {
    srand(time(NULL));
    int x_pos, y_pos, street_number;
    bool empty = false;
    while (!empty) {
        street_number = rand() % STREETS;
        x_pos = streets[street_number];
        y_pos = rand() % (MAP_HEIGHT - 2) + 2;//"center" of the car
        if (map[y_pos - 2][x_pos] == ' ' && map[y_pos + 2][x_pos] == ' ' && map[y_pos][x_pos] == ' ') {//if there is no car already 
            empty = true;
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

    if (friendly) {
        car->friendly = true;
        car->symbol = 'F';
    }
    else {
        car->friendly = false;
        car->symbol = 'E';
    }

    draw_car(map, car);

}
// |     | |     | |     | |     | |     | |     | |     | |     | |     | |     | |     | |     | |     | |     | |     |
void generate_all_cars(Car** cars, char** map, int max_friendly, int max_enemy, int min_cars, int streets[]) {
    int friendly_cars = (rand() % (max_friendly - min_cars)) + min_cars; //generates random amount of
    //friendly cars between max and min amount declared

    int enemy_cars = (rand() % (max_enemy - min_cars)) + min_cars;
    for(int i=0;i<friendly_cars;i++){
        generate_car(cars[i], map, true, streets);
    }
     for(int i=0;i<5;i++){
        generate_car(cars[i],map,false,streets);
    }


}

