/* Copyright Navid Mafi Ranji
This source code is provided only for reference purposes. This is not a public domain source code.
All rights reserved.
*/

#include <stdio.h>
#include <sqlite3.h>
#include <iostream>
#include "ContactController.h"
#include "DisplayController.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;
// init static db pointer
sqlite3 *ContactController::db;
int ContactController::dbSize = 0;

int main(void)
{
    // Init DB
    ContactController::openDatabase();
    ContactController::initDatabase();

    // contactController.listContacts();
    while (true)
    {
        DisplayController::showMainMenu();

        // user input
        int mainMenuInput = DisplayController::readInput(1, 8);
        switch (mainMenuInput)
        {
        case 1:
            // creating a local scope because C++ standard forbids a goto to bypass an initialization of a non-POD object
            {
                ContactType newContact;
                newContact = DisplayController::readContactInput();
                ContactController::addContact(newContact);
                break;
            }
        case 2:
            DisplayController::clearScreen();
            DisplayController::showContactListHeader();
            ContactController::listContacts();
            cout << "Press any key to continue..." << endl;
            getchar();
            break;
        case 3:
            DisplayController::clearScreen();

        case 5:
            DisplayController::confirmDBClear();
            int confirmInput;
            confirmInput = DisplayController::readInput(1, 2);
            if (confirmInput == 1)
            {
                ContactController::clearDatabase();
            }
            else
            {
                logger("info", "DB clear cancelled");
            }

            break;
        case 6:
        {
            DisplayController::clearScreen();
            DisplayController::showContactSearchHeader();
            cout << "Enter a name to search for: ";
            string searchString;
            cin >> searchString;
            ContactController::findContact(searchString);
            getchar();
        }
            cout << "Press Enter to continue" << endl;
            getchar();
            break;

        case 7:
            DisplayController::clearScreen();
            DisplayController::showAbout();
            cout << "Press Enter to continue" << endl;
            getchar();
            getchar();
            break;
        case 8:
            printf("Bye.");
            exit(0);
        default:
            // we should never get here because we provided min and max for readInput
            logger("error", "Invalid input (unhandled)");
            break;
        }
    }

    // Cleanup
    ContactController::closeDatabase();
    return EXIT_SUCCESS;
}