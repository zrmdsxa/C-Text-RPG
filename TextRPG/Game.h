//This is the game class that stores everything in the game

#ifndef GAME_H
#define GAME_H

#include <string>
#include "Player.h"
#include "PlayerLevel.h"
#include "CombatItem.h"
#include "Enemy.h"
#include "ShopArea.h"
#include "BattleArea.h"

using namespace std;


class Game
{
public:

	Game();
	~Game();
	void SetUpStart();		//Set up the start of the game
	void LevelTable();		//Set up level table
	void SetUpWeapons();			//Set up weapons
	void SetUpEnemies();			//Set up enemies
	void SetUpAreas();			//Set up areas



	void MainGame();		//Main game loop

	void Battle(Enemy *e);	//Battle
	int PlayerAttack(int * playerHP, int * enemyHP, int * playerTurn, Enemy * e);
	void EnemyAttack(int * playerHP, int * enemyHP, int * enemyTurn, Enemy * e);

	void VisitShop(ShopArea* shop);

private:

	Player *player;
	static int const NUM_CLASSES = 3;			//number of classes
	static string const CLASSES[NUM_CLASSES];	//classes

	//Level Table
	static int const NUM_LEVELS = 100;
	PlayerLevel * MELEELEVELS[NUM_LEVELS];
	PlayerLevel * RANGEDLEVELS[NUM_LEVELS];
	PlayerLevel * ACEFIGHTERLEVELS[NUM_LEVELS];

	PlayerLevel ** LEVELS[3] = { MELEELEVELS,RANGEDLEVELS,ACEFIGHTERLEVELS };


	static int const NUM_ITEMTYPES = 5;
	static string const ITEMTYPES[NUM_ITEMTYPES];

	//weapons
	static int const NUM_MELEEWEAPONS = 5;
	static int const NUM_RANGEDWEAPONS = 5;
	static int const NUM_ACEFIGHTERWEAPONS = 6;

	CombatItem * MELEEWEAPONS[NUM_MELEEWEAPONS];
	CombatItem * RANGEDWEAPONS[NUM_RANGEDWEAPONS];
	CombatItem * ACEFIGHTERWEAPONS[NUM_ACEFIGHTERWEAPONS];

	//armor

	static int const NUM_ARMOR = 3;
	CombatItem * ARMOR[NUM_ARMOR];

	//Enemy

	int NUM_ENEMIES = 0;
	Enemy ** ENEMIES;

	//Areas
	int currentArea = 0;
	//static int const NUM_AREAS = 4;
	Area ** AREAS;
	int NUM_AREAS = 0;

};

#endif