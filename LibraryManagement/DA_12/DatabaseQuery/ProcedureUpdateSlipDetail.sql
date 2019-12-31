CREATE PROCEDURE update_slip_detail(
	@SlipID int ,
	@BookID int
)
AS
BEGIN
	DECLARE @Num_copy int;
	SELECT @Num_copy=Num_copy FROM dbo.Books b WHERE b.BookID =@BookID;
	UPDATE dbo.Books SET Num_copy=@Num_copy+1 WHERE BookID=@BookID;
    UPDATE dbo.Slip_Detail SET Status =1 WHERE SlipID=@SlipID;
	UPDATE dbo.Slip_Detail SET DateReturn=GETDATE() WHERE SlipID=@SlipID;
END
-- gọi thử procedure 
EXEC update_slip_detail @SlipID =30002 , @BookID = 102;
