#pragma once

#include <string>
//#include "../Container/vector.h"
#include <vector>
#include "Book.h"
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
		void addBook(Book* book);
		vector<Book*> getBooks();
		friend ostream &operator<<(ostream &out, const Category &category);
};

Category::Category(int categoryID, string categoryName, string moreInfo) : categoryID(categoryID), categoryName(categoryName), moreInfo(moreInfo) {}

ostream& operator<<(ostream &out, const Category &category)
{
	out << "Category ID: " << category.categoryID << "\n";
	out << "Category Name: " << category.categoryName << "\n";
	out << "Category Info: " << category.moreInfo << "\n";
	return out;
}
void Category::addBook(Book *book)
{
	books.push_back(book);
}

vector<Book*> Category::getBooks() {
	return this->books;
}
