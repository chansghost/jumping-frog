#include "player.h"

void initialize_player(Player* player) {
	player->points=0;
	player->won = false;
	player->level = 0;
	player->log = false;

}



void new_player(Player* player) {
	int x = MAP_WIDTH / 2;
	int y = MAP_HEIGHT / 2;
	char c;
	char nowe;
	int i = 0;
	cputs("Please enter your name: ");
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
	int x = (MAP_WIDTH + MAP_WIDTH / 4);
	int y = (MAP_HEIGHT / 2);
	
	gotoxy(x, y);
	y++;
	
	gotoxy(x, y);
	//Name: ???
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
void add_log(char text[],Player*player) {
	char clear[] = "                            ";
	if (player->log) {
		cputs(clear);
	}
	int x = (MAP_WIDTH + MAP_WIDTH / 4);
	int y = (MAP_HEIGHT / 2)+10;//10 because i just simply thought so,it looks nice there
	gotoxy(x, y);
	cputs(text);
	player->log = true;
}

int winning_logs(Player* player) {
	clrscr();
	cputs("You won\n");
	if (player->level < 3) {
		char c;
		while (true) {
			cputs("Do you wish to go to the next level?\n");
			cputs("Y-yes\n");
			cputs("N-no\n");
			c = getch(); 

			switch (c) {
			case 'y':
				return true;
			case 'n':
				return false;
			default:
				printf("\nInvalid input. Please enter 'Y' or 'N'.\n");
				break;
			}
		}
	
	}
	else {
		cputs("You finished the highest level of the game. Congratulations!\n");
		return -1;
	}
}
