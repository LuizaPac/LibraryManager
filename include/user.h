#pragma once

#include "document.h"
#include "date.h"
#include "telephone.h"
#include <ostream>
#include <string>
#include <iostream>

namespace library_system {

// Class book just to say it exists
class Book;

class User{
    public:
        User(int, std::string, Document, Date, Telephone);

        friend std::ostream &operator<<(std::ostream &, const User &);

        // Get methods
        int getUserId() const;
        std::string getName() const;
        Document getDocumentNumber() const;
        Date getBirthDate() const;
        Telephone getTelephone() const;

    private:
        int userId;
        std::string name;
        Document documentNumber;
        Date dateOfBirth;
        Telephone telephone;
};

} // namespace library_system
