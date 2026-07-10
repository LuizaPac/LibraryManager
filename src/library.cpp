#include "library.h"
#include "book.h"
#include "date.h"
#include "document.h"
#include "genre.h"
#include "lending.h"
#include "telephone.h"
#include <ctime>
#include <pybind11/embed.h>
#include <pybind11/stl.h>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

// BIG TODO:: Replace c_outs with return methods in order to fit multiple
// frontend interfaces

namespace library_system {
Library::Library() {
  namespace py = pybind11;

  // Import sys module from Python
  py::module_ sys = py::module_::import("sys");

  // Add pythonFunctions directory to the search path
  sys.attr("path").attr("append")("./pythonFunctions");

  // Import scripts and save as variables from library class
  authorRepository =
      py::module_::import("author_repository").attr("AuthorRepository")();
  bookGenreRepository = py::module_::import("book_genre_repository")
                            .attr("BookGenreRepository")();
  documentTypeRepository = py::module_::import("document_type_repository")
                               .attr("DocumentTypeRepository")();
  userRepository =
      py::module_::import("user_repository").attr("UserRepository")();
  bookRepository =
      py::module_::import("book_repository").attr("BookRepository")();
  lendingRepository =
      py::module_::import("lending_repository").attr("LendingRepository")();

  // Load database to Library
  // author : vector of (id, str)
  auto authorList = authorRepository.attr("get_all")()
                        .cast<std::vector<std::tuple<int, std::string>>>();
  for (const auto &author : authorList) {
    int id = std::get<0>(author);
    std::string name = std::get<1>(author);

    authors.push_back(new Author(id, name));
  }

  // genre : vector of (id, str)
  auto genreList = bookGenreRepository.attr("get_all")()
                       .cast<std::vector<std::tuple<int, std::string>>>();
  for (const auto &genre : genreList) {
    int id = std::get<0>(genre);
    std::string name = std::get<1>(genre);

    genres.push_back(new Genre(id, name));
  }

  // user : vector of (int, str, str, str, str, str)
  auto userList =
      userRepository.attr("get_all")()
          .cast<
              std::vector<std::tuple<int, std::string, std::string, std::string,
                                     std::string, std::string>>>();
  for (const auto &user : userList) {
    int id = std::get<0>(user);
    std::string fName = std::get<1>(user);
    std::string lName = std::get<2>(user);
    Document document(std::get<3>(user));
    Telephone telephone(std::get<5>(user));
    Date dateOfBirth(std::get<4>(user));

    users.push_back(new User(id, fName, lName, document, dateOfBirth,
                             Telephone(telephone)));
  }

  // book : vector of (id, title, release_date, author_id, genre_id)
  auto bookList =
      bookRepository.attr("get_all")()
          .cast<std::vector<
              std::tuple<int, std::string, std::string, int, int>>>();
  for (const auto &book : bookList) {
    int id = std::get<0>(book);
    std::string title = std::get<1>(book);
    Date releaseDate(normalizeDateString(std::get<2>(book)));
    Author *author = findAuthorById(std::get<3>(book));
    Genre *genre = findGenreById(std::get<4>(book));

    if (author != nullptr && genre != nullptr) {
      books.push_back(new Book(id, title, releaseDate, author, genre));
    }
  }

  // Lending : only active lendings, where return_date is NULL.
  for (py::handle rowHandle : lendingRepository.attr("get_active")()) {
    py::tuple loan = rowHandle.cast<py::tuple>();
    User *currentUser = nullptr;
    Book *currentBook = nullptr;

    int lendingId = loan[0].cast<int>();
    int userId = loan[1].cast<int>();
    int bookId = loan[2].cast<int>();

    for (User *user : users) {
      if (user->getUserId() == userId) {
        currentUser = user;
        break;
      }
    }

    for (Book *book : books) {
      if (book->getBookId() == bookId) {
        currentBook = book;
        break;
      }
    }

    Date lendingDate(normalizeDateString(loan[3].cast<std::string>()));

    if (currentUser != nullptr && currentBook != nullptr) {
      lendings.push_back(new Lending(lendingId, currentUser, currentBook,
                                     lendingDate);
    }
  }
}

Library::~Library() {
  // Delete all pointers
  for (User *user : users) {
    delete user;
  }

  for (Book *book : books) {
    delete book;
  }

  for (Lending *lending : lendings) {
    delete lending;
  }

  for (Author *author : authors) {
    delete author;
  }

  for (Genre *genre : genres) {
    delete genre;
  }
}

int Library::newUser(std::string fname, std::string lname, Document document,
                     Date dateOfBirth, Telephone telephone) {
  for (const User *user : users) {
    if (document == user->getDocumentNumber()) {
      throw DuplicatedDocument();
    }
  }

  int userId =
      userRepository
          .attr("create")(fname, lname, telephone.getTelephone(),
                          dateOfBirth.getStringDate(), document.getNumber())
          .cast<int>();

  users.push_back(
      new User(userId, fname, lname, document, dateOfBirth, telephone));

  return userId;
}

void Library::userInfo(Document documentNumber) {
  // Search for the user with the same document in the users vector
  bool userFound = false;
  for (const User *user : users) {
    if (user->getDocumentNumber() == documentNumber) {
      userFound = true;
      std::cout << *user << std::endl;
      break;
    }
  }

  if (!userFound) {
    std::cout << "There is not any user with the document number "
              << documentNumber << std::endl;
  }
}

// TODO: Find author id before pushig (let the user chose the author)
int Library::newBook(std::string title, Date releaseDate, std::string author,
                     std::string genre) {
  for (const Book *book : books) {
    if (book->getTitle() == title) {
      throw DuplicatedBook();
    }
  }

  pybind11::tuple authorRow =
      authorRepository.attr("get_or_create")(author).cast<pybind11::tuple>();
  int authorId = authorRow[0].cast<int>();
  Author *bookAuthor = findAuthorById(authorId);
  if (bookAuthor == nullptr) {
    bookAuthor = new Author(authorId, authorRow[1].cast<std::string>());
    authors.push_back(bookAuthor);
  }

  Genre *bookGenre = findGenreByName(genre);
  if (bookGenre == nullptr) {
    throw std::runtime_error("ERROR. This book genre doesn't exist.");
  }

  int bookId = bookRepository
                   .attr("create")(title, releaseDate.getStringDate(), authorId,
                                   bookGenre->getGenreId())
                   .cast<int>();

  books.push_back(new Book(bookId, title, releaseDate, bookAuthor, bookGenre));

  return bookId;
}

void Library::bookInfo(int bookId) {
  // Search for the book with same ID in the books vector
  bool bookFound = false;
  for (const Book *book : books) {
    if (book->getBookId() == bookId) {
      bookFound = true;
      std::cout << *book << std::endl;
      break;
    }
  }

  if (!bookFound) {
    std::cout << "There is no book with ID " << bookId << std::endl;
  }
}

int Library::landBook(Document userDocument, int bookId) {
  for (const Lending *lending : lendings) {
    if (lending->getBorrowedBook()->getBookId() == bookId) {
      throw BookAlreadyBorrowed();
    }
  }

  for (User *user : users) {
    if (user->getDocumentNumber() == userDocument) {
      for (Book *book : books) {
        if (book->getBookId() == bookId) {
          std::string currentDate = dateStringFromNow();
          Date currentDay(currentDate);

          int lendingId =
              lendingRepository
                  .attr("create")(user->getUserId(), book->getBookId(),
                                  currentDate, dateStringFromNow(14))
                  .cast<int>();

          lendings.push_back(new Lending(lendingId, user, book, currentDay));

          return lendingId;
        }
      }

      throw BookNotFound();
    }
  }
  throw UserNotFound();
}

void Library::returnBook(Document userDocument, int bookId) {
  // Search for the book in the lending vector
  for (size_t i = 0; i < lendings.size(); i++) {
    if (lendings[i]->getBorrowedBook()->getBookId() == bookId) {
      // Check if is the same user
      if (lendings[i]->getBorrower()->getDocumentNumber() == userDocument) {
        std::string returnDate = dateStringFromNow();
        bool success =
            lendingRepository
                .attr("check_in_book")(
                    lendings[i]->getBorrowedBook()->getBookId(), returnDate)
                .cast<bool>();

        if (success) {
          delete lendings[i];
          lendings.erase(lendings.begin() + i);
          return;
        } else {
          throw CheckInFailed();
        }
      } else {
        throw WrongUser();
      }
    }
  }
  throw BookWasNotBorrowed();
}

// TODO: check date of every book instead of just checking just loan object
void Library::bookStatus(int bookId) {
  // Search for the book in the lendings vector
  for (const Lending *lending : lendings) {
    if (lending->getBorrowedBook()->getBookId() == bookId) {
      std::cout << *(lending->getBorrowedBook()) << std::endl
                << "    Status: Borrowed" << std::endl
                << std::endl
                << "Borrower:" << std::endl
                << *(lending->getBorrower()) << std::endl
                << std::endl;

      return;
    }
  }

  // If doesn't find in lendings vector, check in the books vector
  for (const Book *book : books) {
    if (book->getBookId() == bookId) {
      std::cout << *book << std::endl
                << "    Status: Available for loan" << std::endl
                << std::endl;

      return;
    }
  }

  throw BookNotFound();
}

std::string Library::dateStringFromNow(int daysFromNow) const {
  std::time_t targetTime = std::time(nullptr) + (daysFromNow * 24 * 60 * 60);
  std::tm *targetLocalTime = std::localtime(&targetTime);
  char buffer[11];
  std::strftime(buffer, sizeof(buffer), "%Y/%m/%d", targetLocalTime);
  return std::string(buffer);
}

std::string Library::normalizeDateString(std::string dateString) const {
  for (char &character : dateString) {
    if (character == '-') {
      character = '/';
    }
  }
  return dateString;
}

Author *Library::findAuthorById(int authorId) const {
  for (Author *author : authors) {
    if (author->get_id() == authorId) {
      return author;
    }
  }
  return nullptr;
}

Genre *Library::findGenreById(int genreId) const {
  for (Genre *genre : genres) {
    if (genre->getGenreId() == genreId) {
      return genre;
    }
  }
  return nullptr;
}

Genre *Library::findGenreByName(const std::string &genreName) const {
  for (Genre *genre : genres) {
    if (genre->getGenre() == genreName) {
      return genre;
    }
  }
  return nullptr;
}

} // namespace library_system
