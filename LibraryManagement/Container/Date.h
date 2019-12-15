#pragma once

#include <iostream>
using namespace std;

class Date
{
private:
	int day, month, year;

public:
	Date(int day = 0, int month = 0, int year = 0);
	Date(const Date& date);
	friend ostream& operator<<(ostream& out, const Date& date);
};

/*=============Definition of Date============*/
Date::Date(int day, int month, int year) :
	day(day), month(month), year(year)
{}

Date::Date(const Date& date) :
	day(date.day), month(date.month), year(date.year)
{}

ostream& operator << (ostream& out, const Date& date) {
	out << date.day << "/" << date.month << "/" << date.year;
	return out;
}