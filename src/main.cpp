#include "document.h"
#include "library.h"
#include <iostream>
#include <string>

// TODO: FIX
// 1. nomes: getline em vez de cin
// 2. limpar buffer
// 5. Mensagem de confirmação com pós operação bem sucessida
// 6. Print do nome do usuário com espaço
// 7. Imprimir tabela de genero
// 8. Padronizar o nome do autor (maiuscula e minuscula para que a entrada não
// seja case sensitive)
// 9. fix: digitar algo não numerico no book_id da bug

int main() {
  // Create the library object
  library_system::Library library;

  // Menu loop
  while (true) {
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

    std::cout << "Option: ";
    std::cin >> option;

    if (option == 1) {
      try {
        std::string firstName, lastName;
        library_system::Document document;
        library_system::Date birthday;
        library_system::Telephone telephone;

        std::cout << "First name: ";
        std::cin >> firstName;

        std::cout << "Last name: ";
        std::cin >> lastName;

        std::cout << "Document: ";
        std::cin >> document;

        std::cout << "Birthday (YYYY/MM/DD): ";
        std::cin >> birthday;

        std::cout << "Telephone: ";
        std::cin >> telephone;

        library.newUser(firstName, lastName, document, birthday, telephone);
      } catch (const std::exception &e) {
        std::cout << e.what() << '\n';
      }
    } else if (option == 2) {
      std::string title;
      std::cout << "Title: ";
      std::cin >> title;

      library_system::Date releaseDate;
      std::cout << "Release date (YYYY/MM/DD): ";
      try {
        std::cin >> releaseDate;
      } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        continue;
      }

      std::string author;
      std::cout << "Author: ";
      std::cin >> author;

      std::string genre;
      std::cout << "Genre: ";
      std::cin >> genre;

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
        library.userInfo(document);
      } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        continue;
      }
    } else if (option == 4) {
      int bookId;
      std::cout << "Book ID: ";
      std::cin >> bookId;

      try {
        library.bookInfo(bookId);
      } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        continue;
      }
    } else if (option == 5) {
      library_system::Document userDocument;
      std::cout << "Document (XXXXXXXXXXX): ";
      try {
        std::cin >> userDocument;
      } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        continue;
      }

      int bookId;
      std::cout << "Book ID: ";
      std::cin >> bookId;

      try {
        library.landBook(userDocument, bookId);
      } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        continue;
      }

    } else if (option == 6) {
      library_system::Document userDocument;
      std::cout << "Document (XXXXXXXXXXX): ";
      try {
        std::cin >> userDocument;
      } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        continue;
      }

      int bookId;
      std::cout << "Book ID: ";
      std::cin >> bookId;

      try {
        library.returnBook(userDocument, bookId);
      } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
        continue;
      }
    } else if (option == 7) {
      int bookId;
      std::cout << "Book ID: ";
      std::cin >> bookId;

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
  }
}
