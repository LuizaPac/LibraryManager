#include "user.h"
#include "date.h"
#include "document.h"
#include "telephone.h"
#include <iostream>
#include <string>

namespace library_system {

User::User(int userId, std::string fName, std::string lName,
           Document documentNumber, Date dateOfBirth, Telephone telephone)
    : userId(userId), firstName(fName), lastName(lName),
      documentNumber(documentNumber), dateOfBirth(dateOfBirth),
      telephone(telephone) {}

std::ostream &operator<<(std::ostream &output, const User &user) {
  output << "User: " << user.getFirstName() + user.getLastName() << std::endl;
  output << "    User ID: " << user.getUserId() << std::endl;
  output << "    Document number: " << user.getDocumentNumber() << std::endl;
  output << "    Day of birth: " << user.getBirthDate() << std::endl;
  output << "    Telephone number: " << user.getTelephone();

  return output;
}

int User::getUserId() const { return userId; }
std::string User::getFirstName() const { return (firstName); }
std::string User::getLastName() const { return (lastName); }
Document User::getDocumentNumber() const { return documentNumber; }
Date User::getBirthDate() const { return dateOfBirth; }
Telephone User::getTelephone() const { return telephone; }

} // namespace library_system
