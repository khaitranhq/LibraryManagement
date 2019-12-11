CREATE DATABASE Lib_Management
GO
USE Lib_Management;
GO


CREATE TABLE dbo.Categories (
    CategoryID INT NOT NULL  Primary Key,
    Category_Name NVARCHAR(50)  NOT NULL,
	Moreinfo NVARCHAR(100)
);
CREATE TABLE dbo.Books (
    BookID INT NOT NULL  PRIMARY KEY ,
    Name_book NVARCHAR(50) NOT NULL,
	Authors NVARCHAR(50) NOT NULL,
    CategoryID INT NOT NULL,
    Num_copy INT  NOT NULL,
    Foreign Key (CategoryID) REFERENCES dbo.Categories(CategoryID)
);
CREATE TABLE dbo.Students (
    UserID INT NOT NULL,
    Student_Name VARCHAR(50) NOT NULL,
    "Address" VARCHAR(50) NOT NULL,
    Tel CHAR(10) NOT NULL,
    Primary Key (UserID)
);
CREATE TABLE dbo.Slip (
    SlipID INT IDENTITY(30001,1) NOT NULL PRIMARY KEY,
	UserID INT NOT NULL ,
    BookID INT,
    DateBorrow DATETIME,
    DateReturn DATETIME NULL,
    "Status" INT,
    --FOREIGN KEY (BookID) REFERENCES dbo.Books(BookID),
    FOREIGN KEY (UserID) REFERENCES dbo.Students(UserID)
);
CREATE TABLE dbo.Book_has_Slip(
	ID INT IDENTITY(1,1)  PRIMARY KEY NOT NULL ,
	SlipID INT,
	BookID INT,
	FOREIGN KEY (BookID) REFERENCES Books(BookID),
	FOREIGN KEY (SlipID) REFERENCES dbo.Slip(SlipID)
);
-- INSERT DATA INTO TABLE Categories  -- 
INSERT INTO Categories 
VALUES 
(001,'Co so du lieu','Access,Oracle'),
(002,'Ecommerce','sach ve thuong mai dien tu'),
(003,'Giai thuat','Giai thuat , Cau Truc Du lieu'),
(004,'He thong','Windows, Linux, Unix'),
(005,'Ngon ngu lap trinh','Visual Basic, C, C++, Java'),
(006,'Phan tich va thiet ke','Phan tich thiet ke giai thuat , he thong thong '),
(007,'Van phong','Word,Excel'),
(008,'Javascript','HTML,Javascipt');
-- INSERT DATA INTO TABLE  Books -- 
INSERT INTO Books
VALUES
(101,'Co so du lieu','Do Trung Tan',001,3),
(102,'SQL Server 7.0','Elicom',001,3),
(103,'Oracle 8i','Tran Tien Dung',001,5),
(111,'Windows2000 Professional','Nguyen Thanh Vinh',004,3),
(112,'Windows2000 Advances Server','Duong Van Chinh',004,5),
(121,'Lap trinh visual Basic 6','Nguyen Tien ',005,3),
(122,'Ngôn ngữ lap trinh c++','Tang Dinh Quy',005,5),
(123,'Lap trinh Windows bang Visual c++','Dang Van Duc',005,4),
(131,'Excel Toan Tap','Doan Cong Hung',007,5),
(132,'Word 2000 Toan Tap','Doan Cong Hung',007,4),
(133,'Lam ke toan bang Excel','Vu Duy Sanh',007,5),
(141,'Javascript','Le Minh Tri',008,5),
(142,'HTML','Nguyen Thi Minh Khoa',008,3);
-- INSERT DATA INTO TABLE  Students -- 
INSERT INTO Students
VALUES 
(2001,'Vy Van Kiet','92 Quang Trung - Da Nang','0511810583'),
(2002,'Nguyen Khanh','92 Quang Trung - Da Nang','0511810583'),
(2003,'Nguyen Minh Quoc','92 Quang Trung - Da Nang','0511810583'),
(2004,'Ho Phuoc Thoi','92 Quang Trung - Da Nang','0511810583'),
(2005,'Nguyen Van Dinh','92 Quang Trung - Da Nang','0511810583'),
(2006,'Nguyen Van Hai','92 Quang Trung - Da Nang','0511810583'),
(2007,'Nguyen Thi Thu Ha','92 Quang Trung - Da Nang','0511810583'),
(2008,'Đo Thi Thien Ngan','92 Quang Trung - Da Nang','0511810583'),
(2009,'Nguyen Van Anh','30 Phan Châu Trinh - Da Nang','0913576890');
-- INSERT DATA INTO TABLE  Slip -- 
INSERT INTO Slip 
VALUES
(2001,101,'2014/07/30',NULL,0),
(2002,121,'2014/06/30','2014/07/25',1),
(2003,102,'2014/08/15',NULL,0),
(2004,123,'2014/08/10','2014/08/30',1),
(2005,141,'2014/07/10','2014/07/20',1),
(2006,111,'2014/08/10',NULL,0),
(2007,112,'2014/08/20','2014/08/25',1),
(2008,141,'2014/08/30',NULL,0),
(2009,102,'2014/08/10','2014/08/15',1),
(2003,141,'2014/07/15','2014/07/30',1),
(2002,131,'2014/08/30',NULL,0),
(2005,133,'2014/08/20','2014/08/25',1),
(2007,131,'2014/08/30',NULL,0),
(2009,101,'2014/08/20','2014/08/23',1);
-- INSERT DATA TO TABLE Books_has_slip --
INSERT INTO Book_has_Slip
VALUES
(30001,101),
(30001,102),
(30003,102),
(30002,121),
(30004,123),
(30005,141),
(30006,111),
(30007,112),
(30008,141),
(30009,102),
(30010,141),
(30011,131),
(30012,133),
(30013,131),
(30014,101);