CREATE PROCEDURE add_Slip_Detail (
	@SlipID int,
	@BookID int
)
AS 
BEGIN
	 IF EXISTS (SELECT b.BookID FROM Books b WHERE BookID = @BookID)
	BEGIN
		DECLARE @Num_copy int;
		SELECT @Num_copy=Num_copy FROM dbo.Books b WHERE b.BookID =@BookID;
		IF(@Num_copy <=0)
		BEGIN
			RAISERROR(50008,1,1);
			ROLLBACK TRANSACTION;
		END
		ELSE
		BEGIN
			UPDATE dbo.Books SET Num_copy=@Num_copy-1 WHERE BookID=@BookID;
			INSERT INTO dbo.SLip_Detail VALUES (@SlipID,@BookID,0,GETDATE(),NULL);
		END
	END
	ELSE IF NOT EXISTS (SELECT b.BookID FROM Books b WHERE BookID = @BookID)
		RAISERROR ( 50006,1,1);
END
-- gọi thử procedure add_Slip_detail--
EXEC add_Slip_Detail @SlipID=3001, @BookID=1032321;