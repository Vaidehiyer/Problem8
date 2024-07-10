/**
 * @file PeopleDB.h
 * @author Hakim Abdisalam
 * StartID: oc3378es
 * @brief People Database header file
 * @version 0.1
 * @date 2024-07-07
 * Instructor: Jerome Covington
 * Due date: 07/08/2024
 *
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef PEOPLE_DB_H
#define PEOPLE_DB_H

#include <iostream>
#include <fstream>
#include <string>
#include "BinarySearchTree.h" // BST defined in textbook
#include "People.h"           // User-defined People class

using namespace std;

class PeopleDB
{
private:
    BinarySearchTree<People> db; // BST of type People

public:
    /**
     * @brief Construct a new People DB object from an input file
     *
     * @param filename : Name of the file containing people details
     */
    PeopleDB(const std::string &filename);

    /**
     * @brief Adds a person to the database
     *
     * @param person : Person to add of type People
     * @post Person is added into the BST in in-order style
     */
    void addPerson(const People &person);

    /**
     * @brief Removes a person from the database
     *
     * @param person to remove
     * @return true if person removed successfully; false otherwise
     */
    bool removePerson(const People &person);

    /**
     * @brief Searches a person in the database
     *
     * @param person to search
     * @return true if person found; false otherwise
     */
    bool searchPerson(const People &person);

    /**
     * @brief Displays the contents of the database
     * sorted in ascending order of names
     *
     * @param visit : A pointer to a function visit
     * that prints the output to screen
     */
    void displayInorder(void (*visit)(People &));

    /**
     * @brief Displays the contents of the database
     * in pre-order style
     *
     * @param visit : A pointer to a function visit
     * that prints the output to screen
     */
    void displayPreorder(void (*visit)(People &));

    /**
     * @brief Saves the contents of the database
     * to an external file
     *
     * @param visit : A pointer to a function visit
     * that writes the data to the external file
     */
    void saveDatabase(void (*visit)(People &));
};

#endif // PEOPLE_DB_H
