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
}Player;

void initialize_player(Player*player);

bool check_if_new(Player* player);

void new_player(Player* player);

void ranking(Player* player,double timer);

