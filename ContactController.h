#include <string>
#include <sqlite3.h>

using std::string;

class ContactController
{
public:
    // ContactController();
    // ~ContactController();
    void openDatabase();
    void closeDatabase();
    void addContact(string name, string phone);
    void deleteContact(string name);
    void updateContact(string name, string phone);
    void listContacts();
    void searchContact(string name);

private:
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    string sql;
    string name;
    string phone;
    string message;
    string logtype;
    string logmessage;
};
