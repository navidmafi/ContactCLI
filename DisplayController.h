/* Copyright Navid Mafi Ranji
This source code is provided only for reference purposes. This is not a public domain source code.
All rights reserved.
*/

#include <string>
#include "Utils.h"

using std::string;

class DisplayController
{

public:
    static const int outputWidth = 40;

    static int readInput(int min, int max);
    static ContactType readContactInput();
    static void clearScreen();
    static void confirmDBClear();
    static void centerPrint(string text);
    static void showMainMenu();
    static void showAbout();
    static void Exit();
};
