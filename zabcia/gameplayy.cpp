#include "gameplayy.h"

void frog_on_car(char** map, Frog* frog, Car* car) {
    
	int x = car->x;
	int y = car->y;
	move_frog(map, frog, x, y);//reposition frog to the center of the car(aesthetic purposes)
	frog->car_index = car->car_id;

}
bool check_for_frog(Car* car,Frog*frog) {
    int x = (car->x)-1;//checking all over car
    int y = (car->y)-1;
    for (int i = 0; i < CAR_SIZE; i++) {//x
        for (int j = 0; j < CAR_SIZE; j++) {//y
            if (frog->x==x+j && frog->y==y+i) {
                return true;
            }
        }
    }
    return false;
}
bool obstacle_check(char** map, int x, int y) {
    if (map[y][x] == 'O') {
        return true;
    }
    return false;
}

bool check_collision(char** map, Frog* frog, Car** cars, int max_cars,int x,int y,int index) {
    
	if ((map[y][x] != ' ') && (map[y][x] != '|')) { //if we are trying to check collision on jumping frog
        
        if (index != -1) {//checking if we are checking for collision from car's perspective
            if(!check_for_frog(cars[index],frog)) {
                return false;
            }
        }
        else index = return_car(x, y, cars, max_cars);

        if (cars[index]->friendly) {
            frog_on_car(map, frog, cars[index]);
        }
        else frog->dead = true;

        return true;
        
	}
    
    return false;
}

void move_car(char** map, Car** cars, int index, int max_cars, Frog* frog, int streets[], int max_speed) {
    if (!(check_for_cars(map, cars, max_cars, index))) {
        Car* car = cars[index];
        if (!(car->y == -1)) {//if car is initialized on the map
            render_car(map, car, REMOVE);
            int newy = car->y;

            if (car->direction==DOWN) {
                newy += car->speed;
                car->y = newy;
            }
            else {
                newy -= car->speed;
                car->y = newy;
            }
            if (car_bounds(map, car->x, car->y)) {
                render_car(map, car, ADD);
                check_collision(map, frog, cars,max_cars,car->x,car->y,car->car_id);
                //if(check_collision(map,frog,cars) && frog->dead)
                if (car->car_id == frog->car_index) {
                    move_frog(map, frog, car->x, car->y);
                }
            }
            else {
                int x = car->x;
                if (car->car_id == frog->car_index) {
                    frog->dead = true;
                }
                reset_car(car, car->friendly,x,car->direction);
            }
        }
        else if (car->respawn == 0) {
            generate_car(car, map, car->friendly, streets, max_speed);
        }
        else car->respawn--;
    }
    else if(cars[index]->car_id == frog->car_index) {
        frog->dead = true;
    }
}

void jump(char** map, Frog* frog, int direction, Car** cars, int max_cars)
{
    int y = frog->y;
    int x = frog->x;
    if (direction == RIGHT) {
        //++y
        x += frog->jump_distance;
    }
    else if (direction == LEFT) {
        x -= frog->jump_distance;
    }
    else if (direction == UP) {
        y -= frog->jump_distance;
    }
    else if (direction == DOWN) {
        y += frog->jump_distance;
    }
    if (frog_within_bounds(x, y)) {//dodac wygrywajace
        frog->jumping = true;
        if (frog->car_index != -1) {
            //frog is on car
            frog->car_index = -1;
            move_frog(map, frog, x, y);
            
            
            
            if (frog->jump_distance == 1) {//frog wants to get off the car, 
                //so if it jumps only over 1 field, we add a "boost"
                //for it to get off
                jump(map, frog, direction, cars, max_cars);
            }
        }
        else if (!obstacle_check(map, x, y)) {
            if (!check_collision(map, frog, cars, max_cars, x, y)) {//if we are don't jump on any car 
                move_frog(map, frog, x, y);
            }
        }
        else cputs("nie wolno!!!!!!!!");
        frog->jumping = false;
        
    }
    else {
        cputs("nie wolno!!!!!!!!");
    }
}
int chooseLevel() {
    clrscr();
    cputs("Choose game level:\n");
    textbackground(RED);
    putch('0');
    cputs("\n");
    putch('1');
    cputs("\n");
    putch('2');
    cputs("\n");
    putch('3');
    textbackground(BLACK);
    int key;
    key = getch();

    switch (key)
    {
    case '0':
        clrscr();
        return 0;
    case '1':
        clrscr();
        return 1;
    case '2':
        clrscr();
        return 2;
    case '3':
        clrscr();
        return 3;
    }
}
void gameplay(char** map, char** basemap, char** pastmap, Car** cars, int max_cars, Frog* frog, int streets[], int max_speed, int time) {
    int key;
    bool quit = false;
    time_t start = time(NULL);
    while (!quit) {//koniec lvl pozniej tu trzeba wsadzic
        if (kbhit()) {
            key = getch();
            start = time(NULL);
            switch (key) {
            case 'w':
                jump(map, frog, UP, cars, max_cars);
                //print_map(map, pastmap, basemap);
                break;
            case 's':
                jump(map, frog, DOWN, cars, max_cars);
                break;
            case 'a':
                jump(map, frog, LEFT, cars, max_cars);
                break;
            case 'd':
                jump(map, frog, RIGHT, cars, max_cars);
                break;
            case 'q':
                quit = true;
                break;
            }
        }
        for (int i = 0; i < max_cars; i++) {
            if (frog->dead) break;
            move_car(map, cars, i, max_cars, frog, streets, max_speed);
        }
        if (time(NULL) - start > time) {
            frog->dead = true;
        }
        if (frog->dead) {
            quit = true;
            cputs("GAME OVERRRRRRRRR");
        }
        print_map(map, pastmap, basemap);
    }
}

void game(char** map, char** basemap, char** pastmap,int max_cars, Car** cars, LevelConfig* config, Frog* frog,Obstacle**obstacles) {
    int sidewalks[SIDEWALKS];
    int street_numbers[STREETS];
    base_map(map, street_numbers, basemap,sidewalks);
    print_map(map, pastmap, basemap);
    generate_all_cars(cars, map, config->max_friend, config->max_enemy, config->minimum_cars, street_numbers, config->max_speed);
    generate_obstacles(obstacles, sidewalks, map, config->max_obstacles);
    print_map(map, pastmap, basemap);
    frog->jump_distance = config->frog_jump;
    gameplay(map, basemap, pastmap, cars, max_cars, frog, street_numbers, config->max_speed,config->frog_time);

}