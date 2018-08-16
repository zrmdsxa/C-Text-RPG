//This class holds information for a generic area
#include <string>

#ifndef AREA_H
#define AREA_H

using namespace std;

class Area
{
public:
	Area(string* name, int aType, int a1, int a2, int a3);
	~Area();

	string const * DisplayAreaName();
	int getAreaType();
	int getArea1();
	int getArea2();
	int getArea3();
	virtual void DisplayItems() const;
	void showChoices(Area ** areaList);

protected:
	string const * areaName;

	/*
	0 - unknown area
	1 - shop area
	2 - battle area
	*/

	int areaType;
	int area1;
	int area2;
	int area3;

};

#endif