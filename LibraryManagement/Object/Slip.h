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

    friend ostream &operator<<(ostream &out, const Slip &slip);
};

/*==================Definition of Slip=================*/

Slip::Slip(int slipID, int userID) :
	slipID(slipID), userID(userID)
{}

void Slip::addItem(ItemDetail item){ items.push_back(item); }
int Slip::getUserID() { return userID; }
int Slip::getNumberItems() { return (int) items.size(); }

ostream &operator<<(ostream &out, const Slip &slip)
{
    out << "slip ID: " << slip.slipID << "\n";
    out << "User ID: " << slip.userID << "\n";
	out << "List of book: " << '\n';
	for(int i = 0 ; i < slip.items.size() ; ++i){
		out << slip.items[i] << endl;
	}
	return out;
}
