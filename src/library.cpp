#include "library.h"
#include "document.h"
#include "date.h"
#include "telephone.h"
#include <string>
#include <vector>
#include <tuple>
#include <pybind11/embed.h>
#include <pybind11/stl.h>

namespace library_system {

Library::Library(std::string libraryName) : libraryName(libraryName) {
    // Import sys module from Python
    pybind11::module_ sys = pybind11::module_::import("sys");

    // Add pythonScripts directory to the search path from Python
    sys.attr("path").attr("append")("./pythonScripts");

    // Import the script
    pybind11::module_ bd = pybind11::module_::import("loadData");

    // Load users
    auto userList = bd.attr("loadUsers")(libraryName).cast<std::vector<std::tuple<int, std::string, std::string, std::string, std::string>>>();
    for (const auto &user : userList) {
        int id = std::get<0>(user);
        std::string name = std::get<1>(user);
        Document document(std::get<2>(user));
        Date dateOfBirth(std::get<3>(user));
        Telephone telephone(std::get<4>(user));
        users.push_back(new User(id, name, document, dateOfBirth, telephone));
    }

    // Load books
    auto bookList = bd.attr("loadBooks")(libraryName).cast<std::vector<std::tuple<int, std::string, std::string, std::string, std::string>>>();
    for (const auto &book : bookList) {
        int id = std::get<0>(book);
        std::string title = std::get<1>(book);
        Date releaseDate(std::get<2>(book));
        std::string author = std::get<3>(book);
        std::string genre = std::get<4>(book);
        books.push_back(new Book(id, title, releaseDate, author, genre));
    }

    // Load loans
    auto loanList = bd.attr("loadActiveLoans")(libraryName).cast<std::vector<std::tuple<int, int>>>();
    for (const auto &loan : loanList){
        User *currentUser = nullptr;
        Book *currentBook = nullptr;

        // Search for the user
        int userId = std::get<0>(loan);
        for (User *user : users){
            if (user->getUserId() == userId){
                currentUser = user;
                break;
            }
        }

        // Search for the book
        int bookId = std::get<1>(loan);
        for (Book *book : books){
            if (book->getBookId() == bookId){
                currentBook = book;
                break;
            }
        }

        // Add the borrowed book in the vector of loan books
        if (currentUser != nullptr && currentBook != nullptr){
            currentUser->insertNewBorrowedBook(currentBook);
        }
    }
}

Library::~Library(){
    // Delete all pointers
    for (User *user : users){
        delete user;
    }

    for (Book *book : books){
        delete book;
    }
}

}
