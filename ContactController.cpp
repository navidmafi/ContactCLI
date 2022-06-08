
#include "ContactController.h"
using std::string;
using std::to_string;

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
    int rc = sqlite3_open("db/test.db", &db);
    if (rc)
    {
        logger("error", "Error occured while opening DB :: " + string(sqlite3_errmsg(db)));
    }
    else
    {
        logger("info", "Opened DB successfully");
    }
}
void ContactController::initDatabase()
{

    string sqlQuery = "CREATE TABLE IF NOT EXISTS CONTACTS("
                      "ID 			INT PRIMARY KEY     NOT NULL,"
                      "FIRSTNAME     TEXT    			NOT NULL,"
                      "LASTNAME		TEXT    			NOT NULL,"
                      "AGE			INT     			NOT NULL,"
                      "GENDER		INT     			NOT NULL,"
                      "ADDRESS		CHAR(50),"
                      "EMAIL			CHAR(50),"
                      "PHONENUMBER	TEXT		 		NOT NULL);";
    char *cErrMsg = 0;
    string errMsg;
    int rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &cErrMsg);
    errMsg = cErrMsg;
    if (rc != SQLITE_OK)
    {
        logger("error", "Error while init db :: " + errMsg);
        sqlite3_free(cErrMsg);
    }
    else
    {
        logger("info", "DB Init succesfully");
    }
}
void ContactController::addContact(ContactType contact)
{
    string sqlQuery = "INSERT INTO CONTACTS (FIRSTNAME,LASTNAME,AGE,GENDER,ADDRESS,EMAIL,PHONENUMBER) "
                      "VALUES (\"" +
                      contact.firstName +
                      "\",\"" + contact.lastName +
                      "\",\"" + to_string(contact.age) +
                      "\",\"" + to_string(contact.gender) +
                      "\",\"" + contact.address +
                      "\",\"" + contact.email +
                      "\",\"" + contact.phoneNumber + "\");";
    char *cErrMsg = 0;
    string errMsg;
    int rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &cErrMsg);
    errMsg = cErrMsg;

    if (rc != SQLITE_OK)
    {
        logger("error", "Error while inserting new contact :: " + errMsg);
        sqlite3_free(cErrMsg);
    }
    else
    {
        logger("info", "New Contact inserted succesfully");
    }
}
void ContactController::closeDatabase()
{
    int rc = sqlite3_close(db);
    if (rc)
    {
        logger("error", "Error while closing DB :: " + string(sqlite3_errmsg(db)));
    }
    else
    {
        logger("info", "Closed DB. Bye.");
    }
}
