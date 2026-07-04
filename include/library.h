#pragma once

#include "book.h"
#include "user.h"
#include "document.h"
#include "date.h"
#include "telephone.h"
#include <string>
#include <vector>

namespace Library{

class Library {
    public:
        Library(std::string);

        ~Library();

        int newUser(std::string, Document, Date, Telephone, std::string);

        void userInfo(Document);

        int newBook(std::string, Date, std::string, std::string);

        void bookInfo(int);

        int bookCheckOut(Document, int);

        int bookCheckIn(Document, int);

        void bookStatus(int);
    private:
        std::vector<User*> users;
        std::vector<Book*> books;
};

}
