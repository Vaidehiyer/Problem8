#include "PeopleDB.h"

// Constructor that initializes the database from a file
PeopleDB::PeopleDB(const string &filename)
{
    ifstream inputFile(filename);
    if (!inputFile)
    {
        cerr << "Error opening file" << endl;
        return;
    }

    People person;
    while (inputFile >> person)
    {
        db.add(person);
    }
    cout << db.getHeight() << endl;
    inputFile.close();
}

// Add a person to the database
void PeopleDB::addPerson(const People &person)
{
    db.add(person);
}

// Remove a person from the database
bool PeopleDB::removePerson(const People &person)
{
    return db.remove(person);
}

// Search for a person in the database
bool PeopleDB::searchPerson(const People &person)
{
    return db.contains(person);
}

// Display the database using preorder traversal
void PeopleDB::displayPreorder(void (*visit)(People &))
{
    db.preorderTraverse(visit);
}

// Display the database in sorted order (inorder traversal)
void PeopleDB::displayInorder(void (*visit)(People &))
{
    db.inorderTraverse(visit);
}

void PeopleDB::saveDatabase(void (*visit)(People &))
{
    db.preorderTraverse(visit);
}
