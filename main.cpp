#include <stdio.h>
#include "ContactController.h"
#include "DisplayController.h"

using std::string;

int main(void)
{
    // Init
    ContactController contactController;

    contactController.openDatabase();
    contactController.initDatabase();

    // Stuff
    ContactType newContact;
    newContact.firstName = "Ali";
    newContact.lastName = "Akbari";
    newContact.gender = 1;
    newContact.age = 22;
    newContact.address = "AliAabd";
    newContact.email = "aliAbaadi@gmail.com";
    newContact.phoneNumber = "09155888884";

    // contactController.addContact(newContact);

    // contactController.listContacts();

    DisplayController displayController;
    displayController.showMainMenu();

    // user input
    int mainMenuInput = displayController.readInput(1, 7);
    switch (mainMenuInput)
    {
    case 5:
        // ContactController::clearDatabase();

    case 6:
        displayController.clearScreen();
        displayController.showAbout();
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
    contactController.closeDatabase();
    return 0;
}