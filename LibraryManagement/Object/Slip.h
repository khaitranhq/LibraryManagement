#pragma once

#include "Book.h"
#include "../Container/Vector.h"

class Date{
    private:
        int day, month, year;
};

class Slip{
    private:
        int slipID;
        Vector<Book*> books;
        int userID;
        Date dateStart, dateEnd;
        bool status;
};
