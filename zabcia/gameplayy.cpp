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
            if (!check_for_frog(cars[index], frog)) {
                return false;
            }
            frog->dead = true;
            return true;
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
bool check_jump_on_car(char** map, Frog* frog, Car** cars, int max_cars, int x, int y) {
    if ((map[y][x] == FRIENDLY) || (map[y][x] ==ENEMY)) {
        frog->dead = true;
        return true;
    }
    return false;
}

bool look_for_frog(Car* car,char**map) {
    //vacinity is 2 fields all around
    //check if frog is not already on this car index
    int vacinity = CAR_SIZE*2 + 1;
    int y = (car->y)-3;
    int x = (car->x)-3;
    for (int i = 0; i < vacinity; i++) {//x
        for (int j = 0; j < vacinity; j++) {//y
            if ((y + i) < MAP_HEIGHT && (y-3) > 0) {//precaution
                if (map[y + i][x + j] == '@') {
                    return true;
                }
            }
        }
    }
    return false;
}

void respawn_car(char** map, Car* car, int streets[], int max_speed) {
    int newy;
    if (car->respawn == 0) {
        if (car->direction == DOWN) {
            newy = 3;
        }
        else newy = MAP_HEIGHT - 3;
        //cars always spawn on either y=3 or y=MAP_HEIGHT - 3 to fit
        if (map[newy][car->x] == ' ')//if no car spawned
        {
            generate_car(car, map, car->friendly, streets, max_speed, car->stops);

        }
        else {
            car->respawn = 1;
        }
    }
    else car->respawn--;
}


void move_car(char** map, Car** cars, int index, int max_cars, Frog* frog, int streets[], int max_speed) {
    bool spawned_on_street = false;//to avoid "flashing cars" while spawning,
    //a boolean to check if during this round a car already spawned on the same street
    int newy;
    if (!(check_for_cars(map, cars, max_cars, index))) {
        Car* car = cars[index];
        if (!(car->y == -1)) {//if car is initialized on the map
            if (frog->car_index == index || !car->stops || !look_for_frog(car, map)) {
                render_car(map, car, REMOVE);
                newy = car->y;

                if (car->direction == DOWN) {
                    newy += car->speed;
                    car->y = newy;
                }
                else {
                    newy -= car->speed;
                    car->y = newy;
                }
                if (car_bounds(car->x, car->y)) {
                    render_car(map, car, ADD);
                    
                    //if(check_collision(map,frog,cars) && frog->dead)
                    if (car->car_id == frog->car_index) {
                        move_frog(map, frog, car->x, car->y);
                    }
                    else {
                        check_collision(map, frog, cars, max_cars, car->x, car->y, car->car_id);
                    }
                }
                else {
                    int x = car->x;
                    if (car->car_id == frog->car_index) {
                        frog->dead = true;
                    }
                    reset_car(car, car->friendly, x, car->direction, car->street_number, car->stops);
                }
            }
        }
        else respawn_car(map, car, streets, max_speed);
    }
    else if(cars[index]->car_id == frog->car_index) {
        frog->dead = true;
    }
}

bool bonus_collected(char** map, Bonus** bonuses,Frog* frog,int direction,int max_bonus) {
    int x = frog->x;
    int y = frog->y;
    int index;
    bool found = false;

    for (int i = 0; i < (frog->jump_distance)+1; i++) {
        if (direction == RIGHT) {
            if (map[y][x+i] == BONUS) {
                x = x + i;
                found = true;
            }
        }
        else if (direction == LEFT) {
            if (map[y][x - i] == BONUS) {
                x = x - i;
                found = true;
            }
        }
        else if (direction == UP) {
            if (map[y-i][x] == BONUS) {
                y = y - i;
                found = true;
            }
        }
        else if (direction == DOWN) {
            if (map[y + i][x] == BONUS) {
                y = y + i;
                found = true;
            }
        }
        if (found) {
            collect_bonus(bonuses, x, y, max_bonus, map);
            return true;
        }
    }
    return false;
}


void try_on_car(char** map, Frog* frog,Car** cars, int max_cars) {
    int x = frog->x - 2;//checking all over car
    int y = (frog->y) - 2;
    int index;
    for (int i = 0; i < CAR_SIZE*2; i++) {//x
        for (int j = 0; j < CAR_SIZE*2; j++) {//y
            if ((y + i) < MAP_HEIGHT && (y - 1) > 0) {
                if (map[y + i][x + j] == 'F') {
                    check_collision(map, frog, cars, max_cars, x + j, y + i);
                }
            }
        }
    }
}


