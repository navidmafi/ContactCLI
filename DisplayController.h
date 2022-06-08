#include <string>

using std::string;

class DisplayController
{

public:
    int outputWidth = 40;

    void centerPrint(string text);
    void showMainMenu();
    void showAbout();
    void Exit();
};
