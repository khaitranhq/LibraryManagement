#pragma once
#include <iostream>
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include <stdlib.h>
#include <string>

//#include "Container/vector.h"
#include <vector>

#include "Object/Book.h"
#include "Object/Category.h"
#include "Object/Slip.h"
#include "Object/Student.h"

#define SQL_RESULT_LEN 240
#define SQL_RETURN_CODE_LEN 1000
using namespace std;

std::wstring s2ws(const std::string &s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t *buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

string toString(char a[])
{
	string s(a);
	return s;
}

class DatabaseConnect
{
	//define handles and variables
	SQLHANDLE sqlConnHandle;
	SQLHANDLE sqlStmtHandle;
	SQLHANDLE sqlEnvHandle;
	SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];

public:
	DatabaseConnect();
	vector<Book*> getBook();
	vector<Category> getCategory();
	vector<Slip> getSlip();
	vector<Student> getStudent();

	void show_error(unsigned int handletype, const SQLHANDLE &handle);

	void insert(const Slip &slip);
	void close();
};

/*=================Definition of class==============*/
DatabaseConnect::DatabaseConnect()
{
	//initializations
	sqlConnHandle = NULL;
	sqlStmtHandle = NULL;

	//allocations
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle))
		close();

	if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
		close();

	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle))
		close();

	//output
	cout << "Attempting connection to SQL Server...";
	cout << "\n";

	//connect to SQL Server
	//I am using a trusted connection and port 14808
	//it does not matter if you are using default or named instance
	//just make sure you define the server name and the port
	//You have the option to use a username/password instead of a trusted connection
	//but is more secure to use a trusted connection
	switch (SQLDriverConnect(sqlConnHandle,
							 NULL,
							 (SQLWCHAR *)L"DRIVER={SQL Server};SERVER=DESKTOP-TOMPGGO;DATABASE=Lib_Management_Final;",
							 //(SQLWCHAR*)L"DRIVER={SQL Server};SERVER=localhost, 1433;DATABASE=master;Trusted=true;",
							 SQL_NTS,
							 retconstring,
							 1024,
							 NULL,
							 SQL_DRIVER_NOPROMPT))
	{

	case SQL_SUCCESS:
		std::cout << "Successfully connected to SQL Server1";
		cout << "\n";
		break;

	case SQL_SUCCESS_WITH_INFO:
		cout << "Successfully connected to SQL Server2";
		cout << "\n";
		break;

	case SQL_INVALID_HANDLE:
		cout << "Could not connect to SQL Server";
		cout << "\n";
		close();

	case SQL_ERROR:
		cout << "Could not connect to SQL Server";
		cout << "\n";
		close();

	default:
		break;
	}

	//if there is a problem connecting then exit application
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
		close();
}

vector<Book*> DatabaseConnect::getBook()
{
	cout << "\n";
	cout << "Executing T-SQL query...";
	cout << "\n";

	vector<Book*> ans;
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR *)L"SELECT * FROM Books", SQL_NTS))
	{
		cout << "Error querying SQL Server";
		cout << "\n";
		close();
	}
	else
	{
		int id, categoryID, numCopy;
		char name[50];
		char author[50];
		while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS)
		{
			SQLGetData(sqlStmtHandle, 1, SQL_C_LONG, &id, 3, NULL);
			SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR, &name, 50, NULL);
			SQLGetData(sqlStmtHandle, 3, SQL_C_CHAR, &author, 50, NULL);
			SQLGetData(sqlStmtHandle, 4, SQL_C_LONG, &categoryID, 2, NULL);
			SQLGetData(sqlStmtHandle, 5, SQL_C_LONG, &numCopy, 2, NULL);
			Book *book = new Book(id, toString(name), toString(author), categoryID, numCopy);
			ans.push_back(book);
		}
	}
	return ans;
}

vector<Category> DatabaseConnect::getCategory()
{
	cout << "\n";
	cout << "Executing T-SQL query...";
	cout << "\n";

	vector<Category> ans;
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR *)L"SELECT * FROM Categoriess", SQL_NTS))
	{
		cout << "Error querying SQL Server";
		cout << "\n";
		close();
	}
	else
	{
		int id;
		char name[50];
		char moreInfo[100];
		while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS)
		{
			SQLGetData(sqlStmtHandle, 1, SQL_C_LONG, &id, 3, NULL);
			SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR, &name, 50, NULL);
			SQLGetData(sqlStmtHandle, 3, SQL_C_CHAR, &moreInfo, 100, NULL);
			ans.push_back(Category(id, toString(name), toString(moreInfo)));
		}
	}
	return ans;
}

