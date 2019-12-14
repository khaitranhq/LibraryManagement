#pragma once

#include <string>
#include "Slip.h"
#include <vector>
using namespace std;

class Student
{
private:
    int userID;
    vector<Slip *> receipt;
    string username;
    string address;
    string phoneNumber;

public:
    Student(){}
    Student(int userID, string username, string address, string phoneNumber);
    void addSlip(Slip *slip);
    friend ostream &operator<<(ostream &out, const Student &student);
};
/*======================================*/
Student::Student(int userID, string username, string address, string phoneNumber) : userID(userID), username(username), address(address), phoneNumber(phoneNumber)
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
