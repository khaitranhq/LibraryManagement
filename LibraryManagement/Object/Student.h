#pragma once

#include <string>
#include "Slip.h"

class Student{
    private:
        int userID;
        Vector<Slip*> receipt;
        string username;
        string address;
        int phoneNumber;
};
public:
    Student(int userID, string name, string author, int categoryId, int numCopy);
		friend ostream& operator << (ostream& out, const Book& book);
};
/*======================================*/

Student::Student(int userID,string username, string address,int phoneNumber ):
    userID(userID),username(username),address(address),phoneNumber(phoneNumber)
    {}
ostream& operator << (ostream& out, const Student& student){
     out << "user ID: " << student.userID << "\n";
     out << "User Name: " << student.username << "\n";
     out << "Address: " << student.address << "\n";
     out << "PhoneNumber: " << student.phoneNumber << "\n";
         
}
