#include <iostream>
#include "BinFile.h"

using namespace std;
BinFile::BinFile(vector<Structure*> structureVector)
{
    ofstream outputFile("binary_file.bin", ios::binary);
    if (outputFile.is_open())
    {
        for (auto& structureNote : structureVector)
        {
            // binary input into file
            int id = structureNote->getId();
            outputFile.write(reinterpret_cast<const char*>(&id), sizeof(int));

            string info = structureNote->getInfo();
            int infoLength = info.size();
            outputFile.write(reinterpret_cast<const char*>(&infoLength), sizeof(int));
            outputFile.write(info.c_str(), infoLength);
        }
        outputFile.close();
    }
    else cout << "Binary file cannot be opened\n";
}
