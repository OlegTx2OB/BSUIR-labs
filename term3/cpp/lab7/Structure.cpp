#include "Structure.h"

ostream &operator<<(ostream &os, Structure &structureNote)
{
    int id = structureNote.getId();
    string strId= to_string(id);
    string info= structureNote.getInfo();
    string out= "{id: " + strId + " | info: " + info + "}\n";
    os << out;
    return os;
}
istream& operator>>(std::istream& is, Structure& structureNote) {
    char c;
    is >> c; // {
    is >> c; // id
    is >> c; // :
    is >> structureNote.id; // id
    is >> c; // |
    is >> c; // info
    is >> c; // :
    is.ignore();
    std::getline(is, structureNote.info, '}'); // info
    return is;
}