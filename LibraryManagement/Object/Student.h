#pragma once

#include <string>
#include "Slip.h"

class Student
{
private:
    int userID;
    Vector<Slip *> receipt;
    string username;
    string address;
    int phoneNumber;

public:
    Student(){}
    Student(int userID, string username, string address, int phoneNumber);
    void addSlip(Slip *slip);
    friend ostream &operator<<(ostream &out, const Student &student);
};
/*======================================*/
Student::Student(int userID, string username, string address, int phoneNumber) : userID(userID), username(username), address(address), phoneNumber(phoneNumber)
{
}
ostream &operator<<(ostream &out, const Student &student)
{
    out << "user ID: " << student.userID << "\n";
    out << "User Name: " << student.username << "\n";
    out << "Address: " << student.address << "\n";
    out << "PhoneNumber: " << student.phoneNumber << "\n";
	return out;
}
void Student::addSlip(Slip *slip)
{
    receipt.push_back(slip);
}
