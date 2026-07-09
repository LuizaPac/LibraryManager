#include "document.h"

namespace library_system {

Document::Document() : number(""){}

Document::Document(std::string documentNumber){
    // Validation
    if (documentNumber.length() != 11){
        throw InvalidDocument();
    }
    this->number = documentNumber;
}

bool Document::operator==(const Document &otherDocument) const{
    return this->number == otherDocument.number;
}

std::ostream &operator<<(std::ostream &output, const Document &document){
    output << document.number.substr(0, 3) 
        << "." << document.number.substr(3, 3) 
        << "." << document.number.substr(6, 3) 
        << "-" << document.number.substr(9, 2);
    return output;
    }

std::istream &operator>>(std::istream &input, Document &document){
    std::string tempNumber;
    input >> tempNumber;

    document = Document(tempNumber);

    return input;
}

std::string Document::getNumber() const { return number; }

};