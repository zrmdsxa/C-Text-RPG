#include "Game.h"

#include <iostream>
#include <ctime>

using namespace std;

/*
class
0 - Melee
1 - Ranged
2 - ACE Fighter
*/

const string Game::CLASSES[NUM_CLASSES] = { "Melee","Ranged","ACE Fighter" };
const string Game::ITEMTYPES[NUM_ITEMTYPES] = { "???", "Weapon", "Armor", "Accessory", "Item" };

//constructor
Game::Game()
{
	
	srand(time(NULL));

	
	player = new Player();
	
	LevelTable();
	SetUpWeapons();
	SetUpEnemies();
	SetUpAreas();
	SetUpStart();

	MainGame();
}

Game::~Game()
{
	delete player;
	for (int i = 0; i < NUM_LEVELS; i++) 
	{
		delete MELEELEVELS[i];
		delete RANGEDLEVELS[i];
		delete ACEFIGHTERLEVELS[i];
		
	}

	for (int i = 0; i < NUM_MELEEWEAPONS; i++)
	{
		delete MELEEWEAPONS[i];
	}

	for (int i = 0; i < NUM_RANGEDWEAPONS; i++)
	{
		delete RANGEDWEAPONS[i];
	}

	for (int i = 0; i < NUM_ACEFIGHTERWEAPONS; i++)
	{
		delete ACEFIGHTERWEAPONS[i];
	}
	
	for (int i = 0; i < NUM_ENEMIES; i++)
	{
		delete ENEMIES[i];
	}
	
	for (int i = 0; i < NUM_AREAS; i++)
	{
		delete AREAS[i];
	}
}


void Game::MainGame()
{
	int area = 0;
	int choice;
	do
	{
		//at area
		
		AREAS[currentArea]->showChoices(AREAS);

		cin >> choice;
		cout << endl;

		cout << endl << "**************************************************" << endl;
		switch (choice)
		{
		case 1:
			if (AREAS[currentArea]->getAreaType() == 2) {
				Enemy *e;
				e = ((BattleArea*)AREAS[currentArea])->getEnemy();

				Battle(e);
				//delete e;
			}

			else
			{
				cout << "Sorry, " << choice << " isn't a valid choice." << endl;
			}
			break;
		case 2:
			
			if (AREAS[currentArea]->getAreaType() == 1)
			{
				cout << "You check the store!!! (WIP)" << endl;
				VisitShop(dynamic_cast < ShopArea* >(AREAS[currentArea]));

			}
			else
			{
				cout << "Sorry, " << choice << " isn't a valid choice." << endl;
			}
			break;
		case 6:
			
			if (AREAS[currentArea]->getArea1() == -1)
			{
				cout << "Sorry, " << choice << " isn't a valid choice." << endl;
			}
			cout << "You go to " << *AREAS[AREAS[currentArea]->getArea1()]->DisplayAreaName() << "." << endl;
			currentArea = AREAS[currentArea]->getArea1();
			break;
		case 7:
			
			if (AREAS[currentArea]->getArea2() == -1)
			{
				cout << "Sorry, " << choice << " isn't a valid choice." << endl;
			}
			else
			{
				cout << "You go to " << *AREAS[AREAS[currentArea]->getArea2()]->DisplayAreaName() << "." << endl;
				currentArea = AREAS[currentArea]->getArea2();
			}
			
			break;
		case 8:
			
			if (AREAS[currentArea]->getArea3() == -1)
			{
				cout << "Sorry, " << choice << " isn't a valid choice." << endl;
			}
			else {
				cout << "You go to " << *AREAS[AREAS[currentArea]->getArea3()]->DisplayAreaName() << "." << endl;
				currentArea = AREAS[currentArea]->getArea3();
			}
				
			break;
		case 9:
			
			player->DisplayStats(CLASSES);
			break;
		case 0:			
			break;
		default:
			
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Sorry, " << choice << " isn't a valid choice." << endl;
		}
		cin.clear();
		cin.ignore(1000, '\n');

	} while (choice != 0);

	cout << endl << "The game has ended" << endl;
	string end;
	cin >> end;
}

