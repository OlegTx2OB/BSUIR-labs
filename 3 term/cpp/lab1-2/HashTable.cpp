#include <cstring>
#include "HashTable.h"
#define MAX_ARRAY_SIZE 1000

using namespace std;

int HashTable::hashCalculation(char* password)
{
    const char* key = "This is example of key for the first fucking laba";
    unsigned long hash = 0;
    for (int i = 0; i < strlen(password); i++) hash += password[i] * i + key[i];

    return (hash % MAX_ARRAY_SIZE);
}

void HashTable::push(HashTable *hashTable, Cell *newCell)
{
    if (hashTable->head == nullptr)
    {
        hashTable->tail = newCell;
        hashTable->head = newCell;
        newCell->setNext(nullptr);
        newCell->setPrev(nullptr);
    }
    else
    {
        newCell->setPrev(hashTable->tail);
        hashTable->tail->setNext(newCell);
        hashTable->tail = newCell;
    }
    cout << "New person has been registered\n";
}
Cell* HashTable::peek(HashTable hashTable, char* login)
{
    if (hashTable.head == nullptr)
    {
        return nullptr;
    }
    Cell* currentCell = hashTable.head;
    while (currentCell != nullptr)
    {
        if (strcmp(currentCell->getLogin(), login) == 0)
        {
            return currentCell;
        }
        currentCell = currentCell->getNext();
    }
    return nullptr;
}

void HashTable::pop(HashTable *hashTable, char* login)
{
    bool neededUserDeleted = false;

    if (hashTable->head == nullptr)
    {
        cout << "User is not found\n";
        return;
    }

    Cell* currentCell = hashTable->head;

    while (currentCell != nullptr)
    {
        if (strcmp(currentCell->getLogin(), login) == 0)
        {
            if (currentCell->getPrev() == nullptr)
            {
                hashTable->head = currentCell->getNext();
                if (hashTable->head != nullptr)
                {
                    hashTable->head->setPrev(nullptr);
                }
            }
            else if (currentCell->getNext() == nullptr)
            {
                hashTable->tail = currentCell->getPrev();
                if (hashTable->tail != nullptr)
                {
                    hashTable->tail->setNext(nullptr);
                }
            }
            else
            {
                Cell* prevCell = currentCell->getPrev();
                Cell* nextCell = currentCell->getNext();
                prevCell->setNext(nextCell);
                nextCell->setPrev(prevCell);
            }

            delete currentCell;
            neededUserDeleted = true;
            break;
        }

        currentCell = currentCell->getNext();
    }

    if (!neededUserDeleted) cout << "User is not found\n";

}