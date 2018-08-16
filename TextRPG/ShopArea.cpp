#include "ShopArea.h"

#include <iostream>

//only put in up to 9 items

ShopArea::ShopArea(string* name, int aType, int a1, int a2, int a3, GenericItem const ** itemList,int size)
	:Area(name, aType, a1, a2, a3),items(itemList),listSize(size)
{
	//cout << *name << " shop list size = " << listSize << endl;
}

ShopArea::~ShopArea()
{
	delete items;
}

void ShopArea::DisplayItems(int playerClass) const
{
	//cout << "SIZE OF " << sizeof(*items) << endl;
	for (int i = 0; i < listSize; i++)
	{
		if (*items[i]->getItemType() == "Weapon")
		{


			//cout << "this is a weapon" << endl;
			//cout << "player class: " << playerClass;
			//cout << "combat item type: " << ((CombatItem*)items[i])->getCombatType() << endl;
			if (playerClass == 0 && ((CombatItem*)items[i])->combatType == 1) {
				//cout << "this is melee class and melee weapon" << endl;
				cout << i + 1 << " - (" << items[i]->getItemValue() << ") " << *items[i]->getName() << " (+" << ((CombatItem*)items[i])->attack << " attack)" << endl;
			}
			else if (playerClass == 1&& ((CombatItem*)items[i])->combatType == 2) {
				//cout << "this is ranged class and ranged weapon" << endl;
				cout << i + 1 << " - (" << items[i]->getItemValue() << ") " << *items[i]->getName() << " (+" << ((CombatItem*)items[i])->attack << " attack)" << endl;
			}
			else if (playerClass == 2 && (((CombatItem*)items[i])->combatType == 3 || ((CombatItem*)items[i])->combatType == 4)) {
				//cout << "this is ace fighter class and db or dg weapon" << endl;
				cout << i + 1 << " - (" << items[i]->getItemValue() << ") " << *items[i]->getName() << " (+" << ((CombatItem*)items[i])->attack << " attack)" << endl;
			}
			
		}
		
		else if (*items[i]->getItemType() == "Armor")
		{
			cout << i + 1 << " - (" << items[i]->getItemValue() << ") " << *items[i]->getName() << " (+" << ((CombatItem*)items[i])->defense << " defense/+" << ((CombatItem*)items[i])->health << " hp)" << endl;
		}
		else {
			cout << i + 1 << " - (" << items[i]->getItemValue() << ") " << *items[i]->getName() << endl;
		}
	}
}

int ShopArea::getListSize()
{
	return listSize;
}


bool ShopArea::buyItem(int choice, int playerClass)
{
	choice -= 1;
	bool success = false;
	if (*items[choice]->getItemType() == "Weapon")
	{
		if (playerClass == 0 && ((CombatItem*)items[choice])->combatType == 1) {
			success = true;
		}
		else if (playerClass == 1 && ((CombatItem*)items[choice])->combatType == 2) {
			success = true;
		}
		else if (playerClass == 2 && (((CombatItem*)items[choice])->combatType == 3 || ((CombatItem*)items[choice])->combatType == 4)) {
			success = true;
		}
	}
	else
	{
		success = true;
	}
	return success;
}

GenericItem const * ShopArea::getItem(int choice) const
{
	choice -= 1;
	return items[choice];
}