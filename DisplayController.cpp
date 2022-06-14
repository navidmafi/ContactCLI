/* Copyright Navid Mafi Ranji
This source code is provided only for reference purposes. This is not a public domain source code.
All rights reserved.
*/

// Migrated to iostream because i really did not want to manually handle char buffers.
#include <iostream>
#include <iomanip>
#include <string>
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
#if defined _WIN32
    system("cls");
    // clrscr(); // including header file : conio.h
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
    // std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences
#elif defined(__APPLE__)
    system("clear");
#endif
}
void DisplayController::centerPrint(string text)
{
    int textLength = text.length();
    int padding = (outputWidth - textLength) / 2;
    // printf("%*s%s%*s\n", padding, "", text.c_str(), padding, "");
    cout << std::setw(padding) << " " << text << std::setw(padding) << " " << endl;
}
void DisplayController::showMainMenu()
{
    cout << "-----------------------------------------\n";
    centerPrint("Main Menu");
    cout << "-----------------------------------------\n";
    cout << "1. Add Contact\n";
    cout << "2. List Contacts\n";
    cout << "3. Edit Contact\n";
    cout << "4. Delete Contact\n";
    cout << "5. Clear Contacts Database\n";
    cout << "6. Find Contact\n";
    cout << "7. About\n";
    cout << "8. Exit\n";
}

void DisplayController::confirmDBClear()
{

    cout << "-----------------------------------------\n";
    centerPrint("Clear Contacts Database");
    cout << "-----------------------------------------\n";
    cout << "Are you sure you want to clear the database?\n";
    cout << "1. Yes                 2. No\n";
}
void DisplayController::showContactSearchHeader()
{
    cout << "-----------------------------------------\n";
    centerPrint("Contacts Search");
    cout << "-----------------------------------------\n";
}
void DisplayController::showContactListHeader()
{

    cout << "-----------------------------------------\n";
    centerPrint("Contacts");
    cout << "-----------------------------------------\n";
}
// updateContactScreen
void DisplayController::showAbout()
{

    cout << "-----------------------------------------\n";
    centerPrint("About");
    cout << "-----------------------------------------\n";
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