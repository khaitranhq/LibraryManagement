#pragma once

#include "Book.h"
#include "../Container/Vector.h"

class Date{
    private:
        int day, month, year;
    public:
    Date(int day, int month, int year);
    friend ostream& operator << (ostream& dout, const Date& date);
};

class Slip{
    private:
        int slipID;
        Vector<Book*> books;
        int userID;
        Date dateStart, dateEnd;
        bool status;
    public:
    Slip(int slipID,int userID, Date dateStart, Date dateEnd, bool status);
    friend ostream& operator << (ostream& out, const Slip& slip);
    
};    
    /*================*/
    
    Slip::Slip(int slipID, int userID, Date dateStart, Date dateEnd, bool status):
     slipID(slipID),books(books),userID(userID),dateStart(dateStart),dateEnd(dateEnd),status(status)
     {}
    Date::Date(int day,int month,int year):day(day),month(month),year(year){}
ostream& operator << (ostream& out, const Slip& slip){
     out << "slip ID: " << slip.slipID << "\n";
     out << "User ID: " << slip.userID << "\n";
     out << "Date Start: " << slip.dateStart << "\n";
     out << "Date End: " << slip.dateEnd << "\n";
     out << "Status: " << slip.status << "\n";    
}
ostream& operator << (ostream& dout, const Date& date){
    dout << "Day: " << date.day << "\n";
    dout << "Month: " << date.month << "\n";
    dout << "Year : " << date.year << "\n";
}
void Book(Book* books) {
    books.Slip;
}
        
               
        


