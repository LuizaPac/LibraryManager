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

class Document {
    public:
        Document();

        Document(std::string);

        bool operator==(const Document &) const;

        friend std::ostream &operator<<(std::ostream &, const Document &);

        friend std::istream &operator>>(std::istream &, Document &);

        std::string getNumber() const;

    private:
        std::string number;
};

} // namespace library_system
