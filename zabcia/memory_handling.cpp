#include "memory_handling.h"
#include "cars.h"


void allocate(char*** map, char*** pastmap, int max_cars) {

    *map = (char**)malloc(MAP_HEIGHT * sizeof(char*));
    for (int i = 0; i < MAP_HEIGHT; i++) {
        *map[i] = (char*)malloc((MAP_WIDTH * sizeof(char)));

    }
    *pastmap = (char**)malloc(MAP_HEIGHT * sizeof(char*));
    for (int i = 0; i < MAP_HEIGHT; i++) {
        *pastmap[i] = (char*)malloc((MAP_WIDTH * sizeof(char)));

    }
}

void free_memory(char** map, char** pastmap, int max_cars) {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        free(map[i]);
    }
    free(map);
    for (int i = 0; i < MAP_HEIGHT; i++) {
        free(pastmap[i]);
    }
    free(pastmap);
    

}