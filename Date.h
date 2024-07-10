/**
 * @file Date.h
 * @author Hakim Abdisalam
 * StartID: oc3378es
 * @brief Date header file
 * @version 0.1
 * @date 2024-07-07
 * Instructor: Jerome Covington
 * Due date: 07/08/2024
 *
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef DATE_H
#define DATE_H

#include <iostream>

class Date
{
private:
    int month;        // Month part of the date
    int day;          // Day part of the date
    int year;         // Year part of the date

public:
    // Constructors
    Date();
    Date(int month, int day, int year);

    // Getters and Setters
    int getMonth() const;
    void setMonth(int month);

    int getDay() const;
    void setDay(int day);

    int getYear() const;
    void setYear(int year);

    // Friend Functions for Input and Output
    friend std::istream &operator>>(std::istream &is, Date &date);
    friend std::ostream &operator<<(std::ostream &os, const Date &date);
};

#endif // DATE_H