void Game::Battle(Enemy *e)
{
	int playerHP = player->getHealth();
	int enemyHP = e->enemyHealth;
	
	int enemyAttack = 0;
	int playerTurn = 0;
	int enemyTurn = 0;
	int battleStart = 1;

	cout << endl << "You are fighting \"" << *e->enemyName << "\"" << endl;

	int choice = 0;

	do
	{

		if (playerTurn == 0 && enemyTurn == 0)
		{
			if (player->getSpeed() >= e->enemySpeed)
			{
				choice = PlayerAttack(&playerHP,&enemyHP,&playerTurn, e);
				
				if (enemyHP > 0)
				{
					EnemyAttack(&playerHP, &enemyHP, &enemyTurn, e);
				}
			}
			else
			{
				EnemyAttack(&playerHP, &enemyHP, &enemyTurn, e);
				if (playerHP > 0)
				{
					choice = PlayerAttack(&playerHP, &enemyHP, &playerTurn, e);
				}
			}
		}
		else if (playerTurn == 0)
		{
			choice = PlayerAttack(&playerHP, &enemyHP, &playerTurn, e);
		}
		else if (enemyTurn == 0)
		{
			EnemyAttack(&playerHP, &enemyHP, &enemyTurn, e);
		}
		else
		{
			playerTurn--;
			enemyTurn--;
		}

		//cout << "PlayerTurn: " << playerTurn << endl;
		//cout << "EnemyTurn: " << enemyTurn << endl;

		
		if (enemyHP <= 0) {
			cout << endl << "You defeated \"" << *e->enemyName << "\"!" << endl;
			cout << endl << "You gained " << e->enemyEXP << " exp and " << e->enemyMoney << " money!" << endl;

			player->gainExperience(e->enemyEXP);
			player->gainCurrency(e->enemyMoney);

			while (player->getExperience() >= player->getExperienceReq() && player->getLevel() < NUM_LEVELS)
			{
				player->LevelUp(
					LEVELS[player->getPlayerClass()][player->getLevel()]->level,
					LEVELS[player->getPlayerClass()][player->getLevel()]->expReq,
					LEVELS[player->getPlayerClass()][player->getLevel()]->attack,
					LEVELS[player->getPlayerClass()][player->getLevel()]->defense,
					LEVELS[player->getPlayerClass()][player->getLevel()]->speed,
					LEVELS[player->getPlayerClass()][player->getLevel()]->health);
			}
		}

		if (playerHP <= 0) {
			cout << endl << "You lost the battle." << endl;
			currentArea = 0;

			cout << endl << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
			cout << "You were brought back to the starting area." << endl;
			cout << endl << "Nurse: \"Are you okay? Be careful out there!" << endl;
		}

	} while (playerHP > 0 && enemyHP > 0);
}
//Players turn to attack
int Game::PlayerAttack(int * playerHP,int * enemyHP, int * playerTurn, Enemy * e)
{
	float playerAttack = 0;

	cout << endl << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "Your HP: " << *playerHP << " ----- Enemy HP: " << *enemyHP << endl;
	cout << endl << "1 - Attack with " << *player->getWeapon1()->getName() << endl;
	if (player->getPlayerClass() == 2)
	{
		cout << "2 - Attack with " << *player->getWeapon2()->getName() << endl;
	}
	cout << endl;
	cout << endl << "Pick a choice: ";

	int choice;
	cin >> choice;
	cout << endl;
	cout << endl << "**************************************************" << endl;
	switch (choice)
	{
	case 1:
	case 2:

		if (choice == 2 && player->getPlayerClass() != 2)
		{
			cout << "Sorry, " << choice << " isn't a valid choice." << endl;
			break;
		}


		//debug if
		
		
		if (choice == 1)
		{
			//cout << "Player Base Attack: " << player->getAttack(choice) - player->getWeapon1()->attack << endl;
			//cout << "Player Weapon Attack: " << player->getWeapon1()->attack << endl;
		}
		else if (choice == 2)
		{
			//cout << "Player Base Attack: " << player->getAttack(choice) - player->getWeapon2()->attack << endl;
			//cout << "Player Weapon Attack: " << player->getWeapon2()->attack << endl;
		}
		
		
		*playerTurn += player->getTurn(choice);
		playerAttack = player->getAttack(choice);
		

		//cout << "Player Total Attack: " << playerAttack << endl;
		//cout << endl << "Enemy Def: " << e->enemyDefense << endl;

		playerAttack = playerAttack * (playerAttack/e->enemyDefense) * ((rand() / (float)RAND_MAX * 0.2) + 0.9);
		if (playerAttack <= 0)
		{
			playerAttack = 1;
		}


		if (playerAttack > player->getAttack(choice) * 1.5)
		{
			playerAttack = player->getAttack(choice) * 1.5;
		}
		playerAttack = truncf(playerAttack);

		//cout << "Player Attack * 1.5: " << player->getAttack(choice) * 1.5 << endl;
		//cout << "Player Total Attack: " << playerAttack << endl;

		cout << endl << "You attack the enemy and do " << playerAttack << " damage." << endl;

		*enemyHP -= playerAttack;

		break;
	case 0:
		
		break;
	default:
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Sorry, " << choice << " isn't a valid choice." << endl;
	}

	return choice;
}
//Enemy's turn to attack
void Game::EnemyAttack(int * playerHP, int * enemyHP, int * enemyTurn, Enemy * e)
{

	float enemyAttack = 0;


	//cout << "Enemy Attack: " << e->enemyAttack << endl;
	//cout << endl << "Player Def: " << player->getDefense() << endl;

	*enemyTurn += e->enemyTurn;

	enemyAttack = e->enemyAttack;
	//enemyAttack = enemyAttack * (enemyAttack/player->getDefense()) * ((rand() / (float)RAND_MAX * 0.2) + 0.9);
	float defM = player->getDefense() / enemyAttack;
	if (defM >= 1.0)
	{
		enemyAttack = enemyAttack / defM * ((rand() / (float)RAND_MAX * 0.2) + 0.9);
	}
	else 
	{
		enemyAttack = enemyAttack - 0.5*(enemyAttack-(player->getDefense()*defM))  * ((rand() / (float)RAND_MAX * 0.2) + 0.9);
	}
	
	if (enemyAttack <= 0)
	{
		enemyAttack = 1;
	}

	if (enemyAttack > e->enemyAttack * 1.5)
	{
		enemyAttack = e->enemyAttack * 1.5;
	}
	enemyAttack = truncf(enemyAttack);

	//cout << "Enemy Total Attack: " << enemyAttack << endl;

	cout << "\"" << *e->enemyName << "\" attacks you for " << enemyAttack << " damage." << endl;

	*playerHP -= enemyAttack;
	
}
/*	Set up the game
	Get player name and the their class
	Give them items
*/
void Game::SetUpStart() 
{
	cout << "\tWelcome to TextRPG" << endl;
	cout << endl;
	cout << "Before we begin, please pick a name (no spaces): ";
	player->enterPlayerName();
	cin.clear();
	cin.ignore(1000, '\n');
	cout << "Your name is " << *player->displayPlayerName() << endl;
	

	int choice;
	do
	{
		cout << endl;
		cout << "The following class are available:" << endl;
		cout << "0 - Melee - Melee class that uses close ranged weapons" << endl;
		cout << "1 - Ranged - Ranged class that uses ranged weapons" << endl;
		cout << "2 - ACE Fighter - A class that uses dual blades and dual guns" << endl;
		cout << endl;
		cout << "Please pick a class to play as: ";

		cin >> choice;
		cout << endl;
		cout << endl << "**************************************************" << endl;
		switch (choice)
		{
		case 0:
		case 1:
		case 2:
			break;
		default:
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Sorry, " << choice << " isn't a valid choice." << endl;
		}
		
	} while (choice < 0 || choice > 2);

	cin.clear();
	cin.ignore(1000, '\n');
	player->changePlayerClass(choice);
	cout << "You chose the " << CLASSES[player->getPlayerClass()] << " class." << endl;
	cout << endl;
	cout << "\\(^o^)/ Your adventure begins, " << *player->displayPlayerName() << "! \\(^o^)/" << endl;

	currentArea = 0;

	switch (choice)
	{
	case 0:
		player->equipCombatItem(MELEEWEAPONS[0]);

		break;
	case 1:
		player->equipCombatItem(RANGEDWEAPONS[0]);

		break;
	case 2:
		player->equipCombatItem(ACEFIGHTERWEAPONS[0]);
		player->equipCombatItem(ACEFIGHTERWEAPONS[1]);

		break;
	}
	//set up player
	player->equipCombatItem(ARMOR[0]);

	player->gainCurrency(70);
	
	player->LevelUp(
		LEVELS[player->getPlayerClass()][0]->level,
		LEVELS[player->getPlayerClass()][0]->expReq,
		LEVELS[player->getPlayerClass()][0]->attack,
		LEVELS[player->getPlayerClass()][0]->defense,
		LEVELS[player->getPlayerClass()][0]->speed,
		LEVELS[player->getPlayerClass()][0]->health);

}

