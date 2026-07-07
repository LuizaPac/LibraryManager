#pragma once

#include "user.h"
#include "book.h"
#include "date.h"

namespace library_system {

class Lending {
    public:
        Lending(User *, Book *, Date);

        // Get methods
        User *getBorrower();
        Book *getBorrowedBook();
        Date getLendingDate();

    private:
        User *borrower;
        Book *borrowedBook;
        Date lendingDate;
};

}
