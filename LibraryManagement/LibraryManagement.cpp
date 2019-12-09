//include the below additional libraries
#include <iostream>
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include <stdlib.h>
#include <string>

#include "Object/Book.h"
#include "Object/Category.h"
#include "Object/Slip.h"
#include "Object/Student.h"

#include "Container/Vector.h"
#include "Container/Trie.h"


void show_error(unsigned int handletype, const SQLHANDLE& handle) {
	SQLWCHAR sqlstate[1024];
	SQLWCHAR message[1024];
	if (SQL_SUCCESS == SQLGetDiagRec(handletype, handle, 1, sqlstate, NULL, message, 1024, NULL))
		std::wcout << L"Message: " << message << L"\nSQLSTATE: " << sqlstate << std::endl;
}
std::wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

//use the std namespace
using namespace std;
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

int main() {
CONTINUEAGAIN:
#define SQL_RESULT_LEN 240
#define SQL_RETURN_CODE_LEN 1000
	//define handles and variables
	SQLHANDLE sqlConnHandle;
	SQLHANDLE sqlStmtHandle;
	SQLHANDLE sqlEnvHandle;
	SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];

	//initializations
	sqlConnHandle = NULL;
	sqlStmtHandle = NULL;

	//allocations
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle))
		goto COMPLETED;

	if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
		goto COMPLETED;

	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle))
		goto COMPLETED;

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
		(SQLWCHAR*)L"DRIVER={SQL Server};SERVER=DESKTOP-TOMPGGO;DATABASE=Lib_Management;",
		//(SQLWCHAR*)L"DRIVER={SQL Server};SERVER=localhost, 1433;DATABASE=master;Trusted=true;",
		SQL_NTS,
		retconstring,
		1024,
		NULL,
		SQL_DRIVER_NOPROMPT)) {

	case SQL_SUCCESS:
		std::cout << "Successfully connected to SQL Server1";
		cout << "\n";
		break;

		//case SQL_SUCCESS_WITH_INFO:
		cout << "Successfully connected to SQL Server2";
		cout << "\n";
		break;

	case SQL_INVALID_HANDLE:
		cout << "Could not connect to SQL Server";
		cout << "\n";
		goto COMPLETED;

	case SQL_ERROR:
		cout << "Could not connect to SQL Server";
		cout << "\n";
		goto COMPLETED;

	default:
		break;
	}

	//if there is a problem connecting then exit application
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
		goto COMPLETED;

	//output
	cout << "\n";
	cout << "Executing T-SQL query...";
	cout << "\n";

	while (true) {
		show_menu();
		int question;
		cin >> question;
		switch (question) {
		case 1: {
			//if there is a problem executing the query then exit application
		//else display query result
		// EXEC fBookByName @nameBook = 'Co so du lieu';
		Again1:
			if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)L"SELECT * FROM Books", SQL_NTS)) {
				show_error(SQL_HANDLE_STMT, sqlStmtHandle);
				cout << "Error querying SQL Server";
				goto here;
			}
			else {
				while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS)
				{
					int bookId, categoryId, numCopy;
					char bookName[50];
					char bookAuthor[50];

					SQLGetData(sqlStmtHandle, 1, SQL_C_LONG, &bookId, 5, NULL);
					SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR, &bookName, 50, NULL);
					SQLGetData(sqlStmtHandle, 3, SQL_C_CHAR, &bookAuthor, 50, NULL);
					SQLGetData(sqlStmtHandle, 4, SQL_C_LONG, &categoryId, 5, NULL);
					SQLGetData(sqlStmtHandle, 5, SQL_C_LONG, &numCopy, 5, NULL);

				}
			}
		here:
			goto CONTINUEAGAIN;
			break;
			//stop1: {cout << " cuon sach nay khong co trong he thu vien cua ban " << endl;  }
		}
		case 2: {
			//if there is a problem executing the query then exit application
			//else display query result
			// EXEC fBookByName @nameBook = 'Co so du lieu';
		Again2:
			string Cname;
			cout << " Moi nhap danh muc ban can kiem :  ";
			cin.ignore();
			getline(std::cin, Cname);
			// EXEC fBookByCategory @nameCategory = 'CO SO DU LIEU';
			string str = "EXEC fBookByCategory @nameCategory ='" + Cname + "'";
			wstring a = s2ws(str);
			LPCWSTR result = a.c_str();

			if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)result, SQL_NTS)) {
				show_error(SQL_HANDLE_STMT, sqlStmtHandle);
				int choice;
				cout << " ban co muon nhap lai thong tin khong ? (1.CO \t 2.KHONG ) " << endl;
				cout << " moi nhap lua chon cua ban :  "; cin >> choice;
				if (choice == 1)
					goto Again2;
				else
					goto here2;
			}
			else {

				cout << "Thong tin cua danh muc " + Cname + " la :" << "\n";
				while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS)
				{
					char Bname1[50];
					char AuthorName[50];
					if (SQLGetData(sqlStmtHandle, 1, SQL_C_CHAR, &Bname1, 50, 0) != SQL_SUCCESS)
					{
						goto stop2;

					}

					SQLGetData(sqlStmtHandle, 1, SQL_C_CHAR, &Bname1, 50, NULL);
					SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR, &AuthorName, 50, NULL);

					cout << Bname1 << " co tac gia la " << AuthorName << endl;
					if (SQLFetch(sqlStmtHandle) != SQL_SUCCESS) {
						goto here2;
					}

				}
			stop2:cout << " Danh muc " << Cname << " khong co trong he thong thu vien cua chung toi" << endl;
			}
		here2:
			//goto CONTINUEAGAIN;
			break;
		}
		case 3: {
		Again3:
			string Sname;
			cout << " Moi nhap ten hoc sinh ban can tim : ";
			cin.ignore();
			getline(std::cin, Sname);
			string str = "EXEC fBookNotReturnedByName @name = '" + Sname + "'";
			wstring a = s2ws(str);
			LPCWSTR result = a.c_str();

			int BookID;
			char Bname1[50];
			char DateBorrow[50];
			if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)result, SQL_NTS)) {
				show_error(SQL_HANDLE_STMT, sqlStmtHandle);
				int choice;
				cout << " ban co muon nhap lai thong tin khong ? (1.CO \t 2.KHONG ) " << endl;
				cout << " moi nhap lua chon cua ban :  "; cin >> choice;
				if (choice == 1)
					goto Again3;
				else
					goto here3;
			}
			else {
				while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS)
				{
					if (SQLGetData(sqlStmtHandle, 1, SQL_C_CHAR, &Bname1, 50, 0) != SQL_SUCCESS) {
						goto stop3;
					}
					cout << "Thong tin muon sach cua hoc sinh " + Sname + " la :" << "\n";
					SQLGetData(sqlStmtHandle, 1, SQL_C_LONG, &BookID, 5, NULL);
					SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR, &Bname1, 50, NULL);
					SQLGetData(sqlStmtHandle, 3, SQL_C_CHAR, &DateBorrow, 50, NULL);

					cout << " Hoc sinh " + Sname + " chua tra cuon " + Bname1 + " co so ID la " + to_string(BookID)
						+ " muon vao ngay " + DateBorrow << endl;
					goto here3;
				}
			stop3:
				cout << " Hoc sinh " << Sname << " khong co trong he thong thu vien cua chung toi " << endl;
				goto CONTINUEAGAIN;
			}
		here3:
			//goto CONTINUEAGAIN;
			break;
		}
		case 4: {

			//int SlipID;
			int UserID;
			int BookID;
		addSlipAgain:
			//cout << " Moi  nhap ID hoa don  : "; cin >> SlipID;
			cout << " Moi nhap ID nguoi dung can muon : "; cin >> UserID;
			cout << " Moi nhap ID cuon sach nguoi dung can muon : "; cin >> BookID;

			// EXEC addSlip @SlipID = 30020 , @UserID=2009, @BookID = 142;
			string str = "EXEC addSlip @UserID =" + to_string(UserID) + ",@BookID =" + to_string(BookID) + ";";
			wstring a = s2ws(str);
			LPCWSTR result = a.c_str();
			while (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)result, SQL_NTS)) {
				int choice;
				show_error(SQL_HANDLE_STMT, sqlStmtHandle);
				cout << " ban co muon nhap lai thong tin khong ? (1.CO \t 2.KHONG ) " << endl;
				cout << " moi nhap lua chon cua ban :  "; cin >> choice;
				if (choice == 1)
					goto addSlipAgain;
				else
					goto here4;
			}

			if (SQLFetch(sqlStmtHandle) == SQL_SUCCESS)
			{
				char Bname[50];
				char Sname[50];
				SQLGetData(sqlStmtHandle, 1, SQL_C_CHAR, Bname, 50, NULL);
				SQLGetData(sqlStmtHandle, 2, SQL_C_CHAR, Sname, 50, NULL);
				cout << " Them phieu muon  thanh cong " << endl;
				cout << " Cuon sach " << Bname << " muon boi nguoi dung" << Sname << endl;
			}
		here4:break;

		}

		}// end switch
	}// end while

COMPLETED:
	SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
	SQLDisconnect(sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);

	//pause the console window - exit when key is pressed
	return 0;
}
