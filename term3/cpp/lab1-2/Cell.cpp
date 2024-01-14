#include "Cell.h"
#define MAX_STR_LEN 64

char* Cell::changeLogin()
{
    char* str = new char[MAX_STR_LEN];
    cout << "Enter new login: ";
    cin.getline(str, MAX_STR_LEN);
    rewind(stdin);
    return str;
}

char* Cell::changeName()
{
    char* str = new char[MAX_STR_LEN];
    cout << "Enter new name: ";
    cin.getline(str, MAX_STR_LEN);
    rewind(stdin);
    return str;
}

bool Cell::operator==(char* _login)
{
    return strcmp(this->getLogin() , _login);
}
