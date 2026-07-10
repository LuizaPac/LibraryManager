#pragma once

#include <exception>
#include <istream>
#include <ostream>
#include <string>
#include <cctype>
#include <iostream>

namespace library_system {

class InvalidDateFormat : public std::exception {
    public:
        virtual const char *what() const throw(){
            return "ERROR: Date should be in the format YYYY/MM/DD.";
        }
};

class InvalidDate : public std::exception {
    public:
        virtual const char *what() const throw(){
            return "ERROR: Day should be in the interval [1, 31] and month in the interval [1, 12]";
        }
};

class Date{
    public:
        Date();

        Date(std::string);

        std::string getStringDate() const;

        friend std::ostream &operator<<(std::ostream &, const Date &);

        friend std::istream &operator>>(std::istream &, Date &);

        // Get methods
        int getYear() const;
        int getMonth() const;
        int getDay() const;

    private:
        int year;
        int month;
        int day;
};

} // namespace library_system
