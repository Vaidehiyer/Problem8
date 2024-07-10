#include "People.h"

// Constructors
People::People() : name("Unknown"), birthday() {}

People::People(const std::string &name, const Date &birthday) : name(name), birthday(birthday) {}

// Getters and Setters
std::string People::getName() const
{
    return name;
}

void People::setName(const std::string &name)
{
    this->name = name;
}

Date People::getBirthday() const
{
    return birthday;
}

void People::setBirthday(const Date &birthday)
{
    this->birthday = birthday;
}

// Input and Output Operators
std::istream& operator>>(std::istream& is, People& person) {
    is >> person.name >> person.birthday;
    return is;
}

std::ostream& operator<<(std::ostream& os, const People& person) {
    os << person.name << " " << person.birthday;
    return os;
}

// Comparison Operators
bool People::operator==(const People &other) const
{
    return name == other.name;
}

bool People::operator<(const People &other) const
{
    return name < other.name;
}

bool People::operator>(const People &other) const
{
    return name > other.name;
}
