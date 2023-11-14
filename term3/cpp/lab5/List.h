#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Node
{
    T value;
    Node<T>* prev;
    Node<T>* next;
};
template <typename T>
class List
{
public:
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    List(){}

    void addNode()
    {
        Node<T>* node = new Node<T>;
        T value = getValue();
        node->value = value;

        if (this->head == nullptr)
            this->head = this->tail = node;
        else
        {
            node->prev = this->tail;
            this->tail->next = node;
            this->tail = node;
        }
    }
    void isEmpty()
    {
        if (this->head == nullptr) cout << "List is empty" << endl;
        else cout << "List is NOT empty" << endl;
    }
    void print()
    {
        cout << "Your list: ";
        if(this->head != nullptr)
        {
            Node<T>* node = this->head;
            while(node != nullptr)
            {
                cout << node->value << " ";
                node = node->next;
            }
        }
    }
    void deleteAll()
    {
        if (this->head == nullptr)
            cout << "List is empty" << endl;
        else if (this->head == this->tail)
        {
            delete this->head;
            cout << "List is clear" << endl;
        }
        else
        {
            Node<T>* node = this->head;
            Node<T>* nodeBuff;
            while (node != nullptr)
            {
                nodeBuff = node;
                node = node->next;
                delete nodeBuff;
                cout << "Element deleted" << endl;
            }
            cout << "List is clear" << endl;
        }
        this->head = this->tail = nullptr;
    }
    void deleteByValue()
    {
        if(this->head != nullptr)
        {
            cout << "Enter node value:";
            T value = getValue();
            Node<T>* node = getNodeByValue(value);
            if(node != nullptr) pop(node);
            else cout << "Element is NOT found" << endl;
        }
        else cout << "List is clear" << endl;
    }

    T getValue()
    {
        T value;
        if (typeid(value) == typeid(int))
        {
            cout << "enter int:";
            while (!scanf("%d", &value))
            {
                cout << "invalid input. enter int:";
                rewind(stdin);
            }
        }
        else if (typeid(value) == typeid(float))
        {
            cout << "enter float:";
            while (!scanf("%f", &value))
            {
                cout << "invalid input. enter float:";
                rewind(stdin);
            }
        }
        else if (typeid(value) == typeid(string))
        {
            cout << "enter string:";
            cin >> value;
        }
        return value;
    }
    Node<T>* getNodeByValue(T value)
    {
        Node<T>* node = this->head;
        bool isFound = false;
        while(node != nullptr)
        {
            if (node->value == value)
            {
                isFound = true;
                break;
            }
            node = node->next;
        }
        if(!isFound) return nullptr;
        return node;
    }
    void pop(Node<T>* &node)
    {
//1
        if(this->head == this->tail)
        {
            delete node;
            this->head = this->tail = nullptr;
        }
//first
        else if(this->head == node)
        {
            Node<T>* nextNode = node->next;
            this->head = nextNode;
            delete node;
            nextNode->prev = nullptr;
        }
//last
        else if(this->tail == node)
        {
            Node<T>* prevNode = node->prev;
            this->tail = prevNode;
            delete node;
            prevNode->next = nullptr;
        }
        else
        {
            Node<T>* nextNode = node->next;
            Node<T>* prevNode = node->prev;

            delete node;

            nextNode->prev = prevNode;
            prevNode->next = nextNode;
        }
        cout << "Element has been deleted" << endl;
    }
};