void Game::VisitShop(ShopArea* shop)
{
	int choice;
	do
	{
		cout << endl << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
		cout << "You are at the shop." << endl;
		/*
		1-
		0-leave shop
		*/

		cout << endl;


		cout << "1 - Buy an item" << endl;
		//cout << "2 - " << endl;

		cout << "9 - Check Stats (WIP)" << endl;
		cout << "0 - Leave Shop" << endl;
		cout << endl << "Pick a choice: ";

		cin >> choice;
		cout << endl;
		cout << endl << "**************************************************" << endl;
		switch (choice)
		{
		case 1:
			int choice2;
			do
			{
				cout << endl << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
				cout << "You currently have: " << player->getCurrency() << endl;
				cout << "You can buy the following items:" << endl;
				cout << endl;
				shop->DisplayItems(player->getPlayerClass());
				cout << "0 - Cancel" << endl;
				cout << endl << "Pick a choice: ";

				cin >> choice2;
				cout << endl;

				switch (choice2)
				{
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
				case 9:
					if (choice2 > shop->getListSize())
					{
						cout << "Sorry, " << choice2 << " isn't a valid choice." << endl;
						break;
					}
					if (shop->buyItem(choice2, player->getPlayerClass()))
					{
						//cout << "You can buy this item" << endl;
						if (player->useCurrency(shop->getItem(choice2)->getItemValue()))
						{
							cout << "You bought the " << *shop->getItem(choice2)->getName() << endl;
							player->equipCombatItem((CombatItem*)shop->getItem(choice2));
						}
						else
						{
							cout << "You don't have enough money" << endl;
						}
					}
					else
					{
						cout << "Sorry, " << choice2 << " isn't a valid choice." << endl;
					}

					break;
				case 0:
					break;
				default:
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Sorry, " << choice2 << " isn't a valid choice." << endl;
				}
				cin.clear();
				cin.ignore(1000, '\n');


			} while (choice2 != 0);
			break;
		case 9:
			player->DisplayStats(CLASSES);
			break;
		case 0:
			break;
		default:
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Sorry, " << choice << " isn't a valid choice." << endl;
		}
		cin.clear();
		cin.ignore(1000, '\n');

	} while (choice != 0);

	cout << endl << "You leave the shop." << endl;
}

