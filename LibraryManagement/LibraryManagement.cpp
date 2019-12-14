#include <iostream>

#include "Container/Trie.h"
//#include "Container/Vector.h"
#include <vector>

#include "Object/Book.h"
/*#include "Object/Category.h"
#include "Object/Slip.h"
#include "Object/Student.h"*/

#include "DatabaseConnect.h"

using namespace std;

//vector<Category> categories;
vector<Book*> books;
//vector<Slip> slips;
//vector<Student> students;

Trie<Book> bookTree;

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

	for (int i = 0; i < 1; ++i)
		bookTree.insert(books[i] -> getName(), books[i]);
}

int main() {
	DatabaseConnect DB;

	books = DB.getBook();


	InitBook();

	return 0;
	int question;
	show_menu();
	cin >> question;


	switch (question) {
		case 1: {
			string name;
			cout << "Nhap ten sach: ";
			cin >> name;
			vector<Book*> ans = bookTree.query(name);
			for (int i = 0; i < ans.size(); ++i)
				cout << *ans[i] << endl;
			break;
		}
	}
	return 0;
}