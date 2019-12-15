#pragma once

#include <iostream>
#include "Book.h"
#include "../Container/Date.h"
using namespace std;

class ItemDetail {
	private:
		int bookID;
		Book* book;
		bool status;
		Date dateBorrow, dateReturn;
	public:
		ItemDetail(Book* book, bool status, Date dateBorrow, Date dateReturn);
		ItemDetail(int bookID, bool status, Date dateBorrow, Date dateReturn);

		bool isReturned(){ return status; }

		friend ostream& operator << (ostream& out, const ItemDetail& item);
};

/*=============Definition of ItemDetail===========*/

ItemDetail::ItemDetail(Book* book, bool status, Date dateBorrow, Date dateReturn):
	book(book), status(status), dateBorrow(dateBorrow), dateReturn(dateReturn) 
{}

ItemDetail::ItemDetail(int bookID, bool status, Date dateBorrow, Date dateReturn):
	bookID(bookID), status(status), dateBorrow(dateBorrow), dateReturn(dateReturn)
{}

ostream& operator << (ostream& out, const ItemDetail& item){
	out << "Ten sach: " << item.book -> getName() << endl;
	out << "Ngay muon: " << item.dateBorrow << endl;
	return out;
}

