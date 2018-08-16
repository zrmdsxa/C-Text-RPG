//Shop Area
//only put in up to 9 items

#ifndef SHOPAREA_H
#define SHOPAREA_H

#include "Area.h"
#include "GenericItem.h"
#include "CombatItem.h"
#include <string>
using namespace std;

class ShopArea : public Area
{
public:
	ShopArea(string* name, int aType, int a1, int a2, int a3, GenericItem const ** itemList, int size);
	~ShopArea();

	virtual void DisplayItems(int playerClass) const;
	int getListSize();
	bool buyItem(int choice, int playerClass);
	GenericItem const * getItem(int choice) const;

private:

	GenericItem const ** items;
	int listSize = 0;
};

#endif