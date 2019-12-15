CREATE DATABASE Lib_Management_Final
GO
USE Lib_Management_Final;
GO


CREATE TABLE dbo.Categories (
    CategoryID INT IDENTITY(1,1) NOT NULL  Primary Key,
    Category_Name NVARCHAR(50)  NOT NULL,
	Moreinfo NVARCHAR(100)
);
CREATE TABLE dbo.Books (
    BookID INT IDENTITY(101,1) NOT NULL  PRIMARY KEY ,
    Name_book NVARCHAR(50) NOT NULL,
	Authors NVARCHAR(50) NOT NULL,
    CategoryID INT NOT NULL,
    Num_copy INT  NOT NULL,
    Foreign Key (CategoryID) REFERENCES dbo.Categories(CategoryID) 
	ON UPDATE CASCADE
	ON DELETE CASCADE
);

CREATE TABLE dbo.Students (
    UserID INT IDENTITY(2001,1) NOT NULL,
    Student_Name VARCHAR(50) NOT NULL,
    "Address" VARCHAR(50) NOT NULL,
    Tel CHAR(10) NOT NULL,
    Primary Key (UserID)
);

CREATE TABLE dbo.Slips (
    SlipID INT IDENTITY(30001,1) NOT NULL PRIMARY KEY,
	UserID INT NOT NULL ,
	Number_Book_Borrow INT NOT NULL,
    FOREIGN KEY (UserID) REFERENCES dbo.Students(UserID) ON UPDATE CASCADE
	ON DELETE CASCADE
);
CREATE TABLE dbo.Slip_Detail(
	ID INT IDENTITY(1,1)  PRIMARY KEY NOT NULL ,
	SlipID INT,
	BookID INT,
	"Status" INT,
	DateBorrow DATETIME,
    DateReturn DATETIME NULL,
	FOREIGN KEY (BookID) REFERENCES Books(BookID) ON UPDATE CASCADE
	ON DELETE CASCADE,
	FOREIGN KEY (SlipID) REFERENCES dbo.Slips(SlipID)
);
-- INSERT DATA INTO TABLE Categories  -- 
INSERT INTO Categories 
VALUES 
('Co so du lieu','Access,Oracle'),
('Ecommerce','sach ve thuong mai dien tu'),
('Giai thuat','Giai thuat , Cau Truc Du lieu'),
('He thong','Windows, Linux, Unix'),
('Ngon ngu lap trinh','Visual Basic, C, C++, Java'),
('Phan tich va thiet ke','Phan tich thiet ke giai thuat , he thong thong '),
('Van phong','Word,Excel'),
('Javascript','HTML,Javascipt');
-- INSERT DATA INTO TABLE  Books -- 
INSERT INTO Books
VALUES
('Co so du lieu','Do Trung Tan',001,3),
('SQL Server 7.0','Elicom',001,3),
('Oracle 8i','Tran Tien Dung',001,5),
('Windows2000 Professional','Nguyen Thanh Vinh',004,3),
('Windows2000 Advances Server','Duong Van Chinh',004,5),
('Lap trinh visual Basic 6','Nguyen Tien ',005,3),
('Ngon ngưu lap trinh c++','Tang Dinh Quy',005,5),
('Lap trinh Windows bang Visual c++','Dang Van Duc',005,4),
('Excel Toan Tap','Doan Cong Hung',007,5),
('Word 2000 Toan Tap','Doan Cong Hung',007,4),
('Lam ke toan bang Excel','Vu Duy Sanh',007,5),
('Javascript','Le Minh Tri',008,5),
('HTML','Nguyen Thi Minh Khoa',008,3);
-- INSERT DATA INTO TABLE  Students -- 
INSERT INTO Students
VALUES 
('Nguyen Khanh','92 Quang Trung - Da Nang','0511810583'),
('Nguyen Minh Quoc','92 Quang Trung - Da Nang','0511810583'),
('Ho Phuoc Thoi','92 Quang Trung - Da Nang','0511810583'),
('Nguyen Van Dinh','92 Quang Trung - Da Nang','0511810583'),
('Nguyen Van Hai','92 Quang Trung - Da Nang','0511810583'),
('Nguyen Thi Thu Ha','92 Quang Trung - Da Nang','0511810583'),
('Do Thi Thien Ngan','92 Quang Trung - Da Nang','0511810583'),
('Nguyen Van Anh','30 Phan Châu Trinh - Da Nang','0913576890');
-- INSERT DATA INTO TABLE  Slip -- 
INSERT INTO Slips
VALUES
(2002,1),
(2003,1),
(2004,1),
(2005,1),
(2006,1),
(2007,1),
(2008,0),
(2003,1),
(2002,1),
(2005,1),
(2007,1)
-- INSERT DATA TO TABLE Books_has_slip --
INSERT INTO Slip_Detail
VALUES
(30001,101,1,'2019/06/30','2019/07/25'),
(30002,102,0,'2019/08/15',NULL),
(30003,103,1,'2019/08/10','2019/08/30'),
(30004,104,1,'2019/07/10','2019/07/20'),
(30005,105,0,'2019/08/10',NULL),
(30006,106,1,'2019/08/20','2019/08/25'),
(30007,107,0,'2019/08/30',NULL),
(30008,109,1,'2019/07/15','2019/07/30'),
(30009,110,0,'2019/08/30',NULL),
(30010,111,1,'2019/08/20','2019/08/25'),
(30011,112,0,'2019/08/30',NULL)
