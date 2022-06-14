/* Copyright Navid Mafi Ranji
This source code is provided only for reference purposes. This is not a public domain source code.
All rights reserved.
*/

#include <iostream>
#include <sqlite3.h>
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
    ContactController::readDBSize();

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
            if (ContactController::dbSize == 0)
            {
                logger("userInput", "No contact to show details, press enter to go back");
                cin.get();
            }
            else
            {
                logger("userInput", "Enter contact ID to show details");
                int subInput;
                subInput = DisplayController::readInput(1, ContactController::dbSize);
                ContactController::showSingleContact(subInput);
                cin.get();
            }
            break;
        case 3:
            DisplayController::clearScreen();
            ContactController::listContacts();
            if (ContactController::dbSize == 0)
            {
                logger("userInput", "No contact to edit, press enter to go back");
                cin.get();
            }
            else
            {
                logger("userInput", "Enter contact ID to edit");
                int subInput;
                subInput = DisplayController::readInput(1, ContactController::dbSize);
                ContactController::showSingleContact(subInput);
                logger("userInput", "enter what info do you want to edit.");
                logger("userInput", "pass empty input to not edit anything");
                logger("userInput", " 1- First name     2- Last name    3- Address      4- Email       5- Phone Number");
                int userSelection;
                userSelection = DisplayController::readInput(1, 6);
                // This is a dirty and lazy way to do it. But since there is no repetition and we only use this logic in one place, it's fine
                switch (userSelection)
                {
                    // Using new scopes in switch cases are necessary. It's not a programmer mistake.
                case 1:
                {
                    logger("userInput", "Enter new firstName: ");
                    string newFirstName;
                    newFirstName = DisplayController::readOptionalInput<string>();
                    if (newFirstName != "Unknown")
                    {
                        ContactController::editContactField(subInput, "LASTNAME", newFirstName);
                    }
                    else
                    {
                        logger("info", "No change made");
                    }
                    break;
                }
                case 2:
                {
                    logger("userInput", "Enter new lastName: ");
                    string newLastName;
                    newLastName = DisplayController::readOptionalInput<string>();
                    if (newLastName != "Unknown")
                    {
                        ContactController::editContactField(subInput, "LASTNAME", newLastName);
                    }
                    else
                    {
                        logger("info", "No change made");
                    }
                    break;
                }
                case 3:
                {
                    logger("userInput", "Enter new address : ");
                    string newAddress;
                    newAddress = DisplayController::readOptionalInput<string>();
                    if (newAddress != "Unknown")
                    {
                        ContactController::editContactField(subInput, "ADDRESS", newAddress);
                    }
                    else
                    {
                        logger("info", "No change made");
                    }
                    break;
                }
                case 4:
                {
                    logger("userInput", "Enter new email: ");
                    string newEmail;
                    newEmail = DisplayController::readOptionalInput<string>();
                    if (newEmail != "Unknown")
                    {
                        ContactController::editContactField(subInput, "EMAIL", newEmail);
                    }
                    else
                    {
                        logger("info", "No change made");
                    }
                    break;
                }
                case 5:
                {
                    logger("userInput", "Enter new phoneNumber: ");
                    string newPhoneNumber;
                    newPhoneNumber = DisplayController::readOptionalInput<string>();
                    if (newPhoneNumber != "Unknown")
                    {
                        ContactController::editContactField(subInput, "PHONENUMBER", newPhoneNumber);
                    }
                    else
                    {
                        logger("info", "No change made");
                    }
                    break;
                }

                default:
                    logger("info", "Invalid input");
                    break;
                }
            }
            break;

            break;
        case 4:
            DisplayController::clearScreen();
            ContactController::listContacts();
            if (ContactController::dbSize == 0)
            {
                logger("userInput", "No contact to delete, press enter to go back");
                cin.get();
            }
            else
            {
                logger("userInput", "Enter contact ID to delete");
                int subInput;
                subInput = DisplayController::readInput(1, ContactController::dbSize);
                // confirm deletion
                logger("userInput", "Are you sure you want to delete this contact? (y/n)");
                char userSelection;

                // using ASCII char number :D
                userSelection = cin.get();
                if (userSelection == 'y')
                {
                    ContactController::deleteContact(subInput);
                }
                else
                {
                    logger("info", "No change made");
                }
            }
            break;
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
            logger("userInput", "enter id to show details or enter 0 to go back");
            int subInput;
            subInput = DisplayController::readInput(0, ContactController::dbSize);
            if (subInput == 0)
            {
                break;
            }
            ContactController::showSingleContact(subInput);
        }
            cout << "Press Enter to continue" << endl;
            cin.get();
            break;

        case 7:
            DisplayController::clearScreen();
            DisplayController::showAbout();
            cout << "Press Enter to continue" << endl;
            cin.get();
            break;
        case 8:
            cout << "bye." << endl;
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