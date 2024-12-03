#pragma once
#include "cars.h"

//
//      CCC
//      CFC <-- car image
//      CCC
//

void car_collision(char** map, Car* org_car, Car* other_car) {
    render_car(map, org_car, REMOVE);
    render_car(map, other_car, REMOVE);
    reset_car(org_car, org_car->friendly,org_car->x,org_car->direction,org_car->street_number,org_car->stops);
    reset_car(other_car, other_car->friendly,other_car->x,other_car->direction,other_car->street_number,other_car->stops);
    //pozniej zrobie zeby sie rozlatywa³y na obstacles ktore
    //sie usuwaj¹ po jakimœ czasie
}

int return_car(int x, int y, Car** cars, int max_cars) {
    for (int i = 0; i < max_cars; i++) {
        if (!(cars[i]->y == -1)) {
            if (cars[i]->x == x || cars[i]->x == x-1 || cars[i]->x == x+1) {//if we found car on the street we're currently exploring
                if (cars[i]->y == y || cars[i]->y == y - 1 || cars[i]->y == y + 1) {
                    return i;
                }
            }
        }
    }
    return -1;
}


bool check_for_cars(char** map, Car** cars, int max_cars, int index) {
    int y2 = 0;
    int y = cars[index]->y;
    int street = cars[index]->x;
    if (cars[index]->direction==DOWN) {
        y += cars[index]->speed;
    }
    else {
        y -= cars[index]->speed;
    }
    for (int i = 0; i < max_cars; i++) {
        if (!(cars[i]->y == -1) && i != index && cars[i]->x == street) {//if initialized
            y2 = cars[i]->y;
            if (y == y2 || (y - 1) == y2 || (y + 1) == y2 || y2==(y+2) || y2==(y-2) || y2 == (y + 3) || y2 == (y - 3)) {
                car_collision(map, cars[index], cars[i]);
                return true;
            }
        }
    }
    return false;
}

void reset_car(Car* car, bool friendly,int x,int direction,int street_number,bool stops) {
    car->x = x;
    car->y = -1;
    car->symbol = ' ';
    car->friendly = friendly;
    car->street_number = street_number;
    car->speed = 0;
    car->direction=direction;
    car->stops = stops;
    if (street_number == -1) {//if not used
        car->respawn = -1;
    }

}




void render_car(char** map, Car* car, bool clear) {
    int x = (car->x) - 1;//minus one, since car drawing begins higher than it's
    int y = (car->y) - 1;//declared coords
    char symbol;
    if (clear) {
        symbol = ' ';
    }
    else {
        symbol = car->symbol;

    }
    for (int i = 0; i < CAR_SIZE; i++) {//x
        for (int j = 0; j < CAR_SIZE; j++) {//y
            if ((y+i) < MAP_HEIGHT && (y) > 0) {//precaution
                update_map(map, x + j, y + i, symbol);
            }

        }
    }
}

bool car_bounds(int x, int y) {
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
    if (car->x == -1) {//if car is not initialized (we keep cars on the same street)
        while (!empty) {
            street_number = rand() % STREETS;
            x_pos = streets[street_number];
            car->street_number = street_number;

            y_pos = rand() % 37;//hardcoded because it doesn't work with a variable name for some reason?

            if (car_bounds(x_pos, y_pos)) {
                if (map[y_pos - 1][x_pos] == ' ' && map[y_pos + 1][x_pos] == ' ' && map[y_pos][x_pos] == ' ') {//if there is no car already 
                    if (map[y_pos - 2][x_pos] == ' ' && map[y_pos + 2][x_pos] == ' ') {
                        empty = true;
                        // map[y_pos][x_pos] = 'O';
                    }

                }
            }

        }
        car->x = x_pos;
        car->y = y_pos;
        if ((car->street_number) % 2 == 0) {
            car->direction = DOWN;
        }
        else car->direction = UP;
    }
        
    
    else {
        
        if (car->direction == DOWN) {
            car->y = 3;//to "fit" the whole car on the beginning of the street
        }
        else {
            
            car->y = MAP_HEIGHT - 3;
        }
    }

    
}
void generate_car(Car* car, char** map, bool friendly, int streets[], int max_speed,bool stop) {
    srand(time(NULL));
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
    int respawn= (rand() % (max_speed - 1)) + 1;
    car->respawn = respawn;
    car->stops = stop;
    render_car(map, car, ADD);

}

void generate_all_cars(Car** cars, char** map, int streets[],LevelConfig config) {
    srand(time(NULL));
    int stops=0;
    bool stop = true;
    if (config.minimum_cars != 0) {
        int friendly_cars = (rand() % (config.max_friend - config.minimum_cars)) + config.minimum_cars; //generates random amount of
        //friendly cars between max and min amount declared
        int enemy_cars = (rand() % (config.max_enemy - config.minimum_cars)) + config.minimum_cars;
        if (config.max_friend > 0) {
            for (int i = 0; i < friendly_cars; i++) {
                if (stops >= config.max_stops) {
                    stop = false;
                }
                generate_car(cars[i], map, true, streets, config.max_speed, stop);
                //cars[i]->car_id = i;
                stops++;
            }
        }
        if (config.max_enemy > 0) {//purely for projects presentation purpouses
            for (int i = 0; i < enemy_cars; i++) {
                generate_car(cars[i + friendly_cars], map, false, streets, config.max_speed);
                //cars[i + friendly_cars]->car_id = i + friendly_cars;
            }
        }
    }
}

void render_all_cars(char** map, Car** cars,LevelConfig config) {
    int max_cars = config.max_enemy + config.max_friend;
    for (int i = 0; i < max_cars; i++) {
        if (cars[i]->x != -1) {//if car was generated
            render_car(map, cars[i], ADD);
        }
    }
}
