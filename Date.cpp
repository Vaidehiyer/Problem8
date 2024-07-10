#include "Date.h"

// Constructors
Date::Date() : month(1), day(1), year(1900) {}

Date::Date(int month, int day, int year) : month(month), day(day), year(year) {}

// Getters and Setters
int Date::getMonth() const
{
    return month;
}

void Date::setMonth(int month)
{
    this->month = month;
}

int Date::getDay() const
{
    return day;
}

void Date::setDay(int day)
{
    this->day = day;
}

int Date::getYear() const
{
    return year;
}

void Date::setYear(int year)
{
    this->year = year;
}

// Input and Output Operators
std::istream &operator>>(std::istream &is, Date &date)
{
    is >> date.month >> date.day >> date.year;
    return is;
}

std::ostream &operator<<(std::ostream &os, const Date &date)
{
    os << date.month << " " << date.day << " " << date.year;
    return os;
}
