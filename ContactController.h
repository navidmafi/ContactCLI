/* Copyright Navid Mafi Ranji
This source code is provided only for reference purposes. This is not a public domain source code.
All rights reserved.
*/

#include <string>
#include <sqlite3.h>
#include "Utils.h"

using std::string;

class ContactController
{
public:
    // ContactController();
    // ~ContactController();
    static void openDatabase();
    static void closeDatabase();
    static void initDatabase();
    static void clearDatabase();
    static void addContact(ContactType contact);
    static void updateContact(int id, ContactType newContent);
    static void deleteContact(string name);
    static void updateContact(string name, string phone);
    static void listContacts();
    static void searchContacts(string name);
    static void findContact(string searchString);
    static sqlite3 *db;
    static int dbSize;

    // private:
};
