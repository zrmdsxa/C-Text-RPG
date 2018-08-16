#include "Enemy.h"

Enemy::Enemy(string *n, int level, int attack, int defense, int speed, int health, int turn, int exp, int money)
	:enemyName(n), enemyLevel(level), enemyAttack(attack), enemyDefense(defense), enemySpeed(speed), enemyHealth(health), enemyTurn(turn), enemyEXP(exp), enemyMoney(money)
{
	
}

Enemy::~Enemy()
{
	if (enemyName)
	{
		delete enemyName;
	}
	
}