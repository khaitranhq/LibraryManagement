CREATE PROCEDURE addSlip(
	--@SlipID int,--
	@UserID int,
	@BookID int
)
AS
BEGIN
	IF EXISTS (SELECT s.UserID,b.BookID FROM Students s, Books b WHERE UserID = @UserID AND BookID = @BookID)
	BEGIN
		INSERT INTO dbo.SLip VALUES (@UserID,@BookID,GETDATE(),NULL,0);
		--INSERT INTO dbo.Book_has_Slip VALUES (@SlipID,@BookID);
		SELECT b.Name_book,Students.Student_Name 
		FROM Books b,Students
		WHERE b.BookID=@BookID AND Students.UserID=@UserID;
	END
	ELSE IF NOT EXISTS (SELECT s.UserID,b.BookID FROM Students s, Books b WHERE UserID = @UserID AND BookID = @BookID)
	BEGIN
		RAISERROR (50007,1,1);
	END
	ELSE IF NOT EXISTS (SELECT s.UserID FROM Students s WHERE UserID = @UserID)
		RAISERROR ( 50005,1,1);
	ELSE IF NOT EXISTS ( SELECT b.BookID FROM Books b WHERE BookID = @BookID)
		RAISERROR (50006,1,1);
END

DROP PROCEDURE dbo.addSlip;

EXEC sp_addmessage 
    @msgnum = 50007, 
    @severity = 1, 
    @msgtext = 'BookID và UserID ban nhap khong co trong he thong cua chung toi ';
-- Gọi thử error 
RAISERROR ( 50007,1,1)