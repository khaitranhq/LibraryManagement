#pragma once

#include "ItemDetail.h"
//#include "../Container/Vector.h"
#include <vector>
using namespace std;

class Slip
{
	private:
		int slipID;
		vector<ItemDetail* > items;
		int userID;
		int numberBorrow;
	public:
		Slip(){}
		Slip(int slipID, int userID, int numberBorrow);

		void addItem(ItemDetail* item);
		int getSlipID();
		int getUserID();
		int getNumberItems();

		friend istream& operator >> (istream& in, Slip& slip);
		friend ostream& operator << (ostream& out, const Slip& slip);
};

/*==================Definition of Slip=================*/

Slip::Slip(int slipID, int userID, int numberBorrow) :
	slipID(slipID), userID(userID), numberBorrow(numberBorrow)
{}

void Slip::addItem(ItemDetail* item){ items.push_back(item); }
int Slip::getSlipID() { return this->slipID; }
int Slip::getUserID() { return this -> userID; }
int Slip::getNumberItems() { return (int) items.size(); }

istream& operator >> (istream& in, Slip& slip) {
	return in;
}

ostream& operator << (ostream& out, const Slip& slip) {
	out << "ID: " << slip.slipID << "\n";
	out << "User ID: " << slip.userID << "\n";
	return out;
}