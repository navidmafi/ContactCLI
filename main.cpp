#include <stdio.h>
#include <sqlite3.h>
#include <string>
#include "ContactController.h"
#include "Utils.h"

using std::string;

int main(void)
{
    // Init
    ContactController contactController;
    contactController.openDatabase();

    getchar();
    // Cleanup
    contactController.closeDatabase();
    return 0;
}