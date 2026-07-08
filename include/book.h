#pragma once

#include "date.h"
#include <ostream>
#include <string>
#include <iostream>

namespace library_system {

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

    private:
        int bookId;
        std::string title;
        Date releaseDate;
        std::string author;
        std::string genre;
};

class DuplicatedBook : public std::exception {
    public:
        virtual const char *what() const throw(){
            return "ERROR. There is another book with the same title.";
        }
};

class BookAlreadyBorrowed : public std::exception {
    public:
        virtual const char *what() const throw(){
            return "ERROR. This book was already borrowed.";
        }
};

class BookNotFound : public std::exception {
    public:
        virtual const char *what() const throw(){
            return "ERROR. This book doesn't exist.";
        }
};

} // namespace library_system
