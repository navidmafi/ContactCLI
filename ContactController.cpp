/* Copyright Navid Mafi Ranji
This source code is provided only for reference purposes. This is not a public domain source code.
All rights reserved.
*/

#include "ContactController.h"
using std::string;
using std::to_string;

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    for (int i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}
static int callback2(void *NotUsed, int argc, char **argv, char **azColName)
{
    // ID - First Name - Last Name
    printf("%s", NotUsed);
    printf("%s - %s %s\n", argv[0], argv[1], argv[2]);

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
                      "ID 			INTEGER PRIMARY KEY,"
                      "FIRSTNAME     TEXT    			NOT NULL,"
                      "LASTNAME		TEXT    			NOT NULL,"
                      "AGE			INTEGER     			NOT NULL,"
                      "GENDER		INTEGER     			NOT NULL,"
                      "ADDRESS		CHAR(50),"
                      "EMAIL			CHAR(50),"
                      "PHONENUMBER	TEXT		 		NOT NULL);";
    char *cErrMsg = 0;
    int rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &cErrMsg);
    logger("debug", "Ran sql init query");
    if (rc != SQLITE_OK)
    {
        string errMsg = cErrMsg;
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
    int rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &cErrMsg);

    if (rc != SQLITE_OK)
    {
        string errMsg = cErrMsg;
        logger("error", "Error while inserting new contact :: " + errMsg);
        sqlite3_free(cErrMsg);
    }
    else
    {
        logger("info", "New Contact inserted succesfully");
    }
}

void ContactController::updateContact(int id, ContactType newContent)
{
    // update contact with id = id to newContent
    string sqlQuery = "UPDATE CONTACTS SET FIRSTNAME = \"" + newContent.firstName +
                      "\", LASTNAME = \"" + newContent.lastName +
                      "\", AGE = \"" + to_string(newContent.age) +
                      "\", GENDER = \"" + to_string(newContent.age) +
                      "\", ADDRESS = \"" + to_string(newContent.age) +
                      "\", EMAIL = \"" + to_string(newContent.age) +
                      "\", PHONENUMBER = \"" + to_string(newContent.age) + "\" WHERE ID = " + to_string(id) + ";";
    char *cErrMsg = 0;
    int rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &cErrMsg);

    if (rc != SQLITE_OK)
    {
        string errMsg = cErrMsg;
        logger("error", "Error while updating contact :: " + errMsg);
        sqlite3_free(cErrMsg);
    }
    else
    {
        logger("info", "Contact updated succesfully");
    }
}
void ContactController::listContacts()
{
    char *cErrMsg = 0;
    const char *data = "Callback function called";
    // string sqlQuery = "SELECT * from CONTACTS";
    // read id and firstname and lastname from db
    string sqlQuery = "SELECT ID,FIRSTNAME,LASTNAME from CONTACTS";
    int rc = sqlite3_exec(db, sqlQuery.c_str(), callback2, (void *)data, &cErrMsg);
    if (rc != SQLITE_OK)
    {

        string errMsg = cErrMsg;
        logger("error", "Error while reading all contacts :: " + errMsg);
        sqlite3_free(cErrMsg);
    }
    else
    {
        logger("info", "Read Contacts succesfully");
    }
}
void ContactController::findContact(string searchString)
{
    // search for contact with firstname or lastname containing searchString
    // return array of contacts
    // if no contact found return empty array
    // if more than one contact found return array of contacts
    char *cErrMsg = 0;
    const char *data = "Callback function called";
    string sqlQuery = "SELECT * from CONTACTS WHERE FIRSTNAME LIKE \"%" + searchString + "%\" OR LASTNAME LIKE \"%" + searchString + "%\"";
    int rc = sqlite3_exec(db, sqlQuery.c_str(), callback2, (void *)data, &cErrMsg);
    if (rc != SQLITE_OK)
    {

        string errMsg = cErrMsg;
        logger("error", "Error while searching contacts :: " + errMsg);
        sqlite3_free(cErrMsg);
    }
    else
    {
        logger("info", "Search Contacts succesfully");
    }
}
void ContactController::clearDatabase()
{
    string sqlQuery = "DELETE from CONTACTS";
    char *cErrMsg = 0;
    int rc = sqlite3_exec(db, sqlQuery.c_str(), callback, 0, &cErrMsg);
    if (rc != SQLITE_OK)
    {
        string errMsg = cErrMsg;
        logger("error", "Error while clearing database :: " + errMsg);
        sqlite3_free(cErrMsg);
    }
    else
    {
        logger("info", "Database cleared succesfully");
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
