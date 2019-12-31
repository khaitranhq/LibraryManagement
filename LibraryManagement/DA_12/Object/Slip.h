#pragma once

#include "ItemDetail.h"
#include "Book.h"
#include "../Container/Vector.h"
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

		vector<ItemDetail* > getItems();
		vector<int> getBooksID();
		vector<Book*> getBookNotReturned();

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

vector<ItemDetail*> Slip::getItems() {
	return this->items;
}

vector<int> Slip::getBooksID() {
	vector<int> ans;
	for (int i = 0; i < items.size(); ++i)
		ans.push_back(items[i]->getBookID());
	return ans;
}

vector<Book*> Slip::getBookNotReturned() {
	vector<Book*> ans;
	for (int i = 0; i < items.size(); ++i)
		if (items[i]->isReturned())
			ans.push_back(items[i]->getBook());
	return ans;
}

ostream& operator << (ostream& out, const Slip& slip) {
	out << "ID: " << slip.slipID << "\n";
	out << "User ID: " << slip.userID << "\n";
	return out;
}