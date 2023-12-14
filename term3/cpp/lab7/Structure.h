#pragma once
#include <iostream>

using namespace std;

class Structure
{
private:
    int id;
    string info;

public:
    Structure(){};


    friend ostream &operator<<(ostream &os, Structure &structureNote);
    friend istream &operator>>(istream &is, Structure& structureNote);

    //get set
    int getId() { return id; }
    string getInfo() { return info; }
    void setId(int _id) { this->id = _id; }
    void setInfo(string _info) { this->info = _info; }

};