/* Copyright Navid Mafi Ranji
This source code is provided only for reference purposes. This is not a public domain source code.
All rights reserved.
*/

#include <stdio.h>
#include <sqlite3.h>
#include "ContactController.h"
#include "DisplayController.h"

using std::string;
// init static db pointer
sqlite3 *ContactController::db;

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
        int mainMenuInput = DisplayController::readInput(1, 7);
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
        case 5:
            ContactController::clearDatabase();
            break;

        case 6:
            DisplayController::clearScreen();
            DisplayController::showAbout();
            printf("Press enter to go back \n");
            getchar();
            getchar();
            break;
        case 7:
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