#include <stdio.h>
#include <string>
#include "DisplayController.h"
#include "Utils.h"

void DisplayController::readInput()
{
    int userInput = 0;
    scanf("%d", &userInput);
    switch (userInput)
    {
    case 6:
        clearScreen();
        this->showAbout();
        break;
    default:
        logger("error", "Invalid input");
        break;
    }
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
    clearScreen();
    printf("█████████████████████████████████████████\n");
    centerPrint("Main Menu");
    printf("█████████████████████████████████████████\n");
    printf("1. Add Contact\n");
    printf("2. List Contacts\n");
    printf("3. Edit Contact\n");
    printf("4. Delete Contact\n");
    printf("5. Clear Contacts Database\n");
    printf("6. About\n");
    printf("7. Exit\n");

    // ! I'm not sure if this is the best way to do this because I'm repeating the same code
    this->readInput();
}

void DisplayController::showAbout()
{

    printf("█████████████████████████████████████████\n");
    centerPrint("About");
    printf("█████████████████████████████████████████\n");
    centerPrint("Software architecture");
    centerPrint("Navid Mafi");
    centerPrint("--------------");
    centerPrint("Development");
    centerPrint("Navid Mafi");
    centerPrint("--------------");
    centerPrint("Testing");
    centerPrint("Navid Mafi");
    centerPrint("--------------");
    printf("Press any key to go back");
    getchar();
    getchar();
    this->showMainMenu();
}
