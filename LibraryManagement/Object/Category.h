#pragma once

#include <string>
#include "../Container/Vector.h"
#include "Book.h"
using namespace std;

class Category{
    private:
        int categoryID;
        Vector<Book*> books;
        string categoryName;
        string moreInfo;
	public:
		Category(int categoryID, string categoryName, string moreInfo);
		friend ostream& operator << (ostream& out, const Category& category);
};
Category::Category(int categoryID, string categoryName, string moreInfo):
	 categoryID(categoryID),categoryName(categoryName),moreInfo(moreInfo){}
ostream% operator << (ostream& out, const Category& category){
	out << "Category ID: " << category.categoryID << "\n";
	out << "Category Name: " << category.categoryName << "\n";
	out << "Category Info: " << category.categoryInfo << "\n";
}
 void addBook(Book* book){
 	book.Category;
 }	
//
