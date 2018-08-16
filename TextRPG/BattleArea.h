//Battle Area

#ifndef BATTLEAREA_H
#define BATTLEAREA_H

#include "Area.h"
#include "Enemy.h"
#include <string>

using namespace std;

class BattleArea : public Area
{
public:
	BattleArea(string* name, int aType, int a1, int a2, int a3, Enemy ** enemyList, int size);
	Enemy * getEnemy();
	~BattleArea();
	//void virtual displayChoices();
	//bool virtual selectChoice();
	//Enemy getEnemy();

private:
	
	Enemy ** enemies;
	int listSize;
};
#endif