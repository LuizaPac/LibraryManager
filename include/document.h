#pragma once

#include <string>
#include <iostream>
#include <exception>

namespace library_system {

class InvalidDocument : public std::exception {
    public:
        virtual const char *what() const throw(){
            return "ERROR: Document should be in the format XXXXXXXXXXX.";
        }
};

class DuplicatedDocument : public std::exception {
    public:
        virtual const char *what() const throw(){
            return "ERROR. There is another user with the same document.";
        }
};


struct Document{
    std::string number;

    // Standart constructor
    Document(){}

    Document(std::string documentNumber){
        // Validation
        if (documentNumber.length() != 11){
            throw InvalidDocument();
        }
        this->number = documentNumber;
    }

    bool operator==(const Document &otherDocument) const{
        return this->number == otherDocument.number;
    }

    friend std::ostream &operator<<(std::ostream &output, const Document &document){
        output << document.number.substr(0, 3) 
            << "." << document.number.substr(3, 3) 
            << "." << document.number.substr(6, 3) 
            << "-" << document.number.substr(9, 2);
        return output;
    }

    friend std::istream &operator>>(std::istream &input, Document &document){
        std::string tempNumber;

        input >> tempNumber;

        // Validation (same as constructor)
        if (tempNumber.length() != 11){
            throw InvalidDocument();
        }

        document.number = tempNumber;

        return input;
    }
};

} // namespace library_system
