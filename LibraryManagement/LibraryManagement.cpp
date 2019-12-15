#include <iostream>
#include <stdio.h>
#include <conio.h>

#include "Container/Trie.h"
#include "Container/Vector.h"
//#include <vector>

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
Slip* refSlip[MAX];

vector<Category *> categories;
vector<Book *> books;
vector<Slip *> slips;
vector<Student *> students;

Trie<Book> bookTree;
Trie<Category> categoryTree;
Trie<Student> studentTree;

DatabaseConnect DB;

void show_menu()
{
	cout << " 1. Tim thong tin theo sach " << endl;
	cout << " 2. Tim thong tin sach theo danh muc " << endl;
	cout << " 3. Nhap vao ten nguoi dung , hien thi ra cac sach nguoi do chua tra " << endl;
	cout << " 4. Them hoa don " << endl;
	cout << " 5. Them sach " << endl;
	cout << " 6. Them danh muc " << endl;
	cout << " 7. Thoat chuong trinh" << endl;
}

void InitBook()
{
	for (int i = 0; i < books.size(); ++i)
	{
		bookTree.insert(books[i]->getName(), books[i]);

		int bookID = books[i]->getID();
		refBook[bookID] = books[i];
	}
}

void InitCategory()
{
	for (int i = 0; i < categories.size(); ++i)
	{
		categoryTree.insert(categories[i]->getName(), categories[i]);
		refCategory[categories[i]->getID()] = categories[i];
	}

	for (int i = 0; i < books.size(); ++i)
	{
		int categoryID = books[i]->getCategoryID();
		Category *category = refCategory[categoryID];
		category->addBook(books[i]);
	}
}

void InitStudent()
{
	for (int i = 0; i < students.size(); ++i)
	{
		studentTree.insert(students[i]->getName(), students[i]);
		int studentID = students[i]->getID();
		refStudent[studentID] = students[i];
	}
}

void InitSlip()
{
	vector<Slip *> s;
	for (int i = 0; i < slips.size(); ++i)
	{
		int studentID = slips[i]->getUserID();
		int slipID = slips[i]->getSlipID();

		refSlip[slipID] = slips[i];
		Student *student = refStudent[studentID];
		student->addSlip(slips[i]);
	}

	vector<ItemDetail *> items = DB.getItemDetail();
	for (int i = 0; i < items.size(); ++i)
	{
		items[i]->setBook(refBook[items[i]->getBookID()]);
		int slipID = items[i]->getSlipID();
		Slip *slip = refSlip[slipID];
		slip->addItem(items[i]);
	}
}

int main()
{
	categories = DB.getCategory();
	books = DB.getBook();
	students = DB.getStudent();
	slips = DB.getSlip();

	InitBook();
	InitCategory();
	InitStudent();
	InitSlip();

	show_menu();
	int question;
	cout << " Moi nhap lua chon cua ban  :  ";
	scanf_s("%d", &question);
	switch (question)
	{
		case 1:
		{
			string name;
			cout << "Nhap ten sach: " << endl;
			getchar();
			getline(cin, name);
			vector<Book *> ans = bookTree.query(toUpper(name));

			if (ans.size() == 0)
				cout << "Cuon sach khong co trong thu vien!!" << endl;
			else
			{
				cout << "Cac sach tim duoc theo ten: " << endl;
				for (int i = 0; i < ans.size(); ++i)
					cout << *ans[i] << endl;
			}
			break;
		}

		case 2:
		{
			string name;
			cout << "Nhap ten danh muc: " << endl;
			getchar();
			getline(cin, name);

			vector<Category *> ansCategory = categoryTree.query(toUpper(name));

			if (ansCategory.size() == 0)
				cout << "Danh muc khong co trong thu vien!!" << endl;
			else
			{
				cout << "Cac sach co trong danh muc: " << endl;
				for (int i = 0; i < ansCategory.size(); ++i)
				{
					vector<Book *> ansBook = ansCategory[i]->getBooks();
					if (ansBook.size() == 0)
						cout << "Khong co sach trong danh muc!!!" << endl;
					else
						for (int j = 0; j < ansBook.size(); ++j)
							cout << *ansBook[j] << endl;
				}
			}
			break;
		}
		case 3:
		{
			string name;
			cout << "Nhap ten cua ban: " << endl;
			getchar();
			getline(cin, name);

			vector<Student *> student = studentTree.query(toUpper(name));
			for(int k = 0 ; k < student.size() ; ++k){
				int cnt = 0;
				cout << "Cac sach chua tra cua " << student[k]->getName() << endl;
				vector<Slip *> receipts = student[0]->getSlips();
				for (int i = 0; i < receipts.size(); ++i)
				{
					vector<Book *> bookNotReturn = receipts[i]->getBookNotReturned();
					for (int j = 0; j < bookNotReturn.size(); ++j)
					{
						cout << *bookNotReturn[j] << endl;
						++cnt;
					}
				}
				if (!cnt)
					cout << "Ban khong muon cuon sach nao!" << endl;
			}
			break;
		}
		case 4:
		{
			int slipID = slips.back()->getSlipID() + 1;

			string name;
			cout << "Ten cua ban: ";
			getchar();
			getline(cin, name);
			vector<Student*> student = studentTree.query(toUpper(name));

			int numBook;
			cout << "So luong sach ban muon muon: ";
			cin >> numBook;
			Slip*  slip = new Slip(slipID, student[0]->getID(), numBook);
			for (int i = 1; i <= numBook; ++i) {
				string nameBook;
				cout << "Nhap ten cuon sach " << i << ": ";
				getchar();
				getline(cin, nameBook);
				vector<Book*> book = bookTree.query(toUpper(nameBook));
				ItemDetail* item = new ItemDetail(book[0]->getID());
				slip->addItem(item);
			}
			DB.insert(*slip);
			slips.push_back(slip);
		}
		case 7:
			return 0;
	}
}