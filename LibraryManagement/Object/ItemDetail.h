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
		ItemDetail(int bookID);

		bool isReturned(){ return status; }
		void setBook(Book* book);
		Book* getBook();
		int getBookID();
		int getSlipID();
		
		void setStatus();
		void setDateReturn();

		friend ostream& operator << (ostream& out, const ItemDetail& item);
};

/*=============Definition of ItemDetail===========*/

ItemDetail::ItemDetail(Book* book, bool status, Date dateBorrow, Date dateReturn):
	book(book), status(status), dateBorrow(dateBorrow), dateReturn(dateReturn) 
{}

ItemDetail::ItemDetail(int slipID, int bookID, bool status, Date dateBorrow, Date dateReturn):
	slipID(slipID), bookID(bookID), status(status), dateBorrow(dateBorrow), dateReturn(dateReturn)
{}

ItemDetail::ItemDetail(int bookID): bookID(bookID)
{}

void ItemDetail::setBook(Book* book) { this->book = book; }
int ItemDetail::getBookID() { return bookID; }
int ItemDetail::getSlipID() { return slipID; }
Book* ItemDetail::getBook() { return book; }

void ItemDetail::setStatus() { this->status = 1; }

ostream& operator << (ostream& out, const ItemDetail& item){
	out << "Ten sach: " << item.book -> getName() << endl;
	out << "Ngay muon: " << item.dateBorrow << endl;
	return out;
}

