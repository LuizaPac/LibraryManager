#pragma once

#include "date.h"
#include <ostream>
#include <string>
#include <iostream>

namespace library_system {

class User;

class Book {
    public:
        Book(int, std::string, Date, std::string, std::string);

        friend std::ostream &operator<<(std::ostream &, const Book &);

        // Get methods
        int getBookId() const;
        std::string getTitle() const;
        Date getReleaseDate() const;
        std::string getAuthor() const;
        std::string getGenre() const;
        User *getBorrower() const;

    private:
        int bookId;
        std::string title;
        Date releaseDate;
        std::string author;
        std::string genre;
        User *checkedOutBy;
};

} // namespace library_system
