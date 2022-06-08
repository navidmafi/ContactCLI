#include <stdio.h>
#include "ContactController.h"

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

    contactController.addContact(newContact);

    getchar();
    // Cleanup
    contactController.closeDatabase();
    return 0;
}