#pragma once

#include "document.h"
#include "date.h"
#include "telephone.h"
#include <ostream>
#include <string>
#include <vector>
#include <iostream>

namespace Library{

// Class book just to say it exists
class Book;

class User{
    public:
        User(int, std::string, Document, Date, std::string);

        friend std::ostream &operator<<(std::ostream &, const User &);

        void insertNewBorrowedBook(Book*);

        void returnBook(Book*);

        // Get methods
        int getUserId() const;
        std::string getName() const;
        Document getDocumentNumber() const;
        Date getBirthDate() const;
        std::string getEmail() const;
        std::vector<Book*> getBorrowedBooks() const;

    private:
        int userId;
        std::string name;
        Document documentNumber;
        Date birthDate;
        std::string email;
        std::vector<Book*> borrowedBook;
};

}

