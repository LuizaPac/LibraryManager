#include "document.h"
#include "library.h"
#include <algorithm>
#include <csignal>
#include <iostream>
#include <limits>
#include <string>

void clearInputBuffer() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string readString(const std::string &prompt) {
  std::string input;
  std::cout << prompt;
  std::cin >> input;
  clearInputBuffer();
  return input;
}

std::string readLine(const std::string &prompt) {
  std::string input;
  std::cout << prompt;
  std::getline(std::cin >> std::ws, input);
  return input;
}

bool readInt(const std::string &prompt, int &input) {
  std::cout << prompt;

  if (std::cin >> input) {
    clearInputBuffer();
    return true;
  }

  if (!std::cin.eof()) {
    std::cin.clear();
    clearInputBuffer();
  }

  return false;
}

void waitForEnter() {
  std::cout << std::endl << "\nPress Enter to continue...";
  std::cin.get();
}

int main() {
  // Create the library object
  library_system::Library library;
  std::signal(SIGINT, SIG_DFL);

  // Menu loop
  while (true) {
    std::cout << "\033[2J\033[1;1H";
    int option;
    std::cout << "========== Library ==========" << std::endl;
    std::cout << "1 - Create a new user" << std::endl;
    std::cout << "2 - Add a new book to the library" << std::endl;
    std::cout << "3 - Get user information" << std::endl;
    std::cout << "4 - Get book information" << std::endl;
    std::cout << "5 - Land a book" << std::endl;
    std::cout << "6 - Return a book" << std::endl;
    std::cout << "7 - Get book status" << std::endl;
    std::cout << "8 - Print all users" << std::endl;
    std::cout << "9 - Print all books" << std::endl << std::endl;
    std::cout << "0 - Exit" << std::endl << std::endl;

    if (!readInt("Option: ", option)) {
      if (std::cin.eof()) {
        break;
      }
      std::cout << "Select a numeric option" << std::endl;
      waitForEnter();
      continue;
    }

    if (option == 1) {
      try {
        std::string firstName = readLine("First name: ");
        std::string lastName = readLine("Last name: ");
        library_system::Document document(readString("Document: "));
        library_system::Date birthday(readString("Birthday (YYYY/MM/DD): "));
        library_system::Telephone telephone(
            readString("Telephone (XXXXXXXXXXX): "));

        library.newUser(firstName, lastName, document, birthday, telephone);

      } catch (const std::exception &e) {
        std::cout << e.what() << '\n';
      }
    } else if (option == 2) {
      std::string title = readLine("Title: ");

      library_system::Date releaseDate;
      try {
        releaseDate =
            library_system::Date(readString("Release date (YYYY/MM/DD): "));
      } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        waitForEnter();
        continue;
      }

      std::string author = readLine("Author: ");

      int genreId;
      std::vector<const library_system::Genre *> genresVector =
          library.getGenresVector();

      // Sort the vector using std::sort
      std::sort(
          genresVector.begin(), genresVector.end(),
          [](const library_system::Genre *a, const library_system::Genre *b) {
            return a->getGenreId() < b->getGenreId();
          });
      for (const library_system::Genre *genre : genresVector) {
        std::cout << genre->getGenreId() << " - " << genre->getGenre() << "\n";
      }
      if (!readInt("Genre ID: ", genreId)) {
        if (std::cin.eof()) {
          break;
        }
        std::cout << "Genre ID must be numeric" << std::endl;
        waitForEnter();
        continue;
      }

      try {
        library.newBook(title, releaseDate, author, genreId);
      } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
      }
    } else if (option == 3) {
      library_system::Document document;
      std::cout << "Document (XXXXXXXXXXX): ";
      try {
        std::cin >> document;
        clearInputBuffer();
        library.userInfo(document);
      } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        waitForEnter();
        continue;
      }
    } else if (option == 4) {
      int bookId;
      if (!readInt("Book ID: ", bookId)) {
        if (std::cin.eof()) {
          break;
        }
        std::cout << "Book ID must be numeric" << std::endl;
        waitForEnter();
        continue;
      }

      try {
        library.bookInfo(bookId);
      } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        waitForEnter();
        continue;
      }
    } else if (option == 5) {
      library_system::Document userDocument;
      std::cout << "Document (XXXXXXXXXXX): ";
      try {
        std::cin >> userDocument;
        clearInputBuffer();
      } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        waitForEnter();
        continue;
      }

      int bookId;
      if (!readInt("Book ID: ", bookId)) {
        if (std::cin.eof()) {
          break;
        }
        std::cout << "Book ID must be numeric" << std::endl;
        waitForEnter();
        continue;
      }

      try {
        library.landBook(userDocument, bookId);
      } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        waitForEnter();
        continue;
      }

    } else if (option == 6) {
      library_system::Document userDocument;
      std::cout << "Document (XXXXXXXXXXX): ";
      try {
        std::cin >> userDocument;
        clearInputBuffer();
      } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        waitForEnter();
        continue;
      }

      int bookId;
      if (!readInt("Book ID: ", bookId)) {
        if (std::cin.eof()) {
          break;
        }
        std::cout << "Book ID must be numeric" << std::endl;
        waitForEnter();
        continue;
      }

      try {
        library.returnBook(userDocument, bookId);
      } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        waitForEnter();
        continue;
      }
    } else if (option == 7) {
      int bookId;
      if (!readInt("Book ID: ", bookId)) {
        if (std::cin.eof()) {
          break;
        }
        std::cout << "Book ID must be numeric" << std::endl;
        waitForEnter();
        continue;
      }

      library.bookStatus(bookId);
    } else if (option == 8) {
      library.printUsers();
    } else if (option == 9) {
      library.printBooks();
    } else if (option == 0) {
      break;
    } else {
      std::cout << "Select a valid option" << std::endl;
    }
    waitForEnter();
  }
}