//set up levels

void Game::LevelTable() 
{
	int exp = 100;

	int atk1 = 55;
	int def1 = 55;
	int spd1 = 3;
	int hp1 = 115;

	int atk2 = 40;
	int def2 = 45;
	int spd2 = 2;
	int hp2 = 90;

	int atk3 = 65;
	int def3 = 35;
	int spd3 = 4;
	int hp3 = 100;

	for (int i = 0;i < NUM_LEVELS;i++) {

		
		MELEELEVELS[i] = new PlayerLevel(i + 1,		 exp + (i * i * 100),		 atk1 + (i * 10),	def1 + (i * 9.5),	spd1 + (i * 0.1),	 hp1 + (i * 9.1));
		RANGEDLEVELS[i] = new PlayerLevel(i + 1,	 exp + (i * i * 100),		 atk2 + (i * 9.5),	def2 + (i * 9),		spd2 + (i * 0.08),	 hp2 + (i * 8.5));
		ACEFIGHTERLEVELS[i] = new PlayerLevel(i + 1, exp + (i * i * 100) ,		 atk3 + (i * 10.5),	def3 + (i * 8),		spd3 + (i * 0.11),	 hp3 + (i * 8.55));

		/*
		cout << "Level: " << MELEELEVELS[i]->level << endl;
		cout << "EXP:   " << MELEELEVELS[i]->expReq << endl;
		cout << "ATK:   " << MELEELEVELS[i]->attack << endl;
		cout << "DEF:   " << MELEELEVELS[i]->defense << endl;
		cout << "SPD:   " << MELEELEVELS[i]->speed << endl;
		cout << "HP:    " << MELEELEVELS[i]->health << endl << endl;

		
		cout << "Level: " << RANGEDLEVELS[i]->level << endl;
		cout << "EXP:   " << RANGEDLEVELS[i]->expReq << endl;
		cout << "ATK:   " << RANGEDLEVELS[i]->attack << endl;
		cout << "DEF:   " << RANGEDLEVELS[i]->defense << endl;
		cout << "SPD:   " << RANGEDLEVELS[i]->speed << endl;
		cout << "HP:    " << RANGEDLEVELS[i]->health << endl << endl;

		cout << "Level: " << ACEFIGHTERLEVELS[i]->level << endl;
		cout << "EXP:   " << ACEFIGHTERLEVELS[i]->expReq << endl;
		cout << "ATK:   " << ACEFIGHTERLEVELS[i]->attack << endl;
		cout << "DEF:   " << ACEFIGHTERLEVELS[i]->defense << endl;
		cout << "SPD:   " << ACEFIGHTERLEVELS[i]->speed << endl;
		cout << "HP:    " << ACEFIGHTERLEVELS[i]->health << endl << endl;
		*/
		
	}

}