/*vector<Slip> DatabaseConnect::getSlip() {
	cout << "\n";
	cout << "Executing T-SQL query...";
	cout << "\n";

	vector<Slip> ans;
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)L"SELECT * FROM Slip", SQL_NTS)) {
		cout << "Error querying SQL Server";
		cout << "\n";
		close();
	}
	else {
		int id, BookId, numCopy;
		char name[50];
		char author[50];
		while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {
			SQLGetData(sqlStmtHandle, 1, SQL_C_LONG, &id, 3, NULL);
			SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR, &name, 50, NULL);
			SQLGetData(sqlStmtHandle, 3, SQL_C_CHAR, &author, 50, NULL);
			SQLGetData(sqlStmtHandle, 4, SQL_C_LONG, &categoryID, 2, NULL);
			SQLGetData(sqlStmtHandle, 5, SQL_C_LONG, &numCopy, 2, NULL);
			ans.push_back(Slip(id, toString(name), toString(author), categoryID, numCopy));
		}
	}
	return ans;
}*/

vector<Student> DatabaseConnect::getStudent()
{
	cout << "\n";
	cout << "Executing T-SQL query...";
	cout << "\n";

	vector<Student> ans;
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR *)L"SELECT * FROM Books", SQL_NTS))
	{
		cout << "Error querying SQL Server";
		cout << "\n";
		close();
	}
	else
	{
		int id;
		char name[50];
		char address[50];
		char tel[10];
		while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS)
		{
			SQLGetData(sqlStmtHandle, 1, SQL_C_LONG, &id, 3, NULL);
			SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR, &name, 50, NULL);
			SQLGetData(sqlStmtHandle, 3, SQL_C_CHAR, &address, 50, NULL);
			SQLGetData(sqlStmtHandle, 4, SQL_C_LONG, &tel, 10, NULL);
			ans.push_back(Student(id, toString(name), toString(address), toString(tel)));
		}
	}
	return ans;
}

void DatabaseConnect::show_error(unsigned int handletype, const SQLHANDLE &handle)
{
	SQLWCHAR sqlstate[1024];
	SQLWCHAR message[1024];
	if (SQL_SUCCESS == SQLGetDiagRec(handletype, handle, 1, sqlstate, NULL, message, 1024, NULL))
		std::wcout << L"Message: " << message << L"\nSQLSTATE: " << sqlstate << std::endl;
}

/*void DatabaseConnect::insert(const Slip& slip)
{
	string str = "EXEC addSlip  @UserID =" + to_string(slip.getUserID()) + ",@Number_Book_Borrow =" + to_string(slip.getNumberBooks) + ";";
	wstring a = s2ws(str);
	LPCWSTR result = a.c_str();
	while (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)result, SQL_NTS))
	{
		int choice;
		show_error(SQL_HANDLE_STMT, sqlStmtHandle);
		cout << " ban co muon nhap lai thong tin khong ? (1.CO \t 2.KHONG ) " << endl;
		cout << " moi nhap lua chon cua ban :  ";
		cin >> choice;
		if (choice == 1)
			goto addSlipAgain;
		else
			goto here4;
	}

	if (SQLFetch(sqlStmtHandle) == SQL_SUCCESS)
	{
		int SlipID, BookID;
		cout << " Mời nhập chi tiết hóa đơn có ID " << SlipID << " : ";
		for (int i = 0; i < number; i++)
		{
			cout << " Mời nhập ID cuốn sách người dùng mượn  : ";
			cin >> BookID;
			// thêm vào DB
			string str1 = " EXEC add_Slip_Detail @SlipID = " + to_string(SlipID) + ",@BookID=" + to_string(BookID);
			wstring b = s2ws(str1);
			LPCWSTR result1 = b.c_str();
			if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)result, SQL_NTS))
			{
				show_error(SQL_HANDLE_STMT, sqlStmtHandle);
			}
			else
			{
				// gọi constructor slip_detail
				cout << " Thêm chi tiết hóa đơn thành công  !!!!";
			}
		}
		cout << " Them hoa don thanh cong " << endl;
	}
here4: break;

}*/

void DatabaseConnect::close()
{
	SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
	SQLDisconnect(sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
	getchar();
	exit(0);
}