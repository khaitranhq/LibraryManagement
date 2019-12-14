#pragma once

#include <string>
//#include "../Container/vector.h"
#include <vector>
#include "Book.h"

#include "../Functions/Functions.h"
using namespace std;

class Category
{
	private:
		int categoryID;
		vector<Book *> books;
		string categoryName;
		string moreInfo;

	public:
		Category(){}
		Category(int categoryID, string categoryName, string moreInfo);

		string getName();
		void addBook(Book* book);
		vector<Book*> getBooks();

		friend ostream &operator<<(ostream &out, const Category &category);
};

Category::Category(int categoryID, string categoryName, string moreInfo) : 
	categoryID(categoryID), categoryName(toUpper(categoryName)), moreInfo(toUpper(moreInfo)) 
{}

ostream& operator<<(ostream &out, const Category &category)
{
	out << "Category ID: " << category.categoryID << "\n";
	out << "Category Name: " << category.categoryName << "\n";
	out << "Category Info: " << category.moreInfo << "\n";
	return out;
}

string Category::getName() { return this->categoryName; }

void Category::addBook(Book *book) { books.push_back(book); }

vector<Book*> Category::getBooks() { return this->books; }