//set up weapons

void Game::SetUpWeapons()
{
	//												NAME				 &ITEMTYPES[1]	VALUE	 DESCRIPTION							CTYPE	ATK	DEF	HP RANGE SPEED TURN

	int a = 0;
	MELEEWEAPONS[a++] = new CombatItem(new string("Training Sword"),	&ITEMTYPES[1], 10,		 new string("Starter Training Sword"),		1,	 5, 0, 0, 3, 0, 10);
	MELEEWEAPONS[a++] = new CombatItem(new string("Short Sword"),		&ITEMTYPES[1], 100,	 new string("Short Sword"),					1,	 15, 0, 0, 3, 0, 10);
	MELEEWEAPONS[a++] = new CombatItem(new string("2H Sword"),			&ITEMTYPES[1], 100,	 new string("2H Sword"),					1,	 25, 0, 0, 5, 0, 12);
	MELEEWEAPONS[a++] = new CombatItem(new string("Katana"),			&ITEMTYPES[1], 100,	 new string("Katana"),						1,	 10, 0, 0, 4, 0, 9);
	MELEEWEAPONS[a++] = new CombatItem(new string("Z Sword"),			&ITEMTYPES[1], 1000000, new string("Z Sword"),					1, 3000, 300, 100, 5, 3, 8);

	int b = 0;
	RANGEDWEAPONS[b++] = new CombatItem(new string("Training Pistol"),	 &ITEMTYPES[1], 10,	 new string("Starter Training Pistol"),			2,	 1, 0, 0, 25, 0, 3);
	RANGEDWEAPONS[b++] = new CombatItem(new string("Pistol1"),			 &ITEMTYPES[1], 100,	 new string("Pistol"),							2,	 10, 0, 0, 25, 0, 3);
	RANGEDWEAPONS[b++] = new CombatItem(new string("Pistol2"),			 &ITEMTYPES[1], 200,	 new string("Pistol2"),						2,	 20, 0, 0, 25, 0, 3);
	RANGEDWEAPONS[b++] = new CombatItem(new string("Pistol3"),			 &ITEMTYPES[1], 500,	 new string("Pistol3"),						2,	 30, 0, 0, 25, 0, 3);
	RANGEDWEAPONS[b++] = new CombatItem(new string("Z Gun"),			 &ITEMTYPES[1], 1000000, new string("Z Gun"),					2, 2500, 0, 100, 100, 3, 3);


	int c = 0;
	ACEFIGHTERWEAPONS[c++] = new CombatItem(new string("Training Dual Blade"),	 &ITEMTYPES[1],	 10, new string("Starter Training Dual Blade"),	3, 0, 0, 0, 3, 0, 7);
	ACEFIGHTERWEAPONS[c++] = new CombatItem(new string("Training Dual Gun"),	 &ITEMTYPES[1],	 10, new string("Starter Training Dual Gun"),	4, -25, 0, 0, 25, 0, 3);
	ACEFIGHTERWEAPONS[c++] = new CombatItem(new string("Dual Blade"),			 &ITEMTYPES[1], 100, new string("Dual Blade"),					3, 10, 0, 0, 3, 0, 7);
	ACEFIGHTERWEAPONS[c++] = new CombatItem(new string("Dual Gun"),				 &ITEMTYPES[1], 100, new string("Dual Gun"),						4, -20, 0, 0, 25, 0, 3);
	ACEFIGHTERWEAPONS[c++] = new CombatItem(new string("Z Dual Blade"),			&ITEMTYPES[1], 1000000, new string("Z Dual Blade"), 3, 3000, 300, 100, 5, 3, 6);
	ACEFIGHTERWEAPONS[c++] = new CombatItem(new string("Z Dual Gun"),			&ITEMTYPES[1], 1000000, new string("Z Dual Gun"), 4, 2500, 0, 100, 100, 3, 3);

	int z = 0;
	ARMOR[z++] = new CombatItem(new string("Training Armor"), &ITEMTYPES[2], 10, new string("Starter Training Armor"), 5, 0, 5, 5, 0, 0, 0);
	ARMOR[z++] = new CombatItem(new string("Standard Armor"), &ITEMTYPES[2], 100, new string("Standard Armor"), 5, 0, 20, 20, 0, 0, 0);
	ARMOR[z++] = new CombatItem(new string("Z Armor"), &ITEMTYPES[2], 1000000, new string("Z Armor"), 5, 0, 3000, 300, 0, 3, 0);

}

