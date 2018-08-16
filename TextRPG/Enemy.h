//This is the Enemy class that stores info about the enemy

#ifndef ENEMY_H
#define ENEMY_H

#include <string>

using namespace std;

class Enemy
{
public:
	Enemy(string *n, int level, int attack, int defense, int speed, int health, int turn, int exp, int money);
	~Enemy();

	string const * enemyName;
	int const enemyLevel;
	int const enemyAttack;
	int const enemyDefense;
	int const enemySpeed;
	int const enemyHealth;
	int const enemyTurn;
	int const enemyEXP;
	int const enemyMoney;

private:

	
};

#endif