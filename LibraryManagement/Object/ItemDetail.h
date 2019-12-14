#pragma once

#include <iostream>
#include "Book.h"
using namespace std;

class Date
{
	private:
		int day, month, year;

	public:
		Date(int day = 0, int month = 0, int year = 0);
		friend ostream& operator<<(ostream& out, const Date& date);
};

class ItemDetail {
	private:
		Book* book;
		bool status;
		Date dateBorrow, dateReturn;
	public:
		ItemDetail(Book* book, bool status, Date dateBorrow, Date dateReturn);

		bool isReturned(){ return status; }

		friend ostream& operator << (ostream& out, const ItemDetail& item);
};

/*=============Definition of Date============*/
Date::Date(int day, int month, int year):
	day(day), month(month), year(year) 
{}

ostream& operator << (ostream& out, const Date& date){
	out << date.day << "/" << date.month << "/" << date.year;
	return out;
}

/*=============Definition of ItemDetail===========*/

ostream& operator << (ostream& out, const ItemDetail& item){
	out << "Ten sach: " << item.book -> getName() << endl;
	out << "Ngay muon: " << item.dateBorrow << endl;
	return out;
}

