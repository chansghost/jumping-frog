#include "player.h"

void initialize_player(Player* player) {
	player->points=0;
	player->won = false;
	player->level = 0;

}

bool check_if_new(Player* player) {
	printf("Czy chcesz wczytaæ star¹ rozgrywkê?\n");
	printf("T - tak\n");
	printf("N-nie\n");
	char c;
	c = getch();
	if (c == 't') {
		return true;
	}
	return false;

}

void new_player(Player* player) {
	int x = MAP_WIDTH / 2;
	int y = MAP_HEIGHT / 2;
	char c;
	char nowe;
	int i = 0;
	
	for (int i = 0; i < MAX_NAME; i++) {
		c = getch();  
		player->name[i] = c;
		putch(c);
		
		if (c=='\r') {
			player->name_length = i;
			return;
		}
		
	}
}

void ranking(Player*player,double timer) {
	int x = (MAP_WIDTH+MAP_WIDTH/4);
	int y = MAP_HEIGHT / 2;
	gotoxy(x, y);
	y++;
	cputs(" Ranking:\n");
	for (int i = 0; i < player->name_length; i++) {
		gotoxy(x+i, y);
		putch(player->name[i]);
	}
	y++;
	gotoxy(x, y);
	cputs("Points: ");
	x += 1;
	y++;
	gotoxy(x, y);
	printf("%d",player->points);
	x= (MAP_WIDTH + MAP_WIDTH / 4);
	y++;
	gotoxy(x, y);
	printf("%.1f", timer);

}