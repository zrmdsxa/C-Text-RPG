#include "CombatItem.h"

#include <iostream>

CombatItem::CombatItem(const string* name, const string* type, int value, const string* desc, int ctype, int atk, int def, int hp, int rng, int spd, int trn)
	:GenericItem(name, type, value, desc),combatType(ctype), attack(atk), defense(def), health(hp), range(rng), speed(spd), turn(trn)
{

}
/*
CombatItem::~CombatItem()
{

}
*/


void CombatItem::DisplayItemInfo()
{
	GenericItem::DisplayItemInfo();
	cout << "Attack: " << attack << endl;
	cout << "Defense: " << defense << endl;
	cout << "Health: " << health << endl;
	cout << "Range: " << range << endl;
	cout << "Speed: " << speed << endl;
	cout << "Turns: " << turn << endl << endl;
}