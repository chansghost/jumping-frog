#pragma once
#include "map.h"


void print_stats(int level, int points) {

    cputs("GAME STATS");
    cputs("\n");
    printf("%d", level);
    cputs("        ");
    putch(points);
    cputs("\n");

}

void print_map(char** map) {
    gotoxy(1, 1);
    clrscr();
    print_stats(1, 2);
    for (int i = 0; i < MAP_HEIGHT; i++) { //y
        for (int j = 0; j < MAP_WIDTH; j++) {//x
            if (map[i][j] == 'F') {
                textcolor(LIGHTBLUE);
                textbackground(LIGHTBLUE);
            }
            else if (map[i][j] == 'E') {
                textcolor(RED);
                textbackground(RED);
            }
            putch(map[i][j]);
            textcolor(WHITE);
            textbackground(BLACK);

        }
        cputs("\n"); //new line
    }

}

void map_tests(char** map) {
    for (int i = 0; i < MAP_HEIGHT; i++) { //y
        for (int j = 0; j < MAP_WIDTH; j++) {//x
            map[i][j] = 'l';
        }
    }
}
// .0100'0'00101000001
void base_map(char** map, int street_numbers[]) {
    int street_counter = 0;
    int counter = -1;//auxiliary variable
    bool placed_sidewalk = true;
    for (int i = 0; i < MAP_HEIGHT; i++) { //y
        for (int j = 0; j < MAP_WIDTH; j++) {//x
            if (placed_sidewalk && counter == 0) {//beginning of the street
                placed_sidewalk = false;
                map[i][j] = '|';
            }
            else if (counter > STREET_WIDTH) {//end of street
                map[i][j] = '|';
                counter = -2; //resetting the counter, it will have the beginning value
                //of -1 at the end of incrementation
                placed_sidewalk = true;
            }
            else {
                map[i][j] = ' ';
                if (i == 0 && counter == 3) {//3=middle of the street, i==0 because we need this statement to
                    //run only in the first row
                    street_numbers[street_counter] = j;//saving the x value for the given street no.
                    street_counter++;
                }

            }
            counter++;

        }
    }
    //map[2][3] = 'O';

}
void update_map(char** map, int x, int y, char symbol) {
    map[y][x] = symbol;

}

