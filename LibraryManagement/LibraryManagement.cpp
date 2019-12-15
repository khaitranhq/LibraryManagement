#include <iostream>

#include "Container/Trie.h"
//#include "Container/Vector.h"
#include <vector>

#include "Object/Book.h"
#include "Object/Category.h"
#include "Object/Slip.h"
#include "Object/Student.h"

#include "Database/DatabaseConnect.h"
#include "Functions/Functions.h"
using namespace std;

const int MAX = 1e6 + 5;

Category* refCategory[MAX];
Book* refBook[MAX];
Student* refStudent[MAX];

vector<Category*> categories;
vector<Book*> books;
vector<Slip*> slips;
vector<Student*> students;

Trie<Book> bookTree;
Trie<Category> categoryTree;

void show_menu()
{
	cout << " 1. Tim thong tin theo sach " << endl;
	cout << " 2. Tim thong tin sach theo danh muc " << endl;
	cout << " 3. Nhap vao ten nguoi dung , hien thi ra cac sach nguoi do chua tra " << endl;
	cout << " 4. Them hoa don " << endl;
	cout << " 5. Them sach " << endl;
	cout << " 6. Them danh muc " << endl;
	cout << " 7. Thoat chuong trinh" << endl;
	cout << " Moi nhap lua chon cua ban  :  ";
}

void InitBook() {
	for (int i = 0; i < books.size(); ++i) 
		bookTree.insert(books[i] -> getName(), books[i]);
}

void InitCategory() {
	for (int i = 0; i < categories.size(); ++i) {
		categoryTree.insert(categories[i]->getName(), categories[i]);
		refCategory[categories[i]->getID()] = categories[i];
	}

	for (int i = 0; i < books.size(); ++i) {
		int categoryID = books[i]->getCategoryID();
		Category* category = refCategory[categoryID];
		category->addBook(books[i]);
	}
}

void InitStudent() {
	for (int i = 0; i < students.size(); ++i) {
		int studentID = students[i]->getID();
		refStudent[studentID] = students[i];
	}
}

void InitSlip() {
	for (int i = 0; i < slips.size(); ++i) {
		int studentID = slips[i]->getUserID();
		Student* student = refStudent[studentID];
		student->addSlip(slips[i]);
	}
}

int main() {
	DatabaseConnect DB;
	
	categories = DB.getCategory();
	books = DB.getBook();
	students = DB.getStudent();
	slips = DB.getSlip();

	InitBook();
	InitCategory();
	InitStudent();
	InitSlip();

	int question;
	show_menu();
	cin >> question;


	switch (question) {
		case 1: {
			string name;
			cout << "Nhap ten sach: ";
			cin >> name;
			vector<Book*> ans = bookTree.query(toUpper(name));

			cout << "Cac sach tim duoc theo ten: " << endl;
			for (int i = 0; i < ans.size(); ++i)
				cout << *ans[i] << endl;
			break;
		}

		case 2: {
			string name;
			cout << "Nhap ten danh muc: ";
			cin >> name;

			cout << "Cac sach co trong danh muc: " << endl;
			vector<Category*> ansCategory = categoryTree.query(toUpper(name));
			for (int i = 0; i < ansCategory.size(); ++i) {
				vector<Book*> ansBook = ansCategory[i]->getBooks();
				for (int j = 0; j < ansBook.size(); ++j)
					cout << ansBook[j] << endl;
			}
		}
	}

	DB.close();
	return 0;
}