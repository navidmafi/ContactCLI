#include <stdio.h>
#include <sqlite3.h>
#include "ContactController.h"
#include "DisplayController.h"

using std::string;
sqlite3 *ContactController::db;

int main(void)
{
    // Init
    // init static db variable
    ContactController::openDatabase();
    ContactController::initDatabase();

    // Stuff
    ContactType newContact;
    newContact.firstName = "Ali";
    newContact.lastName = "Akbari";
    newContact.gender = 1;
    newContact.age = 22;
    newContact.address = "AliAabd";
    newContact.email = "aliAbaadi@gmail.com";
    newContact.phoneNumber = "09155888884";

    ContactController::addContact(newContact);

    // contactController.listContacts();
    DisplayController::showMainMenu();

    // user input
    int mainMenuInput = DisplayController::readInput(1, 7);
    switch (mainMenuInput)
    {
    case 5:
        ContactController::clearDatabase();
        break;

    case 6:
        DisplayController::clearScreen();
        DisplayController::showAbout();
        break;
    case 7:
        printf("Bye.");
        exit(0);
    default:
        // we should never get here because we provided min and max for readInput
        logger("error", "Invalid input (unhandled)");
        break;
    }

    // Cleanup
    ContactController::closeDatabase();
    return 0;
}