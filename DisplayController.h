#include <string>

using std::string;

class DisplayController
{

public:
    int outputWidth = 40;

    int readInput(int min, int max);
    void clearScreen();
    void confirmDBClear();
    void centerPrint(string text);
    void showMainMenu();
    void showAbout();
    void Exit();
};
