/**
 * @file People.h
 * @author Hakim Abdisalam
 * StartID: oc3378es
 * @brief People header file
 * @version 0.1
 * @date 2024-07-07
 * Instructor: Jerome Covington
 * Due date: 07/08/2024
 *
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef PEOPLE_H
#define PEOPLE_H

#include <iostream>
#include <string>
#include "Date.h"

class People
{
private:
    std::string name;        // Name of the person
    Date birthday;           // Birth date of the person

public:
    // Constructors
    People();
    People(const std::string &name, const Date &birthday);

    // Getters and Setters
    std::string getName() const;
    void setName(const std::string &name);

    Date getBirthday() const;
    void setBirthday(const Date &birthday);

    // Friend Functions for Input and Output
    friend std::istream &operator>>(std::istream &is, People &person);
    friend std::ostream &operator<<(std::ostream &os, const People &person);

    // Comparison Operators
    bool operator==(const People &other) const;
    bool operator<(const People &other) const;
    bool operator>(const People &other) const;
};

#endif // PEOPLE_H
