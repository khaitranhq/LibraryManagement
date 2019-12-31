#pragma once

#include <string>
#include "Slip.h"
#include "../Container/Vector.h"
//#include <vector>

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

		string getAddress();
		string getName();
		string getPhoneNumber();
		string getUsername();
		int getID();
		vector<Slip*> getSlips();
		void addSlip(Slip *slip);

		bool operator == (const Student& student);
		friend ostream &operator<<(ostream &out, const Student &student);
};
/*======================================*/
Student::Student(int userID, string username, string address, string phoneNumber) : 
	userID(userID), username(toUpper(username)), address(toUpper(address)), phoneNumber(phoneNumber)
{
}

int Student::getID() { return this->userID; }
string Student::getName() { return this->username; }

string Student::getPhoneNumber() { return this->phoneNumber; }

string Student::getUsername() { return this->username; }

string Student::getAddress() { return this->address; }

vector<Slip*> Student::getSlips() { return this->receipt; }

void Student::addSlip(Slip* slip) { receipt.push_back(slip); }

bool Student::operator == (const Student& student) {
	return this->phoneNumber == student.phoneNumber;
}

ostream &operator<<(ostream &out, const Student &student)
{
    out << "user ID: " << student.userID << "\n";
    out << "User Name: " << student.username << "\n";
    out << "Address: " << student.address << "\n";
    out << "PhoneNumber: " << student.phoneNumber << "\n";
	//out << "SLip: " << student.receipt.size() << "\n";
	return out;
}
