#include "library.h"
#include "document.h"
#include "date.h"
#include "lending.h"
#include "telephone.h"
#include <string>
#include <vector>
#include <tuple>
#include <pybind11/embed.h>
#include <pybind11/stl.h>

namespace library_system {

Library::Library(const std::string &libraryName) : libraryName(libraryName) {
    // Import sys module from Python
    pybind11::module_ sys = pybind11::module_::import("sys");

    // Add pythonScripts directory to the search path from Python
    sys.attr("path").attr("append")("./pythonFunctions");

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
    auto loanList = bd.attr("loadActiveLoans")(libraryName).cast<std::vector<std::tuple<int, int, std::string>>>();
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

        // Create the date struct
        Date currentDate(std::get<2>(loan));

        // Create the lending object
        if (currentUser != nullptr && currentBook != nullptr){
            lendings.push_back(new Lending(currentUser, currentBook, currentDate));
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

    for (Lending *lending : lendings){
        delete lending;
    }
}

int Library::newUser(std::string name, Document document, Date dateOfBirth , Telephone telephone){
    // Check if there is another user with the same document
    for (const User *user : users){
        if (document == user->getDocumentNumber()){
            throw DuplicatedDocument();
        }
    }

    // Import the script
    pybind11::module_ bd = pybind11::module_::import("createUser");

    // Call createUser function
    int userId = bd.attr("createUser")(libraryName, name, document.number, dateOfBirth.getStringDate(), telephone.telephoneNumber).cast<int>();
    users.push_back(new User(userId, name, document, dateOfBirth, telephone));

    return userId;
}

void Library::userInfo(Document documentNumber){
    // Search for the user with the same document in the users vector
    bool userFound = false;
    for (const User *user : users){
        if (user->getDocumentNumber() == documentNumber){
            userFound = true;
            std::cout << *user << std::endl;
            break;
        }
    }

    if (!userFound){
        std::cout << "There is not any user with the document number " << documentNumber << std::endl;
    }
}

int Library::newBook(std::string title, Date releaseDate, std::string author, std::string genre){
    // Check if there is another book with same title
    for (const Book* book : books){
        if (book->getTitle() == title){
            throw DuplicatedBook();
        }
    }

    // Import the script
    pybind11::module_ bd = pybind11::module_::import("createBook");

    // Call createBook function
    int bookId = bd.attr("createBook")(libraryName, title, releaseDate.getStringDate(), author, genre).cast<int>();
    books.push_back(new Book(bookId, title, releaseDate, author, genre));

    return bookId;
}

void Library::bookInfo(int bookId){
    // Search for the book with same ID in the books vector
    bool bookFound = false;
    for (const Book *book : books){
        if (book->getBookId() == bookId){
            bookFound = true;
            std::cout << *book << std::endl;
            break;
        }
    }

    if (!bookFound){
        std::cout << "There is no book with ID " << bookId << std::endl;
    }
}

}