void Game::SetUpEnemies()
{
	int a = 0;
	NUM_ENEMIES = 11;
	ENEMIES = new Enemy*[NUM_ENEMIES];
	
	//									NAME				LEVEL	ATK DEF SPD HP TURN EXP MONEY

	//Training Area 1
	ENEMIES[a++] = new Enemy(new string("Training Melee Enemy (Sword)"), 1, 55, 55, 1, 150,	11, 10, 15);
	ENEMIES[a++] = new Enemy(new string("Training Ranged Enemy (Pistol)"), 1, 35, 50, 1, 90, 3, 10, 15);
	ENEMIES[a++] = new Enemy(new string("Training ACE Fighter Enemy (Dual Blade)"), 1, 60, 35, 2, 100, 7, 10, 15);
	ENEMIES[a++] = new Enemy(new string("Training ACE Fighter Enemy (Dual Gun)"), 1, 40, 35, 2, 100, 3, 10, 15);

	/*
	cout << "Name: " << *ENEMIES[a - 1]->enemyName << endl;
	cout << "Level: " << ENEMIES[a - 1]->enemyLevel << endl;
	cout << "Attack: " << ENEMIES[a - 1]->enemyAttack << endl;
	cout << "Defense: " << ENEMIES[a - 1]->enemyDefense << endl;
	cout << "Speed: " << ENEMIES[a - 1]->enemySpeed << endl;
	cout << "Health: " << ENEMIES[a - 1]->enemyHealth << endl;
	cout << "Turn: " << ENEMIES[a - 1]->enemyTurn << endl;
	cout << "EXP: " << ENEMIES[a - 1]->enemyEXP << endl;
	*/

	//Middle of Nowhere A1
	ENEMIES[a++] = new Enemy(new string("Sniper"),					100, 1000,	4000, 10, 4000, 5, 1000, 1000);
	ENEMIES[a++] = new Enemy(new string("Rocket Truck"),			100, 400,	4500, 15, 5000, 1, 1200, 1500);
	ENEMIES[a++] = new Enemy(new string("Light Armored Vehicle"),	110, 600,	5000, 20, 6000, 3, 2000, 5000);

	//Training Area 2
	ENEMIES[a++] = new Enemy(new string("Samurai"), 5, 90, 75, 5, 300, 10, 45, 30);
	ENEMIES[a++] = new Enemy(new string("Archer"), 5, 75, 60, 3, 250, 5, 40, 25);
	ENEMIES[a++] = new Enemy(new string("Knight"), 5, 60, 200, 2, 400, 15, 50, 50);
	ENEMIES[a++] = new Enemy(new string("Sentry Gun"), 5, 40, 10, 0, 200, 1, 30, 20);

}

