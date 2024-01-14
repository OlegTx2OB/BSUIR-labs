#pragma once
#include <iostream>
#include "Cell.h"

class HashTable
{
public:
    std::shared_ptr<Cell> head;
    std::shared_ptr<Cell> tail;

public:
    HashTable(std::shared_ptr<Cell> tail, std::shared_ptr<Cell> head) : head(head), tail(tail) {}
    HashTable() {}

    std::shared_ptr<Cell> getHead() { return head; }
    std::shared_ptr<Cell> getTail() { return tail; }

    void setHead(std::shared_ptr<Cell> head) { this->head = head; }
    void setTail(std::shared_ptr<Cell> tail) { this->tail = tail; }

    static void push(HashTable *hashTable, std::shared_ptr<Cell> newCell);
    static void pop(HashTable *hashTable, char* login);
    static std::shared_ptr<Cell> peek(HashTable hashTable, char* login);
    static int hashCalculation(char* password);

};