#include "lending.h"
#include "user.h"
#include "book.h"
#include "date.h"

namespace library_system{

Lending::Lending(User *borrower, Book *borrowedBook, Date lendingDate) : borrower(borrower), borrowedBook(borrowedBook), lendingDate(lendingDate){}

User *Lending::getBorrower(){ return borrower; }
Book *Lending::getBorrowedBook(){ return borrowedBook; }
Date Lending::getLendingDate(){ return lendingDate; }

}
