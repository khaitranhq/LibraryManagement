#pragma once
#include <string>
#include "../Functions/Functions.h"
using namespace std;

class Book{
    private:
        int BookID;
        string name;
        string author;
        int categoryId;
        int numCopy;
	public:
		Book(){}
		Book(int BookID, string name, string author, int categoryId, int numCopy);

		int getID();
		int getCategoryID();
		int getNumCopy();
		string getName();

		void decreaseNumcopy();
		void increaseNumcopy();

		bool operator < (const Book& book);
		bool operator > (const Book& book);

		Book& operator = (const Book& book);
		friend ostream& operator << (ostream& out, const Book& book);
};

/*================Definition of Books=============*/

Book::Book(int BookID, string name, string author, int categoryId, int numCopy):
	BookID(BookID), name(toUpper(name)), author(toUpper(author)), categoryId(categoryId), numCopy(numCopy)
{
}

int Book::getID() { return this->BookID; }
int Book::getCategoryID() { return this->categoryId;  }
int Book::getNumCopy() { return this->numCopy; }
string Book::getName(){ return this -> name; }

void Book::decreaseNumcopy() { --(this->numCopy); }
void Book::increaseNumcopy() { ++(this->numCopy); }

bool Book::operator < (const Book& book) {
	return this->name < book.name;
}

bool Book::operator > (const Book& book) {
	return this->name > book.name;
}

Book& Book::operator = (const Book& book)
{
	this->BookID = book.BookID;
	this->name = book.name;
	this->author = book.author;
	this->categoryId = book.categoryId;
	this->numCopy = book.numCopy;
	return *this;
}

ostream& operator << (ostream& out, const Book& book) {
	out << "Book ID: " << book.BookID << "\n";
	out << "Book's name:  " << book.name << "\n";
	out << "Book's author: " << book.author << "\n";
	out << "Category ID of book: " << book.categoryId << "\n";
	out << "Num copy of book: " << book.numCopy << "\n";
	return out;
}