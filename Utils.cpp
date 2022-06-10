/* Copyright Navid Mafi Ranji
This source code is provided only for reference purposes. This is not a public domain source code.
All rights reserved.
*/

#include <stdio.h>
#include <string>
#include "Utils.h"

using std::string;

void logger(string logtype, string message)
{
    printf("[%s] %s\n", logtype.c_str(), message.c_str());
}