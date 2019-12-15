#pragma once

#include "Book.h"
#include "ItemDetail.h"
//#include "../Container/Vector.h"
#include <vector>
using namespace std;

class Slip
{
	private:
		int slipID;
		vector<ItemDetail> items;
		int userID;

	public:
		Slip(){}
		Slip(int slipID, int userID);

		void addItem(ItemDetail item);
		int getUserID();
		int getNumberItems();
};

/*==================Definition of Slip=================*/

Slip::Slip(int slipID, int userID) :
	slipID(slipID), userID(userID)
{}

void Slip::addItem(ItemDetail item){ items.push_back(item); }
int Slip::getUserID() { return this -> userID; }
int Slip::getNumberItems() { return (int) items.size(); }
