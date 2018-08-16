//This is the player class that stores info about the player

#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "CombatItem.h"

using namespace std;

class Player
{
public:
	Player();
	~Player();

	void enterPlayerName();				//enter player name
	string * displayPlayerName() const;	//display player name
	void changePlayerClass(int classChoice);			//change player's class
	int getPlayerClass() const;			//display player class

	int getLevel();
	int getExperience();
	int getExperienceReq();
	int getAttack(int choice);
	int getDefense();
	int getSpeed();
	int getTurn(int choice);
	int getHealth();
	int getCurrency();
	

	void gainExperience(int exp);
	void LevelUp(int lvl, int exp, int atk, int def, int spd, int hp);

	void gainCurrency(int cur);
	bool useCurrency(int cur);

	int equipCombatItem(CombatItem * ci);
	CombatItem * getWeapon1();
	CombatItem * getWeapon2();


	void DisplayStats(string const * classes);

private:
	string *playerName;	//player's name
	int playerClass; //player's class

	CombatItem * weapon1;
	CombatItem * weapon2; //Dual Gun
	CombatItem * armor;
	CombatItem * accessory;
	
	//items[][][][][]][][][][][][][][]

	//stats
	int level;
	int expReq;
	int attack;
	int defense;
	int speed;
	int health;
	int currency = 0;
	int totalExp = 0;

};

#endif