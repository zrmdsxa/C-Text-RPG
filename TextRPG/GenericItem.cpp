#include "GenericItem.h"

#include <iostream>

GenericItem::GenericItem(const string* name, const string* type, int value, const string* desc)
	:itemName(name),itemType(type),itemValue(value),itemDescription(desc)
{

}

GenericItem::~GenericItem()
{
	if (itemName)
	{
		delete itemName;
	}
	
	if (itemDescription)
	{
		delete itemDescription;
	}
	

}

string const * GenericItem::getName() const
{
	return itemName;
}

string const * GenericItem::getItemType() const
{
	return itemType;
}

int GenericItem::getItemValue() const
{
	return itemValue;
}

void GenericItem::DisplayItemInfo() const
{
	cout << "Item:  " << *itemName << endl;
	cout << "Type:  " << *itemType << endl;
	cout << "Value: " << itemValue << endl;
	cout << "Description: " << *itemDescription << endl << endl;
}

