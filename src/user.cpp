#include "user.h"
#include "document.h"
#include "date.h"
#include "telephone.h"
#include <string>
#include <iostream>

namespace library_system {

User::User(int userId, std::string name, Document documentNumber, Date dateOfBirth, Telephone telephone) 
    : userId(userId), name(name), documentNumber(documentNumber), dateOfBirth(dateOfBirth), telephone(telephone) {}

std::ostream &operator<<(std::ostream &output, const User &user){
    output << "User: " << user.getName() << std::endl;
    output << "    User ID: " << user.getUserId() << std::endl;
    output << "    Document number: " << user.getDocumentNumber() << std::endl;
    output << "    Day of birth: " << user.getBirthDate() << std::endl;
    output << "    Telephone number: " << user.getTelephone();

    return output;
}

int User::getUserId() const { return userId; }
std::string User::getName() const { return name; }
Document User::getDocumentNumber() const { return documentNumber; }
Date User::getBirthDate() const { return dateOfBirth; }
Telephone User::getTelephone() const { return telephone; }

}
