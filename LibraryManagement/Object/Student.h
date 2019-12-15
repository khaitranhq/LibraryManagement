#pragma once

#include <string>
#include "Slip.h"
#include <vector>

#include "../Functions/Functions.h"
using namespace std;

class Student
{
	private:
		int userID;
		vector<Slip*> receipt;
		string username;
		string address;
		string phoneNumber;

	public:
		Student(){}
		Student(int userID, string username, string address, string phoneNumber);

		string getName();
		int getID();
		vector<Slip*> getSlips();
		void addSlip(Slip *slip);

		friend ostream &operator<<(ostream &out, const Student &student);
};
/*======================================*/
Student::Student(int userID, string username, string address, string phoneNumber) : 
	userID(userID), username(toUpper(username)), address(toUpper(address)), phoneNumber(toUpper(phoneNumber))
{
}

int Student::getID() { return this->userID; }
string Student::getName() { return this->username; }
vector<Slip*> Student::getSlips() { return this->receipt; }
void Student::addSlip(Slip* slip) { receipt.push_back(slip); }

ostream &operator<<(ostream &out, const Student &student)
{
    out << "user ID: " << student.userID << "\n";
    out << "User Name: " << student.username << "\n";
    out << "Address: " << student.address << "\n";
    out << "PhoneNumber: " << student.phoneNumber << "\n";
	out << "SLip: " << student.receipt.size() << "\n";
	return out;
}
