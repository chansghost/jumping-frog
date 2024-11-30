#include "obstacle.h"

void initialize_obstacle(Obstacle* obstacle) {
	obstacle->x = -1;
	obstacle->y = -1;
	obstacle->obstacle_id = -1;
	obstacle->symbol='O';
}

void generate_obstacles(Obstacle** obstacles, int sidewalks[], char** map, int max_obstacles) {
	int x_pos, y_pos;
	bool empty=false;
	srand(time(NULL));
	int sidewalk_no;
	for (int i = 0; i < max_obstacles; i++) {
		while (!empty) {
			sidewalk_no = rand() % SIDEWALKS;
			x_pos = sidewalks[sidewalk_no];
			y_pos = rand() % (MAP_HEIGHT-1)+1;
			if (map[y_pos][x_pos] == ' ') {
				empty = true;
			}
		}
		obstacles[i]->x = x_pos;
		obstacles[i]->y = y_pos;
		obstacles[i]->obstacle_id = i;
		update_map(map, x_pos, y_pos, obstacles[i]->symbol);
		empty = false;
	}
	
	
}