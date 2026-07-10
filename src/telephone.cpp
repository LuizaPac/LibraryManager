#include "telephone.h"

namespace library_system {

Telephone::Telephone() : telephoneNumber("") {}

Telephone::Telephone(std::string telephoneNumber){
    // Validation size
    if (telephoneNumber.size() != 11){
        throw InvalidTelephone();
    }

    // Validation digits
    for (char c : telephoneNumber) {
        if (!std::isdigit(c)) {
            throw InvalidTelephone();
        }
    }

    this->telephoneNumber = telephoneNumber;
}

std::ostream &operator<<(std::ostream &output, const Telephone &telephone){
    output << "(" 
        << telephone.telephoneNumber.substr(0, 2)
        << ")"
        << telephone.telephoneNumber.substr(2, 5)
        << "-"
        << telephone.telephoneNumber.substr(7, 4);

    return output;
}

std::istream &operator>>(std::istream &input, Telephone &telephone){
    std::string tempTelephone;
    input >> tempTelephone;

    telephone = Telephone(tempTelephone);

    return input;
}

std::string Telephone::getTelephone() const { return telephoneNumber; }

}