#pragma once

#include <iostream>
#include <string>
using namespace std;

class Date
{
private:
	int day, month, year;

public:
	Date(int day = 0, int month = 0, int year = 0);
	Date(const Date& date);
	Date(char date[]);

	friend ostream& operator<<(ostream& out, const Date& date);
};

/*=============Definition of Date============*/
Date::Date(int day, int month, int year) :
	day(day), month(month), year(year)
{}

Date::Date(const Date& date) :
	day(date.day), month(date.month), year(date.year)
{}

Date::Date(char date[]) {
	this->day = 0; this->month = 0; this->year = 0;
	for (int i = 0; i < 4; ++i)
		this->year = this->year * 10 + (date[i] - '0');

	for(int i = 5; i < 7 ; ++i)
		this->month = this->month * 10 + (date[i] - '0');

	for (int i = 8; i < 10; ++i)
		this->day = this->day * 10 + (date[i] - '0');
}

ostream& operator << (ostream& out, const Date& date) {
	out << date.day << "/" << date.month << "/" << date.year;
	return out;
}