/* Copyright Navid Mafi Ranji
This source code is provided only for reference purposes. This is not a public domain source code.
All rights reserved.
*/

#include <string>

using std::string;

#ifndef UTILS_H
#define UTILS_H
struct ContactType
{
    string firstName;
    string lastName;
    int gender;
    int age;
    string address;
    string email;
    string phoneNumber;
};

enum contactProps
{
    firstName,
    lastName,
    gender,
    age,
    address,
    phoneNumber
};

void logger(string logtype, string message);

#endif