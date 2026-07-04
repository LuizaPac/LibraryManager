#pragma once

#include <exception>
#include <istream>
#include <ostream>
#include <string>
#include <cctype>
#include <iostream>

namespace Library{

class InvalidDateFormat : public std::exception {
    public:
        virtual const char *what() const throw(){
            return "ERROR: Date should be in the format DD/MM/YYYY.";
        }
};

class InvalidDate : public std::exception {
    public:
        virtual const char *what() const throw(){
            return "ERROR: Day should be in the interval [1, 31] and month in the interval [1, 12]";
        }
};

struct Date {
    int year;
    int month;
    int day;

    Date(std::string dateString){
        //Validation (lenght and /)
        if (dateString.length() != 10 || dateString[2] != '/' || dateString[5] != '/'){
            throw InvalidDateFormat();
        }
        // Check if there is only number in the day, month and year
        for (size_t i = 0; i < 10; i++){
            if (i == 2 || i == 5){
                continue;
            }
            if (!std::isdigit(dateString[i])){
                throw InvalidDateFormat();
            }
        }

        // Transform string into int
        int tempDay = std::stoi(dateString.substr(0, 2));
        int tempMonth = std::stoi(dateString.substr(3, 2));
        int tempYear = std::stoi(dateString.substr(6, 4));

        // Verify if its a valid day and month
        if ((tempDay < 1 || tempDay > 31) || (tempMonth < 1 || tempMonth > 12)){
            throw InvalidDate();
        }

        year = tempYear;
        month = tempMonth;
        day = tempDay;
    }

    friend std::ostream &operator<<(std::ostream &output, const Date &date){
        output << date.day << "/" << date.month << "/" << date.year << std::endl;
        return output;
    }

    friend std::istream &operator>>(std::istream &input, Date &date){
        std::string tempDate;
        input >> tempDate;

        // Same validation as constructor
        if (tempDate.length() != 10 || tempDate[2] != '/' || tempDate[5] != '/'){
            throw InvalidDateFormat();
        }
        // Check if there is only number in the day, month and year
        for (size_t i = 0; i < 10; i++){
            if (i == 2 || i == 5){
                continue;
            }
            if (!std::isdigit(tempDate[i])){
                throw InvalidDateFormat();
            }
        }

        // Transform string into int
        int tempDay = std::stoi(tempDate.substr(0, 2));
        int tempMonth = std::stoi(tempDate.substr(3, 2));
        int tempYear = std::stoi(tempDate.substr(6, 4));

        // Verify if its a valid day and month
        if ((tempDay < 1 || tempDay > 31) || (tempMonth < 1 || tempMonth > 12)){
            throw InvalidDate();
        }

        date.year = tempYear;
        date.month = tempMonth;
        date.day = tempDay;

        return input;
    }
};

}
