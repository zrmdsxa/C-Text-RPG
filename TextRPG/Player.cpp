#include "Player.h"

#include <iostream>

Player::Player() 
{
	playerName = new string;
	//playerClass = new string;
	weapon1 = NULL;
	weapon2 = NULL;
	armor = NULL;
	accessory = NULL;
}

Player::~Player() 
{
	delete playerName;
	//delete playerClass;
}

void Player::enterPlayerName() 
{
	cin >> *playerName;
}

string * Player::displayPlayerName() const
{
	return playerName;
}

void Player::changePlayerClass(int classChoice) {
	playerClass = classChoice;
}

int Player::getPlayerClass() const
{
	return playerClass;
}

int Player::getLevel()
{
	return level;
}

int Player::getExperience()
{
	return totalExp;
}

int Player::getExperienceReq()
{
	return expReq;
}

int Player::getAttack(int choice)
{
	int atk;
	if (choice == 1)
	{
		atk = attack + weapon1->attack;
	}
	else if (choice == 2)
	{
		atk = attack + weapon2->attack;
	}
	else
	{
		atk = -1;
	}

	return atk;
}

int Player::getDefense()
{
	return defense;
}

int Player::getSpeed()
{
	int spd = speed + weapon1->speed;
	if (playerClass == 2)
	{
		spd += weapon2->speed;
	}
	return spd;
}

int Player::getTurn(int choice)
{
	int turn;
	if (choice == 2)
	{
		turn = getWeapon2()->turn;
	}
	else {
		turn = getWeapon1()->turn;
	}
	return turn;
}

int Player::getHealth()
{
	return health+weapon1->health+armor->health;
}

int Player::getCurrency()
{
	return currency;
}

void Player::gainCurrency(int cur)
{
	if (cur > 0)
	{
		currency += cur;
	}
}

bool Player::useCurrency(int cur)
{
	bool success = false;
	if (cur > 0)
	{
		if (currency >= cur)
		{
			currency -= cur;
			success = true;
		}
	}
	
	return success;
}

void Player::gainExperience(int exp)
{
	if (exp > 0)
	{
		totalExp += exp;
	}

}

void Player::LevelUp(int lvl, int exp, int atk, int def, int spd, int hp)
{
	level = lvl;
	expReq = exp;
	attack = atk;
	defense = def;
	speed = spd;
	health = hp;

	cout << endl << "You leveled up!!!" << endl;
	cout << "Your new stats: " << endl << endl;
	cout << "Level: " << level << endl;
	cout << "Attack: " << attack << endl;
	cout << "Defense: " << defense << endl;
	cout << "Health: " << health << endl;
	cout << "Speed: " << speed << endl;

}

//Equip the Combat Item

int Player::equipCombatItem(CombatItem * ci)
{
	//make sure the CI exists
	if (ci == NULL)
	{
		cout << "Combat Item doesn't exist." << endl << endl;
		return 0;
	}

	/*
	combat item types
	0 - ? ? ?
	1 - melee weapon
	2 - ranged weapon
	3 - acefighter dual blade
	4 - acefighter dual gun
	5 - armor
	8 - accessory
	*/

	/*
	class
	0 - Melee
	1 - Ranged
	2 - ACE Fighter
	*/

	//Check what kind of item we're trying to equip
	switch (ci->combatType)
	{
		//equipping ??? item
	case 0:
		cout << "Combat Item type is ???" << endl << endl;
		return 0;

		//equipping melee weapon
	case 1:
		
		if (playerClass != 0)
		{
			cout << "This weapon can only be equiped by the Melee class." << endl << endl;
			return 0;
		}
		weapon1 = ci;
		break;
		//equipping ranged weapon
	case 2:
		if (playerClass != 1)
		{
			cout << "This weapon can only be equiped by the Ranged class." << endl << endl;
			return 0;
		}
		weapon1 = ci;
		break;
		//equipping dual blade
	case 3:
		if (playerClass != 2)
		{
			cout << "This weapon can only be equiped by the ACE Fighter class." << endl << endl;
			return 0;
		}
		weapon1 = ci;
		break;
		//equipping dual gun
	case 4:
		if (playerClass != 2)
		{
			cout << "This weapon can only be equiped by the ACE Fighter class." << endl << endl;
			return 0;
		}
		weapon2 = ci;
		break;
		//equipping armor
	case 5:
		armor = ci;
		break;
		//equipping accessory
	case 6:
		
		accessory = ci;
		break;
	default:
		cout << "Combat Item type doesn't exist." << endl << endl;
		return 0;
	}

	cout << endl << *ci->getName() << " equipped." << endl;
	return 1;
}

CombatItem * Player::getWeapon1()
{
	return weapon1;
}
CombatItem * Player::getWeapon2()
{
	return weapon2;
}

void Player::DisplayStats(string const * classes)
{
	cout << endl << "Name: " << *playerName << endl;
	cout << "Class: " << classes[playerClass] << endl;
	cout << "Level: " << level << endl;
	cout << "Attack: " << attack << endl;
	cout << "Defense: " << defense << endl;
	cout << "Health: " << health << endl;
	cout << "Speed: " << speed << endl;
	cout << "Total Exp: " << totalExp << endl;
	cout << "Exp to next level: " << expReq << endl;
	cout << "Money: " << currency << endl;
	cout << endl;
	cout << "Equipment:" << endl;
	cout << *weapon1->getName() << "(+" << weapon1->attack << " attack)" << endl;
	if (playerClass == 2)
	{
		cout << *weapon2->getName() << "(+" << weapon2->attack << " attack)" << endl;
	}

	cout << *armor->getName() << "(+" << armor->defense << " defense/+" << armor->health << " hp)" << endl;

	
}