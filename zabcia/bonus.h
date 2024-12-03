#pragma once
#include "map.h"
#include "includes.h"
#include "defines.h"

typedef struct {
	int x, y;
	bool collected;
	bool disappeared;
	char symbol;
	int bonus_id;
}Bonus;

void initialize_bonus(Bonus* bonus);

void generate_bonuses(Bonus** bonuses, char** map,int max_bonuses);

void collect_bonus(Bonus** bonuses, int x, int y,int max_bonus,char**map);

void render_bonuses(Bonus** bonuses, char** map, int max_bonuses);