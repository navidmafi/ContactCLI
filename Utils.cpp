/* Copyright Navid Mafi Ranji
This source code is provided only for reference purposes. This is not a public domain source code.
All rights reserved.
*/

#include <iostream>
#include <string>
#include "Utils.h"

using std::cout;
using std::endl;
using std::string;

void logger(string logtype, string message)
{
    cout << "[" << logtype << "] " << message << endl;
}