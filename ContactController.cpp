#include <string>
#include <sqlite3.h>
#include "ContactController.h"
#include "Utils.h"
using std::string;

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    for (i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void ContactController::openDatabase()
{
    rc = sqlite3_open("db/test.db", &db);
    if (rc)
    {
        logger("error", "Error occured while opening DB " + string(sqlite3_errmsg(db)));
    }
    else
    {
        logger("info", "Opened DB successfully");
    }
}
void ContactController::initDatabase()
{

    char *sqlQuery = "CREATE TABLE CONTACTS("
                     "ID 			INT PRIMARY KEY     NOT NULL,"
                     "FIRSTNAME     TEXT    			NOT NULL,"
                     "LASTNAME		TEXT    			NOT NULL,"
                     "AGE			INT     			NOT NULL,"
                     "GENDER		INT     			NOT NULL,"
                     "ADDRESS		CHAR(50),"
                     "EMAIL			CHAR(50),"
                     "PHONENUMBER	TEXT		 		NOT NULL);";
    char *zErrMsg = 0;
    rc = sqlite3_exec(db, sqlQuery, callback, 0, &zErrMsg);
    if (rc != SQLITE_OK)
    {
        logger("error", "Error while init db");
        sqlite3_free(zErrMsg);
    }
    else
    {
        logger("info", "DB Init succesfully");
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
