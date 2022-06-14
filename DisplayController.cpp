/* Copyright Navid Mafi Ranji
This source code is provided only for reference purposes. This is not a public domain source code.
All rights reserved.
*/

// Migrated to iostream because i really did not want to manually handle char buffers.
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdexcept>
#include <limits>
#include "DisplayController.h"

using std::cin;
using std::cout;
using std::endl;
using std::ws;

// I will try to use the "Single Responsibility Principle" here as much as i can.
int DisplayController::readInput(int min, int max)
{
    int userInput = 0;
    scanf("%d", &userInput);
    while (userInput < min || userInput > max)
    {
        cout << "Invalid input, please try again: ";
        cin >> userInput;
    }
    cin.ignore();

    return userInput;
}
template <typename T>
T DisplayController::readOptionalInput(T defaultValue)
{
    T userInput;

    if (cin.peek() == '\n')
    {
        cin.ignore();
        return defaultValue;
    }
    else
    {
        try
        {
            getline(cin, userInput);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }

        return userInput;
    }
}
ContactType DisplayController::readContactInput()
{
    ContactType contact;
    cout << "First Name : ";
    contact.firstName = readOptionalInput<string>();
    cout << "Last Name: ";
    contact.lastName = readOptionalInput<string>();
    cout << "Age ( 0 For unknown ): ";
    contact.age = readInput(0, 500);
    cout << "Address: ";
    contact.address = readOptionalInput<string>();
    cout << "Email: ";
    contact.email = readOptionalInput<string>();
    cout << "Phone number: ";
    contact.phoneNumber = readOptionalInput<string>();

    return contact;
}
void DisplayController::clearScreen()
{
    printf("\033[2J");
    printf("\033[0;0H");
}
void DisplayController::centerPrint(string text)
{
    int textLength = text.length();
    int padding = (outputWidth - textLength) / 2;
    printf("%*s%s%*s\n", padding, "", text.c_str(), padding, "");
}
void DisplayController::showMainMenu()
{
    printf("-----------------------------------------\n");
    centerPrint("Main Menu");
    printf("-----------------------------------------\n");
    printf("1. Add Contact\n");
    printf("2. List Contacts\n");
    printf("3. Edit Contact\n");
    printf("4. Delete Contact\n");
    printf("5. Clear Contacts Database\n");
    printf("6. Find Contact\n");
    printf("7. About\n");
    printf("8. Exit\n");
}
void DisplayController::confirmDBClear()
{

    printf("-----------------------------------------\n");
    centerPrint("Clear Contacts Database");
    printf("-----------------------------------------\n");
    printf("Are you sure you want to clear the database?\n");
    printf("1. Yes\n");
    printf("2. No\n");
}
void DisplayController::showContactSearchHeader()
{
    printf("-----------------------------------------\n");
    centerPrint("Contacts Search");
    printf("-----------------------------------------\n");
}
void DisplayController::showContactListHeader()
{

    printf("-----------------------------------------\n");
    centerPrint("Contacts");
    printf("-----------------------------------------\n");
}
// updateContactScreen
void DisplayController::showAbout()
{

    printf("-----------------------------------------\n");
    centerPrint("About");
    printf("-----------------------------------------\n");
    centerPrint("Software architecture and DB design");
    centerPrint("Navid Mafi");
    centerPrint("--------------");
    centerPrint("Development");
    centerPrint("Navid Mafi");
    centerPrint("--------------");
    centerPrint("Testing");
    centerPrint("Navid Mafi");
    centerPrint("--------------");
    centerPrint("Copyright (c) Navid Mafi 2022");
}