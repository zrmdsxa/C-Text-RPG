//This is the Item class that stores info about the item

#ifndef GENERICITEM_H
#define GENERICITEM_H
#include <string>

using namespace std;

class GenericItem
{
public:
	GenericItem(const string* name,const string* type, int value,const string* desc);
	~GenericItem();
	void virtual DisplayItemInfo() const;

	string const * getName() const;
	string const * getItemType() const;
	int getItemValue() const;

protected:

	string const * itemName;	//item name

	/*
	item types
	0 - ???
	1 - melee weapon
	2 - ranged weapon
	3 - acefighter dual blade
	4 - acefighter dual gun
	5 - armor
	6 - accessory
	7 - item
	*/

	const string* itemType;			
	int itemValue = 0;
	const string* itemDescription;
		
};

#endif