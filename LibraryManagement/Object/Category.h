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
		friend ostream& operator << (ostream& out, const Category& category);
};