	
-- add custom error use for addSlip --
-- error khi thêm hóa đơn , nhập vào UserID thì không có người dùng đó -- 
EXEC sp_addmessage 
    @msgnum = 50005, 
    @severity = 1, 
    @msgtext = 'UserID ban nhap khong co trong he thong cua chung toi ';
-- Gọi thử error 
RAISERROR ( 50005,1,1)

-- error khi thêm hóa đơn , nhập vào BookID thì không có cuon sach đó -- 
EXEC sp_addmessage 
    @msgnum = 50006, 
    @severity = 1, 
    @msgtext = 'BookID ban nhap khong co trong he thong cua chung toi ';
-- Gọi thử error 
RAISERROR ( 50006,1,1)

EXEC sp_addmessage 
    @msgnum = 50007, 
    @severity = 1, 
    @msgtext = 'BookID và UserID ban nhap khong co trong he thong cua chung toi ';
-- Gọi thử error 
RAISERROR ( 50007,1,1)

EXEC sp_addmessage 
    @msgnum = 50008, 
    @severity = 1, 
    @msgtext = 'Sach ban can hien tai da het trong he thong thu vien cua chung toi  ';
-- Gọi thử error 
RAISERROR ( 50008,1,1)