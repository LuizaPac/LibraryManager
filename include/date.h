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

struct Date {
    int year;
    int month;
    int day;

    // Standart constructor
    Date(){}

    Date(std::string dateString){
        //Validation (lenght and /)
        if (dateString.length() != 10 || dateString[4] != '/' || dateString[7] != '/'){
            throw InvalidDateFormat();
        }
        // Check if there is only number in the day, month and year
        for (size_t i = 0; i < 10; i++){
            if (i == 4 || i == 7){
                continue;
            }
            if (!std::isdigit(dateString[i])){
                throw InvalidDateFormat();
            }
        }

        // Transform string into int
        int tempYear = std::stoi(dateString.substr(0, 4));
        int tempMonth = std::stoi(dateString.substr(5, 2));
        int tempDay = std::stoi(dateString.substr(8, 2));

        // Verify if its a valid day and month
        if ((tempDay < 1 || tempDay > 31) || (tempMonth < 1 || tempMonth > 12)){
            throw InvalidDate();
        }

        year = tempYear;
        month = tempMonth;
        day = tempDay;
    }

    std::string getStringDate() const{
        std::string yearStr = std::to_string(this->year);
        std::string monthStr = (this->month < 10) ? "0" + std::to_string(this->month) : std::to_string(this->month);
        std::string dayStr = (this->day < 10) ? "0" + std::to_string(this->day) : std::to_string(this->day);
        
        return yearStr + "/" + monthStr + "/" + dayStr;
    }

    friend std::ostream &operator<<(std::ostream &output, const Date &date){
        output << date.getStringDate();

        return output;
    }

    friend std::istream &operator>>(std::istream &input, Date &date){
        std::string tempDate;
        input >> tempDate;

        // Same validation as constructor
        if (tempDate.length() != 10 || tempDate[4] != '/' || tempDate[7] != '/'){
            throw InvalidDateFormat();
        }
        // Check if there is only number in the day, month and year
        for (size_t i = 0; i < 10; i++){
            if (i == 4 || i == 7){
                continue;
            }
            if (!std::isdigit(tempDate[i])){
                throw InvalidDateFormat();
            }
        }

        // Transform string into int
        int tempYear = std::stoi(tempDate.substr(0, 4));
        int tempMonth = std::stoi(tempDate.substr(5, 2));
        int tempDay = std::stoi(tempDate.substr(8, 2));

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

} // namespace library_system
