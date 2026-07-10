#include "document.h"
#include "library.h"
#include <iostream>
#include <limits>
#include <string>

// TODO: FIX
// 3. print todos os livros e todos os usuários
//  obs: livro precisa dar get no nome do autor e genero
// 6. Print do nome do usuário com espaço
// 7. Imprimir tabela de genero
// 8. Padronizar o nome do autor (maiuscula e minuscula para que a entrada não
// seja case sensitive)
// 9. fix: digitar algo não numerico no book_id da bug

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

void waitForEnter() {
  std::cout << std::endl << "\nPress Enter to continue...";
  std::cin.get();
}

int main() {
  // Create the library object
  library_system::Library library;

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
    std::cout << "7 - Get book status" << std::endl << std::endl;
    std::cout << "0 - Exit" << std::endl << std::endl;

    std::cout << "Option: ";
    std::cin >> option;
    clearInputBuffer();

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
      std::string genre = readLine("Genre: ");

      try {
        library.newBook(title, releaseDate, author, genre);
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
      std::cout << "Book ID: ";
      std::cin >> bookId;
      clearInputBuffer();

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
      std::cout << "Book ID: ";
      std::cin >> bookId;
      clearInputBuffer();

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
      std::cout << "Book ID: ";
      std::cin >> bookId;
      clearInputBuffer();

      try {
        library.returnBook(userDocument, bookId);
      } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        waitForEnter();
        continue;
      }
    } else if (option == 7) {
      int bookId;
      std::cout << "Book ID: ";
      std::cin >> bookId;
      clearInputBuffer();

      library.bookStatus(bookId);
    } else if (option == 0) {
      break;
    } else {
      std::cout << "Select a valid option" << std::endl;
    }
    waitForEnter();
  }
}
