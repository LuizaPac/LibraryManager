#pragma once

#include <string>
#include <iostream>

namespace library_system {

class InvalidTelephone : public std::exception {
    public:
        virtual const char *what() const throw(){
            return "ERROR: Telephone should be in the format XXXXXXXXXXX";
        }
};

struct Telephone{
    std::string telephoneNumber;

    // Standart constructor
    Telephone(){}

    Telephone(std::string telephoneNumber){
        // Validation size
        if (telephoneNumber.size() != 11){
            throw InvalidTelephone();
        }

        this->telephoneNumber = telephoneNumber;
    }

    friend std::ostream &operator<<(std::ostream &output, const Telephone &telephone){
        output << "(" 
            << telephone.telephoneNumber.substr(0, 2)
            << ")"
            << telephone.telephoneNumber.substr(2, 5)
            << "-"
            << telephone.telephoneNumber.substr(7, 4);

        return output;
    }

    friend std::istream &operator>>(std::istream &input, Telephone &telephone){
        std::string tempTelephone;

        input >> tempTelephone;

        // Validation (same as constructor)
        if (tempTelephone.length() != 11){
            throw InvalidTelephone();
        }

        telephone.telephoneNumber = tempTelephone;

        return input;
    }
};

} // namespace library_system
