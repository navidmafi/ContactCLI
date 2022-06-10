#include <string>

using std::string;

class DisplayController
{

public:
    static const int outputWidth = 40;

    static int readInput(int min, int max);
    static void clearScreen();
    static void confirmDBClear();
    static void centerPrint(string text);
    static void showMainMenu();
    static void showAbout();
    static void Exit();
};
