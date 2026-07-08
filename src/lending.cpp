#include "lending.h"
#include "user.h"
#include "book.h"
#include "date.h"

namespace library_system{

Lending::Lending(int lendingId, User *borrower, Book *borrowedBook, Date lendingDate)
    : lendingId(lendingId), borrower(borrower), borrowedBook(borrowedBook), lendingDate(lendingDate){}

int Lending::getLendingId() const { return lendingId; }
User *Lending::getBorrower() const { return borrower; }
Book *Lending::getBorrowedBook() const { return borrowedBook; }
Date Lending::getLendingDate() const { return lendingDate; }

}
