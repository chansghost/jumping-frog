#include "gameplayy.h"

void frog_on_car(char** map, Frog* frog, Car* car) {
    
	int x = car->x;
	int y = car->y;
	move_frog(map, frog, x, y);//reposition frog to the center of the car(aesthetic purposes)
	frog->car_index = car->car_id;

}

bool check_collision(char** map, Frog* frog, Car** cars, int max_cars,int x,int y) {
	/*int y = frog->y;
	int x = frog->x;*/
	int index;
	if ((map[y][x] != ' ') && (map[y][x] != '|')) {
        
        index = return_car(x, y, cars, max_cars);
        if (cars[index]->friendly) {
            
            frog_on_car(map, frog, cars[index]);

        }
        else {
            
            frog->dead = true;
        }
        
        return true;
	}
    
    return false;
}

void move_car(char** map, Car** cars, int index, int max_cars, Frog* frog) {
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
        else if (!check_collision(map, frog, cars, max_cars,x,y)) {//wrzucic do movecar
            
            move_frog(map, frog, x, y);
        }
        else move_frog(map, frog, x, y);
        
    }
    else {
        cputs("nie wolno!!!!!!!!");
    }
}