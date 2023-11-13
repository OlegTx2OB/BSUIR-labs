#include "Menu.h"
#define MAX_STR_LEN 64
#define MAX_ARRAY_SIZE 1000

using namespace std;

void *Menu::operator new(size_t size)
{
    cout << "Hello\n";
    void *memory = malloc(size);
    return memory;
}
void Menu::operator delete(void *ptr)
{
    cout << "Bye\n";
    free(ptr);
}
istream &operator>>(istream &input, Menu &menu)
{
    menu.mainMenu();
    return input;
}
int Menu::getInt(int lowerBound, int upperBound)
{
    int d;
    while (!scanf_s("%d", &d) || d < lowerBound || d > upperBound || getchar() != '\n')
    {
        printf("invalid input\n");
        cin.ignore();
    }
    return d;
}
HashTable* Menu::createHashTable()
{
    HashTable hashTableArray[MAX_ARRAY_SIZE];
    for (int i = 0; i < MAX_ARRAY_SIZE; i++) hashTableArray[i] = HashTable(nullptr, nullptr);
    return hashTableArray;
}

void Menu::logIn(HashTable* hashTableArray)
{
    char* login = getLoginOrPassword();
    int hash = HashTable::hashCalculation(getLoginOrPassword());
    HashTable& hashTable = hashTableArray[hash];
    Cell* cellLink = HashTable::peek(hashTable, login);
    if (cellLink == nullptr)
    {
        cout << "Person is not found\n";
    }
    else
    {
        Cell& cell = *cellLink;
        userMenu(&cell);
    }
}
void Menu::registerNewAccount(HashTable* hashTableArray)
{
    char* login = getLoginOrPassword();
    int hash = HashTable::hashCalculation(getLoginOrPassword());
    Cell* newCell = new Cell(login, undefinedName(),0, nullptr, nullptr);
    HashTable::push(&hashTableArray[hash], newCell);
    HashTable& hashTable = hashTableArray[hash];
    userMenu(newCell);
}

void Menu::deleteAccount(HashTable* hashTableArray)
{
    char* login = getLoginOrPassword();
    int hashNumber = HashTable::hashCalculation(getLoginOrPassword());

    HashTable::pop(&hashTableArray[hashNumber], login);
}

char* Menu::getLoginOrPassword()
{
    char* str = new char[MAX_STR_LEN];
    cout << "Enter 1.login, 2.password for account: ";
    cin.getline(str, MAX_STR_LEN);
    rewind(stdin);
    return str;
}

char* Menu::undefinedName()
{
    const char* str = "undefined";
    char* mutableStr = const_cast<char*>(str);
    return mutableStr;
}