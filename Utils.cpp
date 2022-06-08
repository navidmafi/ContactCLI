#include <stdio.h>
#include <string>
#include "Utils.h"

using std::string;

void logger(string logtype, string message)
{
    printf("[%s] %s\n", logtype.c_str(), message.c_str());
}