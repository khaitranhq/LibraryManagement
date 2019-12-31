#include <iostream>
#include <cctype>
#include <stdio.h>
#include <conio.h>

#include "Container/Trie.h"
#include "Container/TrieNumber.h"
#include "Container/Vector.h"
//#include <vector>

#include "Object/Book.h"
#include "Object/Category.h"
#include "Object/Slip.h"
#include "Object/Student.h"

#include "Database/DatabaseConnect.h"
#include "Functions/Functions.h"

#define left asdfasdfa
#define right asdfav
using namespace std;

const int MAX = 1e6 + 5;

Category *refCategory[MAX];
Book *refBook[MAX];
Student *refStudent[MAX];
Slip *refSlip[MAX];

vector<Category *> categories;
vector<Book *> books;
vector<Slip *> slips;
vector<Student *> students;

Trie<Book> bookTree;
Trie<Category> categoryTree;
TrieNumber<Student> studentTree;

DatabaseConnect DB;

bool checkNumber(const string &s)
{
	if (!s.size())
		return 0;
	for (int i = 0; i < s.size(); ++i)
		if (!isdigit(s[i]))
			return 0;
	return 1;
}

void show_menu()
{
	cout << " 1. Tim thong tin theo sach " << endl;
	cout << " 2. Tim thong tin sach theo danh muc " << endl;
	cout << " 3. Nhap vao ten nguoi dung , hien thi ra cac sach nguoi do chua tra " << endl;
	cout << " 4. Them hoa don " << endl;
	cout << " 5. Tra sach " << endl;
	cout << " 6. Them sinh vien " << endl;
	cout << " 7. Xoa sinh vien" << endl;
	cout << " 8. Thoat chuong trinh" << endl;
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
		studentTree.insert(students[i]->getPhoneNumber(), students[i]);
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

void swap(Book &x, Book &y)
{
	Book tmp = x;
	x = y;
	y = tmp;
}

void sort(vector<Book *> &vtr, const int &l, const int &r)
{
	if (l <= r)
	{
		Book key = *vtr[(r + l) / 2];

		int i = l, j = r;
		while (i <= j)
		{
			while (*vtr[i] < key)
				++i;
			while (*vtr[j] > key)
				--j;
			if (i <= j)
			{
				swap(vtr[i], vtr[j]);
				++i;
				--j;
			}
		}
		if (l < j)
			sort(vtr, l, j);
		if (r > i)
			sort(vtr, i, r);
	}
}

vector<Book *> getBookNotReturn(Student *student)
{
	vector<Book *> ans;
	vector<Slip *> receipts = student->getSlips();
	for (int i = 0; i < receipts.size(); ++i)
	{
		vector<Book *> bookNotRetunInReceipt = receipts[i]->getBookNotReturned();
		for (int j = 0; j < bookNotRetunInReceipt.size(); ++j)
			ans.push_back(bookNotRetunInReceipt[j]);
	}

	sort(ans, 0, ans.size() - 1);
	return ans;
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

	int question;
	show_menu();
	cin >> question;
	if (question == 1)
	{
		string name;
		cout << "Nhap ten sach: " << endl;

		cin.ignore();
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
	}
	if (question == 2)
	{
		string name;
		cout << "Nhap ten danh muc: " << endl;
		cin.ignore();
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
	}
	if (question == 3)
	{
		//continue;
		string phoneNumber;
		Student *student;

		cout << "Moi ban nhap so dien thoai: " << endl;

		cin.ignore();
		while (1)
		{
			cin >> phoneNumber;
			student = studentTree.query(phoneNumber);

			if (student == NULL)
			{
				cout << "Sai so dien thoai, moi ban nhap lai" << endl;
				continue;
			}
			break;
		}
		cout << phoneNumber << endl;
		vector<Book *> bookNotReturn = getBookNotReturn(student);
		if (!bookNotReturn.size())
			cout << "Ban khong muon cuon sach nao!" << endl;
		else
		{
			cout << "Cac sach ban muon: " << endl;
			for (int i = 0; i < bookNotReturn.size(); ++i)
				cout << *bookNotReturn[i] << endl;
		}
	}
	if (question == 4)
	{
		int slipID = slips.back()->getSlipID() + 1;
		string phoneNumber;
		Student *student;

		cout << "Nhap so dien thoai cua ban: " << endl;
		cin.ignore();

		while (1)
		{
			cin >> phoneNumber;

			if (!checkNumber(phoneNumber))
			{
				cout << "So dien thoai khong hop le!" << endl;
				cout << "Moi nhap lai" << endl;
				continue;
			}

			student = studentTree.query(phoneNumber);
			if (student == NULL)
			{
				cout << "Khong ton tai so dien thoai" << endl;
				continue;
			}
			break;
		}

		int numBook;
		cout << "So luong sach ban muon muon: " << endl;
		cin >> numBook;
		Slip *slip = new Slip(slipID, student->getID(), numBook);
		for (int i = 1; i <= numBook; ++i)
		{
			string nameBook;
			vector<Book *> book;
			cout << "Nhap ten cuon sach " << i << ": ";
			while (1)
			{
				cin.ignore();
				getline(cin, nameBook);

				book = bookTree.query(toUpper(nameBook));
				if (book.size() != 1)
				{
					cout << "Moi ban nhap lai ten chinh xac cua sach" << endl;
					continue;
				}

				if (!book[0]->getNumCopy())
				{
					cout << "Sach ban can tim da het, moi nhap ten cuon sach khac" << endl;
					continue;
				}
				break;
			}
			cout << " Cuon sach co ID la " << book[0]->getID() << endl;
			ItemDetail *item = new ItemDetail(book[0]->getID());
			book[0]->decreaseNumcopy();
			slip->addItem(item);
		}
		DB.insert(*slip);
		slips.push_back(slip);
	}
	if (question == 5)
	{
		string phoneNumber;
		cout << " Moi nhap so dien thoai cua ban " << endl;
		cin >> phoneNumber;

		string bookName;
		cout << " Moi nhap ten sach ban muon tra " << endl;
		cin.ignore();

		vector<Book *> ansBook;
		while (1)
		{
			getline(cin, bookName);

			ansBook = bookTree.query(toUpper(bookName));
			if (ansBook.size() != 1)
			{
				cout << "Nhap sai ten, moi nhap lai" << endl;
				continue;
			}
			break;
		}

		int bookID = ansBook[0]->getID();

		Student *student = studentTree.query(phoneNumber);
		vector<Slip *> ansSlip = student->getSlips();

		for (int i = 0; i < ansSlip.size(); ++i)
		{
			vector<ItemDetail *> ansItems = ansSlip[i]->getItems();

			bool flag = 0;
			for (int j = 0; j < ansItems.size(); ++j)
			{
				if (ansItems[j]->getBookID() == ansBook[0]->getID())
				{
					int slipID = ansItems[j]->getSlipID();
					ansItems[j]->setStatus();
					ansBook[0]->increaseNumcopy();

					DB.update_slip_detail(*ansItems[j]);
					flag = 1;
					break;
				}
			}
			if (flag)
				break;
		}
	}
	if (question == 6)
	{
		int userID = students.back()->getID() + 1;
		string username, address, phoneNumber;
		cout << "Nhap ten cua ban: " << endl;
		cin.ignore();
		getline(cin, username);

		cout << "Nhap dia chi cua ban" << endl;
		cin.ignore();
		getline(cin, address);

		cout << "Nhap so dien thoai" << endl;
		cin >> phoneNumber;

		Student* student = new Student(userID, username, address, phoneNumber);
		students.push_back(student);
		refStudent[userID] = student;
		studentTree.insert(phoneNumber, student);
		DB.add_Student(*student);
	}
	if (question == 7)
	{
		string phoneNumber;
		Student *student;
		cout << "Nhap so dien thoai cua ban" << endl;

		while (1)
		{
			cin >> phoneNumber;
			student = studentTree.query(phoneNumber);
			if (student == NULL)
			{
				cout << "So dien thoai khong dung!" << endl;
				continue;
			}
			break;
		}

		for (int i = 0; i < students.size(); ++i)
			if (*student == *students[i])
			{
				students.erase(i);
				break;
			}
		cout << "So sinh vien: " << students.size() << endl;
		studentTree.erase(phoneNumber);
		DB.delete_Student(phoneNumber);
	}
	if (question == 8)
	{
		cout << question << endl;
	}
	cout << "Goodbye" << endl;
	return 0;
}
