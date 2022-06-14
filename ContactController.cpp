/* Copyright Navid Mafi Ranji
This source code is provided only for reference purposes. This is not a public domain source code.
All rights reserved.
*/
#include <iostream>
#include "ContactController.h"
using std::cout;
using std::endl;
using std::stoi;
using std::string;
using std::to_string;
static int contactListCB(void *NotUsed, int argc, char **argv, char **azColName)
{
    cout << argv[0] << " - " << argv[1] << " " << argv[2] << endl;
    return 0;
}

static int singleContactCB(void *NotUsed, int argc, char **argv, char **azColName)
{
    for (int i = 0; i < argc; i++)
    {
        cout << azColName[i] << " : " << argv[i] << endl;
    }

    printf("\n");
    return 0;
}
static int contactCountCB(void *NotUsed, int argc, char **argv, char **azColName)
{
    logger("info", "Contact count: " + std::to_string(stoi(argv[0])));
    ContactController::dbSize = stoi(argv[0]);
    return 0;
}
void ContactController::openDatabase()
{
    int rc = sqlite3_open("contacts.db", &db);
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
                      "ADDRESS		CHAR(50),"
                      "EMAIL			CHAR(50),"
                      "PHONENUMBER	TEXT		 		NOT NULL);";
    char *cErrMsg = 0;
    int rc = sqlite3_exec(db, sqlQuery.c_str(), contactListCB, 0, &cErrMsg);
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

    // set dbSize
}
void ContactController::readDBSize()
{
    char *cErrMsg = 0;
    string sqlQuery2 = "SELECT COUNT(*) FROM CONTACTS;";
    int rc = sqlite3_exec(db, sqlQuery2.c_str(), contactCountCB, 0, &cErrMsg);
    logger("debug", "Ran sql count query");
    if (rc != SQLITE_OK)
    {
        string errMsg = cErrMsg;
        logger("error", "Error while counting db :: " + errMsg);
        sqlite3_free(cErrMsg);
    }
    else
    {
        logger("info", "DB Count succesfully");
    }
}
void ContactController::addContact(ContactType contact)
{
    string sqlQuery = "INSERT INTO CONTACTS (FIRSTNAME,LASTNAME,AGE,ADDRESS,EMAIL,PHONENUMBER) "
                      "VALUES (\"" +
                      contact.firstName +
                      "\",\"" + contact.lastName +
                      "\",\"" + to_string(contact.age) +
                      "\",\"" + contact.address +
                      "\",\"" + contact.email +
                      "\",\"" + contact.phoneNumber + "\");";
    char *cErrMsg = 0;
    int rc = sqlite3_exec(db, sqlQuery.c_str(), contactListCB, 0, &cErrMsg);

    if (rc != SQLITE_OK)
    {
        string errMsg = cErrMsg;
        logger("error", "Error while inserting new contact :: " + errMsg);
        sqlite3_free(cErrMsg);
    }
    else
    {
        logger("info", "New Contact inserted succesfully");
        readDBSize();
    }
}
void ContactController::editContactField(int id, string field, string newValue)
{
    string sqlQuery = "UPDATE CONTACTS SET " + field + " = \"" + newValue + "\" WHERE ID = " + to_string(id) + ";";
    char *cErrMsg = 0;
    int rc = sqlite3_exec(db, sqlQuery.c_str(), 0, 0, &cErrMsg);
    if (rc != SQLITE_OK)
    {
        string errMsg = cErrMsg;
        logger("error", "Error while editing contact :: " + errMsg);
        sqlite3_free(cErrMsg);
    }
    else
    {
        logger("info", "Field edited succesfully");
    }
}
void ContactController::deleteContact(int id)
{
    string sqlQuery = "DELETE FROM CONTACTS WHERE ID = " + to_string(id) + ";";
    char *cErrMsg = 0;
    int rc = sqlite3_exec(db, sqlQuery.c_str(), 0, 0, &cErrMsg);
    if (rc != SQLITE_OK)
    {
        string errMsg = cErrMsg;
        logger("error", "Error while deleting contact :: " + errMsg);
        sqlite3_free(cErrMsg);
    }
    else
    {
        logger("info", "Contact deleted succesfully");
        readDBSize();
    }
}
void ContactController::updateContact(int id, ContactType newContent)
{
    // update contact with id = id to newContent
    string sqlQuery = "UPDATE CONTACTS SET FIRSTNAME = \"" + newContent.firstName +
                      "\", LASTNAME = \"" + newContent.lastName +
                      "\", AGE = \"" + to_string(newContent.age) +
                      "\", ADDRESS = \"" + to_string(newContent.age) +
                      "\", EMAIL = \"" + to_string(newContent.age) +
                      "\", PHONENUMBER = \"" + to_string(newContent.age) + "\" WHERE ID = " + to_string(id) + ";";
    char *cErrMsg = 0;
    int rc = sqlite3_exec(db, sqlQuery.c_str(), contactListCB, 0, &cErrMsg);

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
    // string sqlQuery = "SELECT * from CONTACTS";
    // read id and firstname and lastname from db
    string sqlQuery = "SELECT ID,FIRSTNAME,LASTNAME from CONTACTS";
    int rc = sqlite3_exec(db, sqlQuery.c_str(), contactListCB, 0, &cErrMsg);
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
void ContactController::showSingleContact(int contactID)
{
    char *cErrMsg = 0;
    string sqlQuery = "SELECT * from CONTACTS WHERE ID = " + to_string(contactID) + ";";
    int rc = sqlite3_exec(db, sqlQuery.c_str(), singleContactCB, 0, &cErrMsg);
    if (rc != SQLITE_OK)
    {

        string errMsg = cErrMsg;
        logger("error", "Error while reading single contact :: " + errMsg);
        sqlite3_free(cErrMsg);
    }
    else
    {
        logger("info", "Read single contact succesfully");
    }
}
void ContactController::findContact(string searchString)
{
    // search for contact with firstname or lastname containing searchString
    // return array of contacts
    // if no contact found return empty array
    // if more than one contact found return array of contacts
    char *cErrMsg = 0;
    string sqlQuery = "SELECT * from CONTACTS WHERE FIRSTNAME LIKE \"%" + searchString + "%\" OR LASTNAME LIKE \"%" + searchString + "%\"";
    int rc = sqlite3_exec(db, sqlQuery.c_str(), contactListCB, 0, &cErrMsg);
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
    int rc = sqlite3_exec(db, sqlQuery.c_str(), contactListCB, 0, &cErrMsg);
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
