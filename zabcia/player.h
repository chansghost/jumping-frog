#pragma once
#include "defines.h"
#include "includes.h"
#include <iostream>

typedef struct {
	char name[MAX_NAME];
	int points;
	bool won;
	int level;
	int name_length;
	bool log;
}Player;

void initialize_player(Player*player);

void add_log(char text[], Player* player);

int winning_logs(Player* player);

void new_player(Player* player);

void ranking(Player* player,double timer);

