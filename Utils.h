#include <string>

using std::string;

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

void logger(string logtype, string message);