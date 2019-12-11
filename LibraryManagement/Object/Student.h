#pragma once
//
#include <string>
#include "Slip.h"

class Student{
    private:
        int userID;
        Vector<Slip*> receipt;
        string username;
        string address;
        int phoneNumber;
};
