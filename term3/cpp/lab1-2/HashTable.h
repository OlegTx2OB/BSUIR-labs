#pragma once
#include <iostream>
#include "Cell.h"

class HashTable
{
public:
    Cell* head;
    Cell* tail;

public:
    HashTable(Cell* tail, Cell* head) : head(head), tail(tail) {}
    HashTable() {}

    Cell* getHead() { return head; }
    Cell* getTail() { return tail; }

    void setHead(Cell* head) { this->head = head; }
    void setTail(Cell* tail) { this->tail = tail; }

    static void push(HashTable *hashTable, Cell *newCell);
    static void pop(HashTable *hashTable, char* login);
    static Cell* peek(HashTable hashTable, char* login);
    static int hashCalculation(char* password);

};