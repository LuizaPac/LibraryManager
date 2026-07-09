#pragma once

#include "date.h"
#include "author.h"
#include "genre.h"
#include <ostream>
#include <string>
#include <iostream>

namespace library_system {

class Book {
    public:
        Book(int, std::string, Date, Author *, Genre *);

        friend std::ostream &operator<<(std::ostream &, const Book &);

        // Get methods
        int getBookId() const;
        std::string getTitle() const;
        Date getReleaseDate() const;
        Author *getAuthor() const;
        Genre *getGenre() const;

    private:
        int bookId;
        std::string title;
        Date releaseDate;
        Author *author;
        Genre *genre;
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

class BookWasNotBorrowed : public std::exception {
    public:
        virtual const char *what() const throw(){
            return "ERROR. This book wasn't borrowed.";
        }
};

} // namespace library_system