void Game::SetUpAreas()
{
	int a = 0;
	NUM_AREAS = 6;
	AREAS = new Area* [NUM_AREAS];

	GenericItem const ** shopArea1 = new const GenericItem* [7];
	
	shopArea1[0] = MELEEWEAPONS[1];
	shopArea1[1] = MELEEWEAPONS[2];
	shopArea1[2] = MELEEWEAPONS[3];
	shopArea1[3] = RANGEDWEAPONS[1];
	shopArea1[4] = ACEFIGHTERWEAPONS[2];
	shopArea1[5] = ACEFIGHTERWEAPONS[3];
	shopArea1[6] = ARMOR[1];

	//shopArea1[0]->DisplayItemInfo();
	
	//Starting Area
	//0
	//a1 - 2 - Training Area - Super easy
	//a2 - 1 - Entrance
	//a3
	AREAS[a++] = new ShopArea(new string("Starting Area"), 1, 2, 1, -1, shopArea1, 7);

	//Entrance
	//1
	//a1 - 0 - Starting Area
	//a2 - 2 - Training Area - Super easy
	//a3 - 3 - Outside
	AREAS[a++] = new Area(new string("Building Entrance"), 0, 0, 2, 3);

	//AREAS[a - 1]->displayChoices();

	Enemy ** battleArea1 = new Enemy* [4];

	battleArea1[0] = ENEMIES[0];
	battleArea1[1] = ENEMIES[1];
	battleArea1[2] = ENEMIES[2];
	battleArea1[3] = ENEMIES[3];

	//Training Area - Super easy
	//2
	//a1 - 0 - Starting Area
	//a2 - 1 - Entrance
	//a3 - 4 - Training Area - easy
	AREAS[a++] = new BattleArea(new string("Training Area"), 2, 0, 1, 4,battleArea1, 4);
	
	Enemy ** battleArea2 = new Enemy*[3];

	battleArea2[0] = ENEMIES[4];
	battleArea2[1] = ENEMIES[5];
	battleArea2[2] = ENEMIES[6];

	//Outside
	//3
	//a1 - 1 - Entrance
	//a2 - 
	//a3 - 
	AREAS[a++] = new BattleArea(new string("Middle of Nowhere A1"), 2, 1, -1, -1, battleArea2, 3);

	Enemy ** battleArea3 = new Enemy*[4];

	battleArea3[0] = ENEMIES[7];
	battleArea3[1] = ENEMIES[8];
	battleArea3[2] = ENEMIES[9];
	battleArea3[3] = ENEMIES[10];
	
	//Training Area 2
	//4
	//a1 - 0 - Training Area
	//a2 - 5 - Elite Shop

	AREAS[a++] = new BattleArea(new string("Training Area 2"), 2, 2, 5, -1, battleArea3, 4);

	//Elite Shop
	//5
	//a1 - 4 - Training Area 2

	GenericItem const ** shopArea2 = new const GenericItem*[5];

	shopArea2[0] = MELEEWEAPONS[4];
	shopArea2[1] = RANGEDWEAPONS[4];
	shopArea2[2] = ACEFIGHTERWEAPONS[4];
	shopArea2[3] = ACEFIGHTERWEAPONS[5];
	shopArea2[4] = ARMOR[2];

	AREAS[a++] = new ShopArea(new string("Elite Shop"), 1, 4, -1, -1, shopArea2, 5);
}