void jump(char** map, Frog* frog, int direction, Car** cars, int max_cars,int max_bonuses,Bonus**bonuses, Player* player)
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
            frog->map_piece = 'F';
            move_frog(map, frog, x, y);
            
            
            
            if (frog->jump_distance == 1) {//frog wants to get off the car, 
                //so if it jumps only over 1 field, we add a "boost"
                //for it to get off
                jump(map, frog, direction, cars, max_cars, max_bonuses,bonuses,player);
            }
        }
        else if (!obstacle_check(map, x, y)) {
            if (bonus_collected(map, bonuses, frog, direction, max_bonuses)) {
                player->points += 1;
                move_frog(map, frog, x, y);
            }
            else if (!check_jump_on_car(map, frog, cars, max_cars, x, y))
            {
                move_frog(map, frog, x, y);
            }
        }
        else cputs("nie wolno!!!!!!!!");
        frog->jumping = false;
        
    }
    else if(x>=MAP_WIDTH){
        player->won = true;
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



void fly_stork(Stork* stork, Frog* frog, char** map) {
    if (stork->exists) {
        if (stork->speed >= 1 || stork->gained_speed >= 1) {
            int x, y;
            int directionUPDOWN = 0, directionLEFTRIGHT = 0;//might not need to move vertically, hence 0 (in defines,
            //directions range from 1-4)
            x = frog->x;
            y = frog->y;
            if (x > stork->x) {
                directionLEFTRIGHT = RIGHT;
            }
            else if (x < stork->x) {
                directionLEFTRIGHT = LEFT;
            }
            if (y > stork->y) {
                directionUPDOWN = DOWN;
            }
            else if (y < stork->y) {
                directionUPDOWN = UP;
            }
            render_stork(map, stork, REMOVE);
            move_stork(stork, directionUPDOWN, directionLEFTRIGHT);
            if (frog_caught(stork, map)) frog->dead = true;
            update_map_piece(stork, map);
            render_stork(map, stork, ADD);
            stork->gained_speed = stork->speed;
        }
        else {
            stork->gained_speed+=stork->speed;
        }
    }
}

void gameplay(char** map, char** pastmap, int max_cars,Car** cars, Frog* frog, int streets[], LevelConfig config, Bonus** bonuses, Player* player, Stork* stork,Obstacle**obstacles){
    int key;
    bool quit = false;
    time_t start = time(NULL);
    time_t timer = time(NULL);
    time_t newtime = time(NULL);
    double passed;
    while (!quit) {//koniec lvl pozniej tu trzeba wsadzic
        if (kbhit()) {
            key = getch();
            start = time(NULL);
            switch (key) {
            case 'w':
                jump(map, frog, UP, cars, max_cars,config.bonuses,bonuses,player);
                //print_map(map, pastmap, basemap);
                break;
            case 's':
                jump(map, frog, DOWN, cars, max_cars, config.bonuses, bonuses, player);
                break;
            case 'a':
                jump(map, frog, LEFT, cars, max_cars, config.bonuses, bonuses, player);
                break;
            case 'd':
                jump(map, frog, RIGHT, cars, max_cars, config.bonuses, bonuses, player);
                break;
            case 'c':
                try_on_car(map, frog, cars, max_cars);
                break;
            case 'p':
                save_game_state(cars, obstacles, bonuses, frog, stork, player, config);
                quit = true;
                break;
            case 'q':
                quit = true;
                break;
            }
        }
        for (int i = 0; i < max_cars; i++) {
            if (frog->dead) break;
            move_car(map, cars, i, max_cars, frog, streets, config.max_speed);
            render_stork(map, stork, ADD);//so that the cars don't cover up the stork
        }
        newtime = time(NULL);
        passed = difftime(newtime, timer);

        if (config.stork && !(stork->exists)) {
            spawn_stork(stork, passed, map);
        }
        ranking(player, passed);
        
        fly_stork(stork, frog, map);
        if (time(NULL) - start > config.frog_time) {
            frog->dead = true;
        }
        if (frog->dead) {
            quit = true;
        }
        if (player->won) {
            quit = true;
        }
        print_map(map, pastmap);
    }
}

void game(char** map,char**basemap, char** pastmap, Car** cars, LevelConfig config, Frog* frog,Obstacle**obstacles,Bonus**bonuses,Player*player, Stork* stork) {
    int max_cars = config.max_enemy + config.max_friend;
    int sidewalks[SIDEWALKS];
    int street_numbers[STREETS];
    base_map(map, street_numbers, basemap, sidewalks);
    print_map(map, pastmap);
    generate_all_cars(cars, map,street_numbers,config);
    generate_obstacles(obstacles, sidewalks, map, config.max_obstacles);
    generate_bonuses(bonuses, map, config.bonuses);
    update_map(map, frog->x, frog->y, frog->symbol);
    print_map(map, pastmap);
    frog->jump_distance = config.frog_jump;
    stork->time_spawn = config.stork_spawn;
    stork->speed = config.stork_speed;
    stork->gained_speed = config.stork_speed;
    gameplay(map, pastmap,max_cars, cars, frog, street_numbers,config,bonuses,player,stork,obstacles);

}

bool check_if_new() {
    printf("Do you want to load a saved game?\n");
    printf("Y-yes\n");
    printf("N-no\n");
    char c;
    c = getch();
    if (c == 'y') {
        return true;
    }
    return false;

}



void start() {
    int sidewalks[SIDEWALKS];
    int street_numbers[STREETS];
    int level;
    Player* player = (Player*)malloc(sizeof(Player));
    initialize_player(player);
    char** basemap;
    char** map;
    char** pastmap;
    initialize_map(&basemap, &map, &pastmap);
   
    Car** cars;
    Obstacle** obstacles;
    Bonus** bonuses;
    Stork* stork;
    Frog* frog;
    LevelConfig config;
    if (!check_if_new()) {
        level = chooseLevel();
        player->level = level;
        manage_config(&config, level);
        initialize_memory(&cars, &obstacles, &bonuses, &frog,&stork, config);
        game(map, basemap, pastmap, cars, config, frog, obstacles, bonuses, player, stork);
    }
    else {
        load_game_state(&cars, &obstacles, &bonuses, &frog, &stork, player, &config);
        int max_cars = config.max_enemy + config.max_friend;
        base_map(map, street_numbers, basemap, sidewalks);
        render_all_cars(map, cars, config);
        render_stork(map, stork, ADD);
        render_obstacles(obstacles, map, config.max_obstacles);
        render_bonuses(bonuses, map, config.bonuses);
        update_map(map, frog->x, frog->y, FROG);
        print_map(map, pastmap);
        gameplay(map, pastmap, max_cars, cars, frog, street_numbers, config, bonuses, player, stork, obstacles);
    }
}