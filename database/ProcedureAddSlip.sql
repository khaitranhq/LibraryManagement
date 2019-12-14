-- tạo procedure thêm hóa đơn --
CREATE PROCEDURE addSlip(
	@UserID int,
	@Number_Book_Borrow int
)
AS
BEGIN
	IF EXISTS (SELECT s.UserID FROM Students s WHERE UserID = @UserID)
	BEGIN
		INSERT INTO dbo.SLips VALUES (@UserID,@Number_Book_Borrow);
	END
	ELSE IF NOT EXISTS (SELECT s.UserID FROM Students s WHERE UserID = @UserID)
		RAISERROR ( 50005,1,1);
END;
-- gọi thử procedure thêm hóa đơn -- 
EXEC addSlip  @UserID=300016, @Number_Book_Borrow=2;
