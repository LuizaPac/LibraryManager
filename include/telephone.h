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

class Telephone {
    public:
        Telephone();

        Telephone(std::string);

        friend std::ostream &operator<<(std::ostream &, const Telephone &);

        friend std::istream &operator>>(std::istream &, Telephone &);

        // Get methods
        std::string getTelephone() const;

    private:
        std::string telephoneNumber;

};

}