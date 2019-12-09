#pragma once

using namespace std;

class Book{
    private:
        int BookID;
        string name;
        string author;
        int categoryId;
        int numCopy;
	public:
		friend ostream& operator << (ostream& out, const Book& book);
};

/*================Definition of Books=============*/

ostream& operator << (ostream& out, const Book& book) {
	out << "Book ID: " << book.BookID << "\n";
	out << "Book's name:  " << book.name << "\n";
	out << "Book's author: " << book.author << "\n";
	out << "Category ID of book: " << book.categoryId << "\n";
	out << "Num copy of book: " << book.numCopy << "\n";
}