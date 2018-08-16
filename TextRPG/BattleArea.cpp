#include "BattleArea.h"
#include <iostream>

BattleArea::BattleArea(string* name, int aType, int a1, int a2, int a3, Enemy ** enemyList, int size)
	:Area(name,aType,a1,a2,a3), enemies(enemyList), listSize(size)
{

}

BattleArea::~BattleArea()
{
	delete enemies;
}

Enemy * BattleArea::getEnemy()
{
	return enemies[rand() % listSize];
}

