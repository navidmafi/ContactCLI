#include <string>
#include <sqlite3.h>
#include "Utils.h"

using std::string;

class ContactController
{
public:
    // ContactController();
    // ~ContactController();
    void openDatabase();
    void closeDatabase();
    void initDatabase();
    void clearDatabase();
    void addContact(ContactType contact);
    void deleteContact(string name);
    void updateContact(string name, string phone);
    void listContacts();
    void searchContact(string name);

private:
    sqlite3 *db;
    string name;
    string phone;
    string message;
    string logtype;
    string logmessage;
};
