#include <stdio.h>
#include <string>
#include "DisplayController.h"

void DisplayController::centerPrint(string text)
{
    int textLength = text.length();
    int padding = (outputWidth - textLength) / 2;
    printf("%*s%s%*s\n", padding, "", text.c_str(), padding, "");
}
void DisplayController::showMainMenu()
{
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
}

void DisplayController::showAbout()
{
    // clear screen
    printf("\033[2J");
    printf("\033[0;0H");

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
}
