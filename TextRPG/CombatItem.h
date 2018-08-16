//Like GenericItem but with stats

#ifndef COMBATITEM_H
#define COMBATITEM_H

#include "GenericItem.h"

class CombatItem : public GenericItem
{
public:
	CombatItem(const string* name, const string* type, int value, const string* desc, int ctype, int atk, int def, int hp, int rng, int spd, int trn);
	//~CombatItem();
	void virtual DisplayItemInfo();

	/*
	combat item types
	0 - ???
	1 - melee weapon
	2 - ranged weapon
	3 - acefighter dual blade
	4 - acefighter dual gun
	5 - armor
	6 - accessory
	7 - item
	*/

	int const combatType;
	int const attack;
	int const defense;
	int const health;
	int const range;
	int const speed;
	int const turn;
};
#endif