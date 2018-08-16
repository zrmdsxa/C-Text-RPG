#include "Area.h"
#include <iostream>

Area::Area(string* name, int aType, int a1, int a2, int a3)
	:areaName(name),areaType(aType),area1(a1),area2(a2),area3(a3)
{


}


Area::~Area()
{
	delete areaName;
}

string const * Area::DisplayAreaName()
{
	return areaName;
}

int Area::getAreaType()
{
	return areaType;
}
int Area::getArea1()
{
	return area1;
}
int Area::getArea2()
{
	return area2;
}
int Area::getArea3()
{
	return area3;
}

void Area::DisplayItems() const
{
}

void Area::showChoices(Area ** areaList)
{
	cout << endl << "++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "You are at " << *DisplayAreaName() << "." << endl;

	if (*DisplayAreaName() == "Building Entrance")
	{
		cout << endl << "Guard : \"It's dangerous outside. Only soldiers should go out there but I won't stop you." << endl;
	}

	if (*DisplayAreaName() == "Middle of Nowhere A1")
	{
		cout << endl << "You see a war happening in the distance. Projectiles are flying everywhere." << endl << "You should probably head back." << endl;
	}

	if (*DisplayAreaName() == "Elite Shop")
	{
		cout << endl << "Elite Shop Keeper: The best items for the best people." << endl;
	}


	/*
	1-battle
	2-shop
	3-
	4-
	5-
	6-area1
	7-area2
	8-area3
	9-display stats
	0-end game
	*/

	cout << endl;

	if (getAreaType() == 2)
	{
		cout << "1 - Battle" << endl;
	}

	if (getAreaType() == 1)
	{
		cout << "2 - Check the store (WIP)" << endl;
	}

	if (getArea1() != -1)
	{
		cout << "6 - Go to " << *areaList[getArea1()]->DisplayAreaName() << endl;
	}

	if (getArea2() != -1)
	{

		cout << "7 - Go to " << *areaList[getArea2()]->DisplayAreaName() << endl;
	}

	if (getArea3() != -1)
	{
		cout << "8 - Go to " << *areaList[getArea3()]->DisplayAreaName() << endl;
	}


	cout << "9 - Check Stats (WIP)" << endl;
	cout << "0 - End Game" << endl;
	cout << endl << "Pick a choice: ";
}
