#include "book.h"
#include "date.h"
#include <string>
#include <iostream>

namespace library_system {

Book::Book(int bookId, std::string title, Date releaseDate, std::string author, std::string genre)
    : bookId(bookId), title(title), releaseDate(releaseDate), author(author), genre(genre){}

std::ostream &operator<<(std::ostream &output, const Book &book){
    output << "Title: " << book.getTitle() << std::endl
        << "    Book ID: " << book.getBookId() << std::endl
        << "    Release date: " << book.getReleaseDate() << std::endl
        << "    Author: " << book.getAuthor() << std::endl
        << "    Genre: " << book.getGenre();

    return output;
}

// Get methods
int Book::getBookId() const { return bookId; }
std::string Book::getTitle() const { return title; }
Date Book::getReleaseDate() const { return releaseDate; }
std::string Book::getAuthor() const { return author; }
std::string Book::getGenre() const {return genre; }

}
