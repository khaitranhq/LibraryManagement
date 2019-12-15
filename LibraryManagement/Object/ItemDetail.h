#pragma once

#include <iostream>
#include "Book.h"
#include "../Container/Date.h"
using namespace std;

class ItemDetail {
	private:
		int bookID, slipID;
		Book* book;
		bool status;
		Date dateBorrow, dateReturn;
	public:
		ItemDetail(Book* book, bool status, Date dateBorrow, Date dateReturn);
		ItemDetail(int slipID, int bookID, bool status, Date dateBorrow, Date dateReturn);

		bool isReturned(){ return status; }
		void setBook(Book* book);
		int getBookID();
		int getSlipID();

		friend ostream& operator << (ostream& out, const ItemDetail& item);
};

/*=============Definition of ItemDetail===========*/

ItemDetail::ItemDetail(Book* book, bool status, Date dateBorrow, Date dateReturn):
	book(book), status(status), dateBorrow(dateBorrow), dateReturn(dateReturn) 
{}

ItemDetail::ItemDetail(int slipID, int bookID, bool status, Date dateBorrow, Date dateReturn):
	slipID(slipID), bookID(bookID), status(status), dateBorrow(dateBorrow), dateReturn(dateReturn)
{}

void ItemDetail::setBook(Book* book) { this->book = book; }
int ItemDetail::getBookID() { return bookID; }
int ItemDetail::getSlipID() { return slipID; }

ostream& operator << (ostream& out, const ItemDetail& item){
	out << "Ten sach: " << item.book -> getName() << endl;
	out << "Ngay muon: " << item.dateBorrow << endl;
	return out;
}

