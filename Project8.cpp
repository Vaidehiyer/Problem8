/**
 * @file Project8.cpp
 * @author Hakim Abdisalam
 * StartID: oc3378es
 * @brief A program that maintains a database containing person’s name and birthday.
 * You should be able to enter, remove, modify, or search for this database.
 * @version 0.1
 * @date 2024-07-07
 * Instructor: Jerome Covington
 * Due date: 07/08/2024
 *
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include "PeopleDB.h"

using namespace std;

// Global variable for the output file stream
ofstream fsOut("SCSU_DB2.txt", ios_base::app);

// This operation is applied at each node to display data to the screen
void toScreen(People &p)
{
    cout << p << endl;
}

// This operation is applied at each node to write data to a file
void toFile(People &p)
{
    fsOut << p << endl;
}

/**
 * @brief Displays the menu containing 7 user choices
 *
 */
void displayMenu()
{
    cout << "\nPlease enter your option" << endl;
    cout << "1. Add a new person" << endl;
    cout << "2. Remove a person" << endl;
    cout << "3. Modify the database" << endl;
    cout << "4. Search for a person in the database" << endl;
    cout << "5. Display the database" << endl;
    cout << "6. Display the database sorted by names" << endl;
    cout << "7. Quit and save the database to a file" << endl;
    cout << "-->";
}

int main()
{

    // Display header and ask for input filename
    string filename;
    cout << "Welcome to the People database system." << endl;
    cout << "Please enter the file that contains the initial people list: ";
    cin >> filename;

    // Load the database from the file and display it screen
    PeopleDB database(filename);
    cout << "The initial database built from the input file is displayed by its original order:" << endl;
    database.displayPreorder(toScreen);

    int choice; // To store user choice

    // Start a loop to repeatedly ask for inputs
    do
    {
        displayMenu();
        cin >> choice;

        // Switch actions based on choice
        switch (choice)
        {

        // Add a new person to db
        case 1:
        {
            char cont = 'y';

            // Add person repeatedly until user wants to quit
            while (cont == 'y' || cont == 'Y')
            {
                People p;
                cout << "To add, enter name and birthday (month day year):" << endl;
                cin >> p;
                database.addPerson(p);
                cout << "Add another one? ";
                cin >> cont;
            }
            break;
        }

        // Remove a person from db
        case 2:
        {
            char cont = 'y';
            while (cont == 'y' || cont == 'Y')
            {

                // Get the name and birthday
                string name;
                Date birthday;
                cout << "To remove, enter name and birthday:" << endl;
                cin >> name >> birthday;

                // Try to remove, otherwise show error
                if (!database.removePerson(People(name, birthday)))
                {
                    cout << "Cannot find this person." << endl;
                }
                else
                {
                    cout << "This person has been removed." << endl;
                }
                cout << "Remove another one? ";
                cin >> cont;
            }
            break;
        }

        // Modify details of a person
        case 3:
        {
            char cont = 'y';
            while (cont == 'y' || cont == 'Y')
            {

                // Get details from user
                string name;
                Date birthday;
                cout << "To modify, enter name and birthday:" << endl;
                cin >> name >> birthday;

                // Try to remove the old details of person from DB
                if (database.removePerson(People(name, birthday)))
                {
                    cout << "Found this person in the database. This person's data has been removed." << endl;
                    People newPerson;

                    // Add new info to the db
                    cout << "Enter this person's new information: name and birthday (month day year):" << endl;
                    cin >> newPerson;
                    database.addPerson(newPerson);
                    cout << "The database has been modified." << endl;
                }
                else
                {
                    cout << "Cannot find this person." << endl;
                }
                cout << "Continue to modify? ";
                cin >> cont;
            }
            break;
        }

        // Search for a person
        case 4:
        {
            char cont = 'y';
            while (cont == 'y' || cont == 'Y')
            {

                // Get details to search
                string name;
                Date birthday;
                cout << "To search, enter name and birthday:" << endl;
                cin >> name >> birthday;

                // If person found in DB, person found message
                if (database.searchPerson(People(name, birthday)))
                {
                    cout << "Found the person in the database:" << endl;
                    cout << People(name, birthday) << endl;
                }
                else
                {
                    cout << "Cannot find." << endl;
                }
                cout << "Continue another search? ";
                cin >> cont;
            }
            break;
        }

        // Display details
        case 5:
        {
            cout << endl;
            database.displayPreorder(toScreen);
            break;
        }

        // Display details in sorted manner
        case 6:
        {
            cout << endl;
            database.displayInorder(toScreen);
            break;
        }

        // Updated db saved to external file before quitting
        case 7:
        {
            cout << endl;
            database.saveDatabase(toFile);
            cout << "The updated database has been saved to \"SCSU_DB2.txt\"." << endl;
            break;
        }

        // Invalid option
        default:
        {
            cout << "Invalid option. Please try again." << endl;
            break;
        }
        }
    } while (choice != 7);

    fsOut.close();
    cout << "Bye!" << endl;

    return 0;
}
