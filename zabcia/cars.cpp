#pragma once
#include "cars.h"


//      CCC
//      CFC <-- car image
//      CCC


void car_collision(char** map, Car* org_car, Car* other_car) {
    render_car(map, org_car, REMOVE);
    render_car(map, other_car, REMOVE);
    reset_car(org_car, org_car->friendly);
    reset_car(other_car, other_car->friendly);
    //pozniej zrobie zeby sie rozlatywa³y na obstacles ktore
    //sie usuwaj¹ po jakimœ czasie
}

int return_car(int x, int y, Car** cars, int max_cars) {
    for (int i = 0; i < max_cars; i++) {
        if (cars[i]->x == x) {//if we found car on the street we're currently exploring
            if (cars[i]->y == y || cars[i]->y == y - 1 || cars[i]->y == y + 1) {

            }
        }
    }
}


bool check_for_cars(char** map, Car** cars, int max_cars, int index) {
    int y2 = 0;
    int y = cars[index]->y;
    int street = cars[index]->x;
    if ((cars[index]->street_number) % 2 == 0) {
        y += 1;
    }
    else {
        y -= 1;
    }
    for (int i = 0; i < max_cars; i++) {
        if (!(cars[i]->y == -1) && i != index && cars[i]->x == street) {//if initialized
            y2 = cars[i]->y;
            if (y == y2 || (y - 1) == y2 || (y + 1) == y2) {
                car_collision(map, cars[index], cars[i]);
                return true;
            }
        }
    }
    return false;
}

void reset_car(Car* car, bool friendly) {
    car->x = -1;
    car->y = -1;
    car->symbol = ' ';
    car->friendly = friendly;
    car->street_number = -1;
    car->speed = 0;

}
void move_car(char** map, Car** cars, int index, int max_cars,Frog*frog) {
    if (!(check_for_cars(map, cars, max_cars, index))) {
        Car* car = cars[index];
        if (!(car->x == -1)) {//if car is initialized on the map
            render_car(map, car, REMOVE);
            int newy = car->y;

            if ((car->street_number) % 2 == 0) {
                newy += car->speed;
                car->y = newy;
            }
            else {
                newy -= car->speed;
                car->y = newy;
            }
            if (car_bounds(map, car->x, car->y)) {
                render_car(map, car, ADD);
                if (car->car_id == frog->car_index) {
                    move_frog(map, frog, car->x, car->y);
                }
            }
            else {
                reset_car(car, car->friendly);
            }
        }
    }
}



void render_car(char** map, Car* car, bool clear) {
    int x = (car->x) - 1;
    int y = (car->y) - 1;
    char symbol;
    if (clear) {
        symbol = ' ';
    }
    else {
        symbol = car->symbol;

    }
    for (int i = 0; i < CAR_SIZE; i++) {//x
        for (int j = 0; j < CAR_SIZE; j++) {//y
            update_map(map, x + j, y + i, symbol);

        }
    }
}

bool car_bounds(char** map, int x, int y) {
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

void generate_random_car_position(Car* car, char** map, int streets[]) {
    srand(time(NULL));
    int x_pos, y_pos, street_number;
    bool empty = false;
    while (!empty) {
        street_number = rand() % STREETS;
        x_pos = streets[street_number];
        y_pos = rand() % 37;//hardcoded because it doesn't work with a variable name for some reason?

        if (car_bounds(map, x_pos, y_pos)) {
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
void generate_car(Car* car, char** map, bool friendly, int streets[], int max_speed) {
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
    int random_speed = (rand() % (max_speed - 1)) + 1;
    car->speed = random_speed;

    render_car(map, car, ADD);

}

void generate_all_cars(Car** cars, char** map, int max_friendly, int max_enemy, int min_cars, int streets[], int max_speed) {
    int friendly_cars = (rand() % (max_friendly - min_cars)) + min_cars; //generates random amount of
    //friendly cars between max and min amount declared
    int enemy_cars = (rand() % (max_enemy - min_cars)) + min_cars;
    for (int i = 0; i < friendly_cars; i++) {
        generate_car(cars[i], map, true, streets, max_speed);
        cars[i]->car_id = i;
    }
    for (int i = 0; i < enemy_cars; i++) {
        generate_car(cars[i + friendly_cars], map, false, streets, max_speed);
        cars[i + friendly_cars]->car_id = i + friendly_cars;
    }


}

