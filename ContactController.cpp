#include <string>
#include <sqlite3.h>
#include "ContactController.h"
#include "Utils.h"
using std::string;

void ContactController::openDatabase()
{
    rc = sqlite3_open("test.db", &db);
    if (rc)
    {
        logger("error", "Error occured while opening DB " + string(sqlite3_errmsg(db)));
    }
    else
    {
        logger("info", "Opened DB successfully");
    }
}

void ContactController::closeDatabase()
{
    rc = sqlite3_close(db);
    if (rc)
    {
        logger("error", "Error while closing DB " + string(sqlite3_errmsg(db)));
    }
    else
    {
        logger("info", "Closed DB. Bye.");
    }
}
